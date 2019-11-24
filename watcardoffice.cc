#include "watcardoffice.h"

using namespace std;

/**
 * TODO:
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
//  Private Methods
// ---------------------------------
void WATCardOffice::main() {
}  // WATCardOffice::main

// ---------------------------------
//  Constructor
// ---------------------------------
WATCardOffice( Printer& prt, Bank& bank, unsigned int numCouriers ) : prt( prt ), bank( bank ), numCouriers( numCouriers ) {
    
}  // WATCardOffice::WATCardOffice

// ---------------------------------
//  Public Methods
// ---------------------------------
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    // TODO
}  // WATCardOffice::create

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard* card ) {
    // TODO
}  // WATCardOffice::transfer

Job * WATCardOffice::requestWork() {
    // TODO
}  // WATCardOffice::requestWork