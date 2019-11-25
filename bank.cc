#include "bank.h"

/**
 *  - Create student accounts with $0 balances
 *  - Parent calls deposit for a specific student
 *  - Courier calls withdraw to transfer money
 */

// ---------------------------------
//  Constructor and Destructor
// ---------------------------------
Bank::Bank( unsigned int numStudents ) : numStudents( numStudents ), accounts( new unsigned int[numStudents] ) {
    for ( unsigned int i = 0; i < numStudents; i++ ) {
        // fill the accouts with $0
        accounts[i] = 0;
    }  // for
}  // Bank::Bank

Bank::~Bank() {
    delete accounts;
}  // Bank::~Bank

// ---------------------------------
//  Public Methods
// ---------------------------------
void Bank::deposit( unsigned int id, unsigned int amount ) {
    accounts[id] += amount;
}  // Bank::deposit

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    accounts[id] -= amount;
}  // Bank::withdraw
