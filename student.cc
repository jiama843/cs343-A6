#include "student.h"
#include "vendingmachine.h"

using namespace std;

/**
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
    VendingMachine::Flavours flavour = (VendingMachine::Flavours)mprng(3);
    prt.print(Printer::Kind::Student, id, 'S', flavour, num_bottles);

    WATCard::FWATCard wc = cardOffice.create(id, 5); // Create 5$ WATCard
    WATCard::FWATCard gc = groupoff.giftCard(); // Get future giftcard
    VendingMachine *vm = nameServer.getMachine(id); // Get vending machine location

    prt.print(Printer::Kind::Student, id, 'V', vm->getId());

    for(unsigned int i = 0; i < num_bottles; i++){
        // Before buying soda
        yield(mprng(1, 10));

        // Block until either card is available
        WATCard *card;
        _Select(gc){
            card = gc();
        }
        or _Select(wc){
            card = wc();
        }  // _Select

        for(;;){
            // Attempt to buy soda
            try{
                try{
                    vm->buy(flavour, *card);

                    if (card == wc){
                        prt.print(Printer::Kind::Student, id, 'B', flavour, card->getBalance());
                    }
                    else if(card == gc){
                        prt.print(Printer::Kind::Student, id, 'G', flavour, card->getBalance());
                        gc.reset(); // Reset funds if giftcard
                    }  // if

                    break;
                }
                _Catch (VendingMachine::Free &){
                    yield(4);

                    if (card == wc){
                        prt.print(Printer::Kind::Student, id, 'A', flavour, card->getBalance());
                    }
                    else if(card == gc){
                        prt.print(Printer::Kind::Student, id, 'a', flavour, card->getBalance());
                    }  // if
                }
                _Catch (VendingMachine::Funds &){
                    if(card == wc){
                        cardOffice.transfer(id, vm->cost() + 5, card);
                    }  // if
                }
                _Catch (VendingMachine::Stock &){
                    vm = nameServer.getMachine(id); // Get another vending machine
                }  // _Catch
            }
            _Catch(WATCardOffice::Lost &){ // Catch courier exception if lost
                prt.print(Printer::Kind::Student, id, 'L');
                wc = cardOffice.create(id, 5); // Create 5$ WATCard
            }  // _Catch
        }  // for
    }  // for

    prt.print(Printer::Kind::Student, id, 'F');
}  // Student::main

// ---------------------------------
//  Constructor
// ---------------------------------
Student::Student( Printer& prt, NameServer& nameServer, WATCardOffice& cardOffice, Groupoff& groupoff, unsigned int id, unsigned int maxPurchases ) : 
    prt( prt ), nameServer( nameServer ), cardOffice( cardOffice ), groupoff( groupoff ), id( id ), maxPurchases( maxPurchases ) {
}  // Student::Student