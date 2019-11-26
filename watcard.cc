#include "watcard.h"

/**
 *  - Create with $0 balance
 *  - Courier calls deposit after a funds transfer
 *  - VendingMachine calls withdraw when a soda is purchased
 * 
 *  Note 1: FWATCard is a future pointer to a student’s WATCard for synchronizing
 *          access to the WATCard between the student and the courier.
 */

// ---------------------------------
//  Constructor
// ---------------------------------
WATCard::WATCard() : balance( 0 ) {
}  // WATCard::WATCard

// ---------------------------------
//  Public Methods
// ---------------------------------
void WATCard::deposit( unsigned int amount ) {
    balance += amount;
}  // WATCard::deposit

void WATCard::withdraw( unsigned int amount ) {
    balance -= amount;
}  // WATCard::withdraw

unsigned int WATCard::getBalance() {
    return balance;
}  // WATCard::getBalance