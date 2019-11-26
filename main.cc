#include <unistd.h>  // access: getpid
#include <cstdlib>   // access: exit
#include <cstring>   // access: strcmp
#include <fstream>   // access: ifstream
#include <iostream>  // access: cerr, cin, cout, istream, ostream

#include "MPRNG.h"           // the random number generator
#include "bank.h"            // the Bank Monitor
#include "bottlingplant.h"   // the BottlingPlant Task
#include "config.h"          // the ConfigParms struct
#include "groupoff.h"        // the Groupoff Task
#include "nameserver.h"      // the NameServer Task
#include "parent.h"          // the Parent Task
#include "printer.h"         // the Printer Monitor
#include "student.h"         // the Student Task
#include "truck.h"           // the Truck Task
#include "vendingmachine.h"  // the VendingMachine Task
#include "watcard.h"         // the WATCard class
#include "watcardoffice.h"   // the WATCardOffice Task

using namespace std;  // direct access to std

MPRNG mprng;  // global random number generator

// -----------------------------------
//  uMain
// -----------------------------------
int main( int argc, char* argv[] ) {
    // Default values
    string configFile = "soda.config";  // contains the configuration constants
    int    seed       = getpid();       // starting seed for the random number generator

    ConfigParms configParms;  // the struct that contains the configuration parameters

    try {
        switch ( argc ) {
            case 3:
                if ( strcmp( argv[2], "d" ) != 0 ) {
                    seed = stoi( argv[2] );
                    if ( seed < 1 ) throw 1;
                }  // if

                // fallthrough
            case 2:
                configFile = argv[1];

                // fallthrough
            case 1:
                // use default values
                break;
            default:  // wrong number of options
                throw 1;
        }  // switch
    } catch ( ... ) {
        cerr << "Usage: " << argv[0]
             << " [ config-file [ Seed ] ]" << endl;
        exit( EXIT_FAILURE );  // TERMINATE

    }  // try

    // -----------------------------------
    //  Start of main code section
    //      - PRNG seed initialization
    //      - Call processConfigFile
    // -----------------------------------
    mprng.set_seed( seed );
    processConfigFile( configFile, configParms );

    // -----------------------------------
    //  Create objects in the following order:
    //      - Printer
    //      - Bank
    //      - Parent
    //      - WATCardOffice
    //      - Groupoff
    //      - NameServer
    //      - VendingMachines
    //      - BottlingPlant
    //      - Students
    // -----------------------------------
    Printer       printer( configParms.numStudents, configParms.numVendingMachines, configParms.numCouriers );  // create a printer object with number of voters
    Bank          bank( configParms.numStudents );
    Parent        parent( printer, bank, configParms.numStudents, configParms.parentalDelay );
    WATCardOffice watCardOffice( printer, bank, configParms.numCouriers );
    Groupoff      groupoff( printer, configParms.numStudents, configParms.sodaCost, configParms.groupoffDelay );
    NameServer    nameServer( printer, configParms.numVendingMachines, configParms.numStudents );

    // create all the VendingMachines
    VendingMachine* vendingMachines[configParms.numVendingMachines];
    for ( unsigned int i = 0; i < configParms.numVendingMachines; i++ ) {
        vendingMachines[i] = new VendingMachine( printer, nameServer, i, configParms.sodaCost );
    }  // for

    // dynamically allocate this so that we can control its lifetime
    BottlingPlant* bottlingPlant = new BottlingPlant( printer, nameServer, configParms.numVendingMachines, configParms.maxShippedPerFlavour, configParms.maxStockPerFlavour, configParms.timeBetweenShipments );

    // create all the Students
    Student* students[configParms.numStudents];
    for ( unsigned int i = 0; i < configParms.numStudents; i++ ) {
        students[i] = new Student( printer, nameServer, watCardOffice, groupoff, i, configParms.maxPurchases );
    }  // for

    // delete all of the Students
    for ( unsigned int i = 0; i < configParms.numStudents; i++ ) {
        delete students[i];
    }  // for

    /*
     * Note, there is one trick in closing down the system: 
     * 
     * Delete the bottling plant before deleting the vending machines to
     * allow the truck to complete its final deliveries to the vending
     * machines; otherwise, a deadlock can occur.
     */
    delete bottlingPlant;

    // delete all of the VendingMachines
    for ( unsigned int i = 0; i < configParms.numVendingMachines; i++ ) {
        delete vendingMachines[i];
    }  // for
}  // uMain
