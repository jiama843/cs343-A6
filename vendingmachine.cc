#include "vendingmachine.h"

// TODO:
/*

  fields:
  - constructor
  - const int (MaxStockPerFlavour)
  - flag (restocked?)
  - cost
  - id
  - map (soda flavor: quantity)

  main:
  - Probably loop with _Accept(buy) or _Accept(restock) or _Accept(inventory) etc.

  buy:
  - MUST HALT WHILE RESTOCKING -> in main _Accept(restock) after _Accept(buy)
  - Check if student has sufficient funds -> card.getBalance()
    - If insufficient, raise Funds exception
  - Check if soda is available -> stock[flavour]
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
: prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost) {}

void VendingMachine::main(){
  prt.print(Printer::VendingMachine, 'S', sodaCost);
  for(;;){
    _Accept(~VendingMachine) {
      break;
    }
    or _Accept(inventory){

      // Can only buy after restocking is complete
      _Accept(restocked){}
    }
    or _Accept(buy){
      // Check insufficient funds
      if(card.getBalance() < sodaCost) _Throw Funds{}; 

      // Check insufficient stock
      if(stock[flavour] <= 0) _Throw Stock{}; 

      // Free?
      if(mprng(1, 5) == 1) _Throw Free{};

      card.withdraw(sodaCost); // Debit WATcard
      stock[flavour]--; // Dispense soda

      prt.print(Printer::Kind::VendingMachine, 'B', flavour, stock[flavour]);
    }
  }
  prt.print(Printer::Kind::VendingMachine, 'F');
}

void VendingMachine::buy( Flavours flavour, WATCard & card ){
  VendingMachine::flavour = flavour;
  VendingMachine::card = card;
  // Might need uCond for two consecutive buy case
}

unsigned int * VendingMachine::inventory(){
  prt.print(Printer::Kind::VendingMachine, 'r');
  return stock;
}

void VendingMachine::restocked(){
  prt.print(Printer::Kind::VendingMachine, 'R');
}

_Nomutex unsigned int VendingMachine::cost() const{
  return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() const{
  return id;
}