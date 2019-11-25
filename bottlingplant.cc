#include "bottlingplant.h"
#include "MPRNG.h"  // the random number generator

extern MPRNG mprng;  // global random number generator

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

// ---------------------------------
//  Private Methods
// ---------------------------------
void BottlingPlant::main() {
    printer.print( Printer::Kind::BottlingPlant, 'S' );  // starting

    // begin by creating a truck
    Truck truck( prt, nameServer, *this, numVendingMachines, maxStockPerFlavour );

    for ( ;; ) {
        try {
            /*
             * periodically produce random new quantities of each flavour of soda,
             * [0, MaxShippedPerFlavour] per flavour.
             */
            unsigned int sodaQuantity = mprng( maxShippedPerFlavour );
            printer.print( Printer::Kind::BottlingPlant, 'G', sodaQuantity );  // generating soda

            inventory[0] = sodaQuantity;
            inventory[1] = sodaQuantity;
            inventory[2] = sodaQuantity;
            inventory[3] = sodaQuantity;

            /*
             * To simulate a production run of soda, the bottling plant
             * yields for TimeBetweenShipments times (not random).
             */
            yield( timeBetweenShipments );

            _Accept( ~BottlingPlant ) {
                shouldThrowShutdown = true;
                break;
            }
            or _Accept( getShipment ) {
                // shipment picked up by truck
                printer.print( Printer::Kind::BottlingPlant, 'P' );
            }  // _Accept
        } catch ( uMutexFailure::RendezvousFailure& ) {
            // so we know there is a Shutdown here
        }  // try

    }  // for

    printer.print( Printer::Kind::BottlingPlant, 'F' );  // finished
}  // BottlingPlant::main

// ---------------------------------
//  Constructor
// ---------------------------------
BottlingPlant::BottlingPlant( Printer& prt, NameServer& nameServer, unsigned int numVendingMachines,
                              unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                              unsigned int timeBetweenShipments ) : prt( prt ), nameServer( nameServer ), numVendingMachines( numVendingMachines ), maxShippedPerFlavour( maxShippedPerFlavour ), maxStockPerFlavour( maxShippedPerFlavour ), timeBetweenShipments( timeBetweenShipments ), inventory( { 0, 0, 0, 0 } ), shouldThrowShutdown( false ) {
}  // BottlingPlant::BottlingPlant

// ---------------------------------
//  Public Methods
// ---------------------------------

// getShipment throws the exception Shutdown if the bottling plant is closing down
void BottlingPlant::getShipment( unsigned int cargo[] ) {
    /*
     * getShipment throws the exception Shutdown if the bottling plant is closing
     * down and no shipment is copied into the cargo array passed by the truck
     */
    if ( shouldThrowShutdown ) {
        _Throw Shutdown();
    }  // if

    /*
     * The truck calls getShipment to obtain a shipment from the plant 
     * (i.e., the production run), and the shipment is copied into the
     * cargo array passed by the truck
     */
    cargo[0] = inventory[0];
    cargo[1] = inventory[1];
    cargo[2] = inventory[2];
    cargo[3] = inventory[3];
}  // BottlingPlant::getShipment