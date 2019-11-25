#include "truck.h"

// TODO:
/*

  fields:
  - constructor vars
  - lastVendingMachine
  - map (soda flavor: quantity)

  main:
  - obtain all vending machine locations from nameserver (getMachineList()?)
  - loop
    - yield from [0, 10]
    - clear list of soda (throw away out of date soda)
    - call plant.getShipment() to get soda from bottling plant
    - Restock vending machines starting from lastVendingMachine
      - Fill machines to max, or empty truck

*/

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
      unsigned int numVendingMachines, unsigned int maxStockPerFlavour )
: prt(prt), nameServer(nameServer), plant(plant), numVendingMachines(numVendingMachines),
  maxStockPerFlavour(maxStockPerFlavour), lastVendingMachine(0) {}


void Truck::restock_vending(){

}


void Truck::main(){
  VendingMachine ** vlist = nameServer.getMachineList();
  
  try {  
    yield(1, 10);
    cargo = {0, 0, 0, 0};
    plant.getShipment(cargo);
    restock_vending();
  }
  catch(BottlingPlant::Shutdown){
    // handle Shutdown
  }

}
