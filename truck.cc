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


void Truck::restock_vending(VendingMachine ** vlist){
  // Start restocking at NEXT vending machine
  lastVendingMachine++;

  for (int i = 0; i < numVendingMachines; i++){
    int *inv = vlist[i]->inventory();

    for(int j = 0; j < NUM_FLAVOURS; j++){

      // Fill with as much soda as possible
      while(inv[j] < maxStockPerFlavour && cargo[j] > 0){
        inv[j]++;
        cargo[j]--;
      }
    }

    vlist[i]->restocked();
  }
}


void Truck::main(){
  // Array of pointers to vending machines
  VendingMachine ** vlist = nameServer.getMachineList();
  
  try {
    for(;;){
      yield(mprng(1, 10));
      cargo = {0, 0, 0, 0};
      plant.getShipment(cargo);
      restock_vending(vlist);
    }
  }
  _Catch(BottlingPlant::Shutdown &){
    // handle Shutdown
  }
}
