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
    unsigned int num_bottles = mprng(1, maxPurchases);
    unsigned int flavour = mprng(3);
    prt.print(Printer::Kind::Student, 'S', flavour, num_bottles);

    WATCard::FWATCard wc = cardOffice.create(id, 5); // Create 5$ WATCard
    WATCard::FWATCard gc = groupoff.giftcard(); // Get future giftcard
    VendingMachine *vm = nameServer.getMachine(id); // Get vending machine location

    prt.print(Printer::Kind::Student, 'V', vm->getId());

    for(int i = 0; i < num_bottles; i++){
        // Before buying soda
        yield(mprng(1, 10));

        // Block until either card is available
        WATCard::WATCard *card;
        _Select(wc){
            *card = &wc;
        }
        or _Select(gc){
            *card = &gc;
        }

        for(;;){
            // Attempt to buy soda
            try{
                try{
                    vm.buy(flavour, card);

                    if (card == wc){
                        prt.print(Printer::Kind::Student, 'W', flavour, card->getBalance());
                    }
                    else if(card == gc){
                        prt.print(Printer::Kind::Student, 'G', flavour, card->getBalance());
                        gc.reset(); // Reset funds if giftcard
                    }

                    break;
                }
                _Catch (VendingMachine::Free &){
                    yield(4 * 10);

                    if (card == wc){
                        prt.print(Printer::Kind::Student, 'A', flavour, card->getBalance());
                    }
                    else if(card == gc){
                        prt.print(Printer::Kind::Student, 'a', flavour, card->getBalance());
                    }

                    break;
                }
                _Catch (VendingMachine::Funds &){
                    if(card == wc){
                        cardOffice.transfer(id, vm.cost() + 5, card);
                    }
                }
                _Catch (VendingMachine::Stock &){
                    vm = nameServer.getMachine(id); // Get another vending machine
                }
            }
            _Catch(WATCardOffice::Lost){ // Catch courier exception if lost
                prt.print(Printer::Kind::Student, 'L');
                wc = cardOffice.create(id, 5); // Create 5$ WATCard
            }
        }
    }

    prt.print(Printer::Kind::Student, 'F');
}  // Student::main

// ---------------------------------
//  Constructor
// ---------------------------------
Student::Student( Printer& prt, NameServer& nameServer, WATCardOffice& cardOffice, Groupoff& groupoff, unsigned int id, unsigned int maxPurchases ) : 
    prt( prt ), nameServer( nameServer ), cardOffice( cardOffice ), groupoff( groupoff ), id( id ), maxPurchases( maxPurchases ) {
}  // Student::Student