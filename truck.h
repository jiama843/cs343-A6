#ifndef TRUCK_H
#define TRUCK_H

#include "bottlingplant.h"
#include "nameserver.h"
#include "printer.h"

_Task Truck {
    const int NUM_FLAVOURS = 4;

    Printer&       prt;
    NameServer&    nameServer;
    BottlingPlant& plant;

    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;

    int          lastVendingMachine;
    unsigned int cargo[4] = { 0 };

    // helper method for restocking vending machines
    void restock_vending( VendingMachine * *vlist );

    void main();

   public:
    Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif