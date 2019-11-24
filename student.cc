#include "student.h"

using namespace std;

/**
 * TODO:
 *  --> Begin by:
 *      - Selecting a random number of bottles to burchase [1, maxPurchases]
 *      - Selecting a random favourite flavour [0, 3]
 *      - Creating a WATCard via the WATCardOffice
 *      - Creating a gift card via the Groupoff with a value of SodaCost
 *      - Obtaining the location of a vendinc machine from the NameServer
 * 
 *  --> Before buying a soda:
 *      - yield [1, 10]
 *      - Wait for money to be transferred (either WATCard or gift card)
 *      - Buy a single bottle of soda
 *      - Reset giftcard future after use
 *      - If WATCardOffice::Lost is raised when accessing future, create a new WATCard
 *      - Re-attempt to buy a soda without yielding
 *      - WATCard may be lost repeatedly
 * 
 *  --> When buying a soda:
 *      - Call a vending machine to begin transaction
 *      - One of the four scenarios can happen:
 *          - If vending machine returns PAID bottle of soda
 *          - If vending machine returns FREE bottle of soda, yield 4 times
 *          - If vending machine returns insufficient funds, transfer soda-cost + $5 to WATCard
 *          - If vending machine is out of favourite flavour, get another vending machine from NameServer
 *      - After one of the four scenarios above, attempt ANOTHER PURCHASE
 * 
 *  Note 1: A student may busy wait while waiting for a specific soda to appear.
 *  Note 2: Watch out for the case where a student buys just ONE soda with gift card.
 */

// ---------------------------------
//  Private Methods
// ---------------------------------
void Student::main() {

}  // Student::main

// ---------------------------------
//  Constructor
// ---------------------------------
Student::Student( Printer& prt, NameServer& nameServer, WATCardOffice& cardOffice, Groupoff& groupoff, unsigned int id, unsigned int maxPurchases ) : 
    prt( prt ), nameServer( nameServer ), cardOffice( cardOffice ), groupoff( groupoff ), id( id ), maxPurchases( maxPurchases ) {

}  // Student::Student