#include "bottlingplant.h"

// TODO:
/*

  fields:
  - constructor vars
  - TimeBetweenShipments const
  - map (soda: quantity)

  main:
  - loop probably:
    - produce random quantities of each flavour of soda (loop through) add to map
    - create truck
    - wait for it to call getShipment
    - yield (TimeBetweenShipments)

  getShipment:
  - if plant shutdown, throw exception
  - else fill truck as best as possible (loop and fill cargo array)

*/

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
unsigned int timeBetweenShipments )
: {}

void BottlingPlant::main(){

}

void BottlingPlant::getShipment( unsigned int cargo[] ){

}