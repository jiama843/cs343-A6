#include "nameserver.h"

// TODO:
/*

  fields:
  - Map (id: vending machine)
  - list (vending machines)
  - incremental int (from 1 to infinity) -> modulo getMachineList.size() or smth

  main:
  - loop through all student ids 
    - assign student vending machine sequentially

  VMregister:
  - Called by vending machines -> set vending machine id (need field)

  getMachineList:
  - return list of all vending machines (need list field)

  getMachine:
  - Use student id to map to a vending machine(map)
    - return getMachineList[incremental int % getMachineList.size()] (modulo incrementing)

*/

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents )
: {}

void NameServer::main(){

}

void NameServer::VMregister( VendingMachine * vendingmachine ){

}

VendingMachine * NameServer::getMachine( unsigned int id ){

}

VendingMachine ** NameServer::getMachineList(){

}