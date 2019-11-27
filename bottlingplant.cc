#include "bottlingplant.h"
#include "truck.h"

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
    prt.print( Printer::Kind::BottlingPlant, 'S' );  // starting

    // begin by creating a truck
    Truck truck( prt, nameServer, *this, numVendingMachines, maxStockPerFlavour );

    for ( ;; ) {
        try {
            /*
             * periodically produce random new quantities of each flavour of soda,
             * [0, MaxShippedPerFlavour] per flavour.
             */
            unsigned int sodaQuantity = mprng( maxShippedPerFlavour );
            prt.print( Printer::Kind::BottlingPlant, 'G', sodaQuantity );  // generating soda

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

                // we want the Truck to find out that we are closing
                _Accept( getShipment );
            }
            or _Accept( getShipment ) {
                // shipment picked up by truck
                prt.print( Printer::Kind::BottlingPlant, 'P' );
            }  // _Accept
        }
        _Catch( uMutexFailure::RendezvousFailure& ) {
            // so we know there is a Shutdown here
            break;
        }  // try

    }  // for

    prt.print( Printer::Kind::BottlingPlant, 'F' );  // finished
}  // BottlingPlant::main

// ---------------------------------
//  Constructor
// ---------------------------------
BottlingPlant::BottlingPlant( Printer& prt, NameServer& nameServer, unsigned int numVendingMachines,
                              unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                              unsigned int timeBetweenShipments ) : prt( prt ), nameServer( nameServer ), numVendingMachines( numVendingMachines ), maxShippedPerFlavour( maxShippedPerFlavour ), maxStockPerFlavour( maxStockPerFlavour ), timeBetweenShipments( timeBetweenShipments ), shouldThrowShutdown( false ) {
    inventory[0] = 0;
    inventory[1] = 0;
    inventory[2] = 0;
    inventory[3] = 0;
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
        prt.print( Printer::Kind::BottlingPlant, 'X' );  // temp
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