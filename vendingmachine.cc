#include "vendingmachine.h"

#include "MPRNG.h"

extern MPRNG mprng;  // global random number generator

/**
 * fields:
 * - constructor
 * - const int (MaxStockPerFlavour)
 * - flag (restocked?)
 * - cost
 * - id
 * - map (soda flavor: quantity)
 * 
 * main:
 * - Probably loop with _Accept(buy) or _Accept(restock) or _Accept(inventory) etc.
 * 
 * buy:
 * - MUST HALT WHILE RESTOCKING -> in main _Accept(restock) after _Accept(buy)
 * - Check if student has sufficient funds -> card.getBalance()
 *   - If insufficient, raise Funds exception
 * - Check if soda is available -> stock[flavour]
 *   - If insufficient, raise Stock exception
 * - (Both conditions are satisfied), random 1/5 chance that soda is free
 *   - if free, throw Free exception
 *   - if not free, debit the watcard balance (watcard.withdraw)
 *
 * inventory:
 * - return current stock of all sodas (will need to add data structure to store this)
 *
 * restocked:
 * - called to signal restocked (set flag variable?)
 *
 * cost:
 * - return cost of a purchasing a soda (require field)
 *
 * getid:
 * - return vending machine id (require field)
 */

// -----------------------------------
//  Constructor
// -----------------------------------
VendingMachine::VendingMachine( Printer& prt, NameServer& nameServer, unsigned int id, unsigned int sodaCost ) : prt( prt ), nameServer( nameServer ), id( id ), sodaCost( sodaCost ) {
    nameServer.VMregister( this );  // VendingMachines call VMregister to register themselves
}  // VendingMachine::VendingMachine

// -----------------------------------
//  Mutex Methods
// -----------------------------------
void VendingMachine::buy( Flavours flavour, WATCard& card ) {
    VendingMachine::flavour = flavour;
    VendingMachine::card    = &card;

    // Check insufficient funds
    if ( card.getBalance() < sodaCost ) _Throw Funds();

    // Check insufficient stock
    if ( stock[flavour] <= 0 ) _Throw Stock();

    // Free?
    if ( mprng( 1, 5 ) == 1 ) _Throw Free();
}  // VendingMachine::buy

unsigned int* VendingMachine::inventory() {
    return stock;
}  // VendingMachine::inventory

void VendingMachine::restocked() {
    // nothing needs to be done here, print is done in main
}  // VendingMachine::restocked

// -----------------------------------
//  Nomutex Methods
// -----------------------------------
_Nomutex unsigned int VendingMachine::cost() const {
    return sodaCost;
}  // VendingMachine::cost

_Nomutex unsigned int VendingMachine::getId() const {
    return id;
}  // VendingMachine::getId

// -----------------------------------
//  Task Main
// -----------------------------------
void VendingMachine::main() {
    prt.print( Printer::Kind::Vending, id, 'S', sodaCost );  // starting

    for ( ;; ) {
        try {
            _Accept( ~VendingMachine ) {
                break;
            }
            or _Accept( inventory ) {
                prt.print( Printer::Kind::Vending, id, 'r' );  // start reloading by truck

                // Can only buy after restocking is complete
                _Accept( restocked ) {
                    prt.print( Printer::Kind::Vending, id, 'R' );  // complete reloading by truck
                }
            }
            or _Accept( buy ) {
                card->withdraw( sodaCost );  // Debit WATcard
                stock[flavour]--;            // Dispense soda

                // student bought a soda
                prt.print( Printer::Kind::Vending, id, 'B', flavour, stock[flavour] );
            }  // _Accept
        }
        _Catch( uMutexFailure::RendezvousFailure& ) {
            // we failed to buy, so just go back to start of loop
        }  // try

    }  // for

    prt.print( Printer::Kind::Vending, id, 'F' );  // finished
}  // VendingMachine::main
