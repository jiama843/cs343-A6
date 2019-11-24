#include <unistd.h>  // access: getpid
#include <cstdlib>   // access: exit
#include <cstring>   // access: strcmp
#include <fstream>   // access: ifstream
#include <iostream>  // access: cerr, cin, cout, istream, ostream

#include "MPRNG.h"           // the random number generator
#include "bank.h"            // the Bank Monitor
#include "bottlingplant.h"   // the BottlingPlant Task
#include "config.h"          // the ConfigParms struct
#include "group.h"           // the Groupoff Task
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


}  // uMain
