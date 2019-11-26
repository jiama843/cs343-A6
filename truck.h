#ifndef TRUCK_H
#define TRUCK_H

#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"

_Task Truck {
	const int NUM_FLAVOURS = 4;

	Printer & prt;
	NameServer & nameServer;
	BottlingPlant & plant;

	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;

	int lastVendingMachine;
	int cargo[4] = {0};

	// helper method for restocking vending machines
	void restock_vending(VendingMachine ** vlist);

	void main();
  public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif