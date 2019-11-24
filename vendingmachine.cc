#include "vendingmachine.h"

// TODO:
/*

  main:
  - Probably loop with _Accept(buy) or _Accept(restock) or _Accept(inventory) etc.

  buy:
  - MUST HALT WHILE RESTOCKING -> check flag variable (see restocked)?
  - Check if student has sufficient funds -> card.getBalance()
    - If insufficient, raise Funds exception
  - Check if soda is available -> 
    - If insufficient, raise Stock exception
  - (Both conditions are satisfied), random 1/5 chance that soda is free
    - if free, throw Free exception
    - if not free, debit the watcard balance (watcard.withdraw)

  inventory:
  - return current stock of all sodas (will need to add data structure to store this)

  restocked:
  - called to signal restocked (set flag variable?)

  cost:
  - return cost of a purchasing a soda (require field)

  getid:
  - return vending machine id (require field)

*/


VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost )
: {}

void VendingMachine::main(){

}

void VendingMachine::buy( Flavours flavour, WATCard & card ){

}

unsigned int * VendingMachine::inventory(){

}

void VendingMachine::restocked(){

}

_Nomutex unsigned int VendingMachine::cost() const{

}

_Nomutex unsigned int VendingMachine::getId() const{

}