#include "parent.h"
#include "printer.h"

using namespace std;

extern MPRNG mprng;  // global random number generator

/**
 *  - Periodically give [$1, $3] to a random student
 *      -- Yield for parentalDelay times before gifting
 *      -- Check for call to destructor to know when to terminate
 *      -- Use a terminating _Else on the accept statement
 */

// ---------------------------------
//  Private Methods
// ---------------------------------
void Parent::main() {
    prt.print( Printer::Kind::Parent, 'S' );  // starting

    for ( ;; ) {
        /*
         * the parent must check for a call to its destructor to know when to terminate.
         * Since it must not block on this call, it is necessary to use a terminating
         * _Else on the accept statement
         */
        _Accept( ~Parent ) {
            // hence, the parent is busy waiting for the call to its destructor.
            break;
        }
        _Else {
            yield( parentalDelay );

            unsigned int studentID = mprng( numStudents );
            unsigned int funds     = mprng( 1, 3 );

            bank.deposit( studentID, funds );
            prt.print( Printer::Kind::Parent, 'D', studentID, funds );  // deposit gift

        }  // _Accept

    }  // for

    prt.print( Printer::Kind::Parent, 'F' );  // finished
}  // Parent::main

// ---------------------------------
//  Constructor
// ---------------------------------
Parent::Parent( Printer& prt, Bank& bank, unsigned int numStudents, unsigned int parentalDelay ) : prt( prt ), bank( bank ), numStudents( numStudents ), parentalDelay( parentalDelay ) {
}  // Parent::Parent