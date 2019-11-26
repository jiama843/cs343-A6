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

  for (int i = 0; i < numVendingMachines; i++){
    // Start restocking at NEXT vending machine
    lastVendingMachine++;
    lastVendingMachine %= numVendingMachines;

    prt.print(Printer::Kind::Truck, 'd', lastVendingMachine, cargo[0] + cargo[1] + cargo[2] + cargo[3]);
    int *inv = vlist[lastVendingMachine]->inventory();

    for(int j = 0; j < NUM_FLAVOURS; j++){

      // Fill with as much soda as possible
      for(;;){
        if (inv[j] >= maxStockPerFlavour) break;
        if (cargo[j] <= 0) break;

        inv[j]++;
        cargo[j]--;
      }
    }
    int b_remain = maxStockPerFlavour * 4 - (inv[0] + inv[1] + inv[2] + inv[3]);
    if(b_remain > 0) prt.print(Printer::Kind::Truck, 'U', lastVendingMachine, b_remain);

    prt.print(Printer::Kind::Truck, 'D', lastVendingMachine, cargo[0] + cargo[1] + cargo[2] + cargo[3]);
    vlist[lastVendingMachine]->restocked();
  }
}


void Truck::main(){
  prt.print(Printer::Kind::Truck, 'S');

  // Array of pointers to vending machines
  VendingMachine ** vlist = nameServer.getMachineList();
  
  try {
    for(;;){
      yield(mprng(1, 10));
      cargo = {0, 0, 0, 0};
      plant.getShipment(cargo);
      prt.print(Printer::Kind::Truck, 'P', cargo[0] + cargo[1] + cargo[2] + cargo[3]);

      restock_vending(vlist);
    }
  }
  _Catch(BottlingPlant::Shutdown &){
    // handle Shutdown
    prt.print(Printer::Kind::Truck, 'F');
  }
}
