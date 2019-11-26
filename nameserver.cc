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
vlist(new *VendingMachine[numVendingMachines]), student_incr(new int[numStudents]) {
  for (int i = 0; i < numStudents; i++){
    student_incr[i] = 0;
  }
}

void NameServer::main(){
  prt.print(Printer::NameServer, 'S');

  for(int i = 0; i < numVendingMachines; i++){
    _Accept(VMregister);
  }

  for(;;){
    _Accept(~NameServer) break;
  }

  delete[] vlist;

  prt.print(Printer::NameServer, 'F');
}

void NameServer::VMregister( VendingMachine * vendingmachine ){
  prt.print(Printer::NameServer, 'V', vendingmachine.id);
  vlist[vendingmachine.id] = vendingmachine;
}

VendingMachine * NameServer::getMachine( unsigned int id ){
  student_incr[id]++;
  VendingMachine *v = vlist[(id + student_incr[id]) % numVendingMachines];

  printer.print(Printer::NameServer, 'N', id, v->getId());
  return v;
}

VendingMachine ** NameServer::getMachineList(){
  return vlist;
}