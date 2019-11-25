#include "nameserver.h"

// TODO:
/*

  fields:
  - Map (id: vending machine)
  - list (vending machines)
  - incremental int (from 1 to infinity) -> modulo numVendingMachines

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
: prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents), 
vlist(new *VendingMachine[numVendingMachines]), student_incr(new int[newnumStudents]) {}

void NameServer::main(){

}

void NameServer::VMregister( VendingMachine * vendingmachine ){
  vlist[vendingmachine.id] = vendingmachine;
}

VendingMachine * NameServer::getMachine( unsigned int id ){
  student_incr[id]++;
  return vlist[(id + student_incr[id]) % numVendingMachines];
}

VendingMachine ** NameServer::getMachineList(){
  return vlist;
}