#ifndef BOTTLING_H
#define BOTTLING_H

#include "nameserver.h"
#include "printer.h"

_Task BottlingPlant {
    Printer&     prt;
    NameServer&  nameServer;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;

    unsigned int inventory[4];         // there are 4 different flavours
    bool         shouldThrowShutdown;  // set to true once Destructor is called

    void main();

   public:
    _Event Shutdown{};  // shutdown plant

    BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
                   unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                   unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
};

#endif