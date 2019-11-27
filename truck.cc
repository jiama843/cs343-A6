#include "truck.h"
#include "vendingmachine.h"

#include "MPRNG.h"

extern MPRNG mprng;  // global random number generator

/**
 * fields:
 * - constructor vars
 * - lastVendingMachine
 * - map (soda flavor: quantity)
 *
 * main:
 * - obtain all vending machine locations from nameserver (getMachineList()?)
 * - loop
 *   - yield from [1, 10]
 *   - clear list of soda (throw away out of date soda)
 *   - call plant.getShipment() to get soda from bottling plant
 *   - Restock vending machines starting from lastVendingMachine
 *     - Fill machines to max, or empty truck
 *
 */

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour )
    : prt( prt ), nameServer( nameServer ), plant( plant ), numVendingMachines( numVendingMachines ), maxStockPerFlavour( maxStockPerFlavour ), lastVendingMachine( -1 ) {}

void Truck::restock_vending( VendingMachine **vlist ) {
    for ( unsigned int i = 0; i < numVendingMachines; i++ ) {
        // Start restocking at NEXT vending machine
        lastVendingMachine++;
        lastVendingMachine %= numVendingMachines;

        prt.print( Printer::Kind::Truck, 'd', lastVendingMachine, cargo[0] + cargo[1] + cargo[2] + cargo[3] );  // begin delivery to vending machine
        unsigned int *inv = vlist[lastVendingMachine]->inventory();

        for ( int j = 0; j < NUM_FLAVOURS; j++ ) {
            // Fill with as much soda as possible
            for ( ;; ) {
                if ( inv[j] >= maxStockPerFlavour ) break;
                if ( cargo[j] <= 0 ) break;

                inv[j]++;
                cargo[j]--;
            }  // for
        }  // for

        int b_remain = ( maxStockPerFlavour * 4 ) - ( inv[0] + inv[1] + inv[2] + inv[3] );
        if ( b_remain > 0 ) prt.print( Printer::Kind::Truck, 'U', lastVendingMachine, b_remain );  // unsuccessfully filled vending machine

        prt.print( Printer::Kind::Truck, 'D', lastVendingMachine, cargo[0] + cargo[1] + cargo[2] + cargo[3] );  // end delivery to vending machine
        vlist[lastVendingMachine]->restocked();
    }  // for
}  // Truck::restock_vending

void Truck::main() {
    prt.print( Printer::Kind::Truck, 'S' );  // starting

    // Array of pointers to vending machines
    VendingMachine **vlist = nameServer.getMachineList();

    try {
        for ( ;; ) {
            yield( mprng( 1, 10 ) ); // yield from [1, 10] to get coffee

            // clear list of soda (throw away out of date soda)
            cargo[0] = 0;
            cargo[1] = 0;
            cargo[2] = 0;
            cargo[3] = 0;

            // call plant.getShipment() to get soda from bottling plant
            plant.getShipment( cargo );
            prt.print( Printer::Kind::Truck, 'P', cargo[0] + cargo[1] + cargo[2] + cargo[3] );  // picked up shipment

            // restock vending machines starting from lastVendingMachine
            restock_vending( vlist );
        }  // for
    }
    _Catch( BottlingPlant::Shutdown & ) {
        // handle Shutdown
        prt.print( Printer::Kind::Truck, 'F' );  // finished
    }  // try
}  // Truck::main
