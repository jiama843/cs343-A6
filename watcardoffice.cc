#include "watcardoffice.h"
#include "MPRNG.h"

#include <uFuture.h>
#include <queue>
#include <vector>

extern MPRNG mprng;  // global random number generator

/**
 *  --> Begin by:
 *      - Creating a fixed-size courier pool
 * 
 *  --> After constructor:
 *      - Student ASYNCHRONOUSLY calls create to create a "real" WATCard
 *        or
 *      - Student ASYNCHRONOUSLY calls transfer when it has insufficient funds
 *        Then,
 *      - A future WATCard is returned and sufficient funds are subsequently obtained from the bank via a courier
 * 
 *  --> Courier responsibilities:
 *      - Can transfer funds from a student's bank account to WATCard
 *      - Each courier calls RequestWork, blocks for a Job, then receives the next Job
 *      - Courier updates WATCard as soon as money is obtained from bank
 *      - 1 in 6 chance a courier loses WATCard
 *          -- Insert WATCardOffice::Lost into the future
 *          -- Delete the current WATCard
 */

// ---------------------------------
//  Args Struct
// ---------------------------------
WATCardOffice::Args::Args( unsigned int sid, unsigned int amount, WATCard* card ) : sid( sid ), amount( amount ), card( card ) {}

// ---------------------------------
//  Job Struct
// ---------------------------------
WATCardOffice::Job::Job( Args args ) : args( args ) {}

// ---------------------------------
//  Courier Task
// ---------------------------------
WATCardOffice::Courier::Courier( Printer& prt, Bank& bank, WATCardOffice& cardOffice, unsigned int id ) : prt( prt ), bank( bank ), cardOffice( cardOffice ), id( id ) {}

void WATCardOffice::Courier::main() {
    /*
     *  --> Courier responsibilities:
     *      - Can transfer funds from a student's bank account to WATCard
     *      - Each courier calls RequestWork, blocks for a Job, then receives the next Job
     *      - Courier updates WATCard as soon as money is obtained from bank
     *      - 1 in 6 chance a courier loses WATCard
     *          -- Insert WATCardOffice::Lost into the future
     *          -- Delete the current WATCard
     */
    prt.print( Printer::Kind::Courier, id, 'S' );  // starting

    for ( ;; ) {
        // a job is available since we passed the _When statement, so go get it
        Job* job = cardOffice.requestWork();
        if ( job == NULL ) break;

        // refer to page 176 of course notes for reference
        Args args = job->args;
        prt.print( Printer::Kind::Courier, id, 't', args.sid, args.amount );  // start funds transfer

        // withdraw sufficient funds and add to the card
        bank.withdraw( args.sid, args.amount );
        args.card->deposit( args.amount );

        // 1 in 6 chance to lose WATCard
        if ( true /* mprng( 1, 6 ) == 1 */ ) {
            job->result.exception( new Lost() );
            prt.print( Printer::Kind::Courier, id, 'L', args.sid );  // lost WATCard card
        } else {
            job->result.delivery( args.card );
            prt.print( Printer::Kind::Courier, id, 'T', args.sid, args.amount );  // complete funds transfer
        }                                                                         // if

        // job satisfied, safe to delete
        delete job;
    }  // for

    prt.print( Printer::Kind::Courier, id, 'F' );  // finished
}  // WATCardOffice::Courier::main

// ---------------------------------
//  Private Methods
// ---------------------------------
void WATCardOffice::main() {
    prt.print( Printer::Kind::WATCardOffice, 'S' );  // starting

    for ( ;; ) {
        _Accept( ~WATCardOffice ) {
            for ( ;; ) {
                // any pending jobs are invalid, so delete them
                if ( jobQueue.empty() ) break;
                delete jobQueue.front();
                jobQueue.pop();
            }  // for

            // wake every Courier up so that they can terminate
            for ( unsigned int i = 0; i < numCouriers; i++ ) {
                // cooperate by allowing couriers to be unblocked on cardOffice.requestWork();
                _Accept( requestWork );
            }  // for

            break;
        }
        or _When( !jobQueue.empty() ) _Accept( requestWork ) {
            // request work call complete
            prt.print( Printer::Kind::WATCardOffice, 'W' );
        }
        or _Accept( create ) {
            // create call complete
            prt.print( Printer::Kind::WATCardOffice, 'C', recentSID, recentAmount );
        }
        or _Accept( transfer ) {
            // transfer call complete
            prt.print( Printer::Kind::WATCardOffice, 'T', recentSID, recentAmount );
        }  // _Accept

    }  // for

    prt.print( Printer::Kind::WATCardOffice, 'F' );  // finished
}  // WATCardOffice::main

// ---------------------------------
//  Constructor and Destructor
// ---------------------------------
WATCardOffice::WATCardOffice( Printer& prt, Bank& bank, unsigned int numCouriers ) : prt( prt ), bank( bank ), numCouriers( numCouriers ) {
    /*
     *  --> Begin by:
     *      - Creating a fixed-size courier pool
     */
    couriers = new Courier*[numCouriers];

    for ( unsigned int i = 0; i < numCouriers; i++ ) {
        couriers[i] = new Courier( prt, bank, *this, i );
    }  // for
}  // WATCardOffice::WATCardOffice

WATCardOffice::~WATCardOffice() {
    for ( unsigned int i = 0; i < numCouriers; i++ ) {
        delete couriers[i];
    }  // for
    delete[] couriers;

    for ( WATCard* card : createdCards ) {
        delete card;
    }  // for
}  // WATCardOffice::~WATCardOffice

// ---------------------------------
//  Public Methods
// ---------------------------------
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    // refer to page 176 of course notes for reference on implementing "perform"
    recentSID    = sid;
    recentAmount = amount;

    // save the WATCard in a vector so that we can delete it later
    WATCard* newCard = new WATCard();
    createdCards.push_back( newCard );

    // create the new job and add it to queue
    Args args( sid, amount, newCard );
    Job* newJob = new Job( args );
    jobQueue.push( newJob );

    // return future WATCard, sufficient funds are subsequently obtained from the bank via a courier
    return newJob->result;
}  // WATCardOffice::create

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard* card ) {
    // refer to page 176 of course notes for reference on implementing "perform"
    recentSID    = sid;
    recentAmount = amount;

    // create the new job and add it to queue
    Args args( sid, amount, card );
    Job* newJob = new Job( args );
    jobQueue.push( newJob );

    // return future WATCard, sufficient funds are subsequently obtained from the bank via a courier
    return newJob->result;
}  // WATCardOffice::transfer

WATCardOffice::Job* WATCardOffice::requestWork() {
    if ( jobQueue.empty() ) return NULL;

    // grab earliest job from the queue
    Job* newJob = jobQueue.front();
    jobQueue.pop();

    return newJob;
}  // WATCardOffice::requestWork