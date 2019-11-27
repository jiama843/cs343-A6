#include "nameserver.h"
#include "vendingmachine.h"

/**
 * fields:
 * - Map (id: vending machine)
 * - list (vending machines)
 * - incremental int (from 1 to infinity) -> modulo numVendingMachines
 *
 * main:
 * - loop through all student ids 
 *   - assign student vending machine sequentially
 *
 * VMregister:
 * - Called by vending machines -> set vending machine id (need field)
 *
 * getMachineList:
 * - return list of all vending machines (need list field)
 *
 * getMachine:
 * - Use student id to map to a vending machine(map)
 *   - return getMachineList[incremental int % getMachineList.size()] (modulo incrementing)
 */

// -----------------------------------
//  Constructor and Destructor
// ----------------------------------
NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : prt( prt ), numVendingMachines( numVendingMachines ), numStudents( numStudents ), vlist( new VendingMachine *[numVendingMachines] ), student_incr( new unsigned int[numStudents] ) {
    for ( unsigned int i = 0; i < numStudents; i++ ) {
        student_incr[i] = 0;
    }  // for
}  // NameServer::NameServer

NameServer::~NameServer() {
    delete[] vlist;
}  // NameServer::~NameServer

// -----------------------------------
//  Mutex Methods
// ----------------------------------
void NameServer::VMregister( VendingMachine *vendingmachine ) {
    prt.print( Printer::Kind::NameServer, 'R', vendingmachine->getId() );  // register vending machine
    vlist[vendingmachine->getId()] = vendingmachine;
}  // NameServer::VMregister

VendingMachine *NameServer::getMachine( unsigned int id ) {
    VendingMachine *v = vlist[( id + student_incr[id] ) % numVendingMachines];
    student_incr[id]++;

    prt.print( Printer::Kind::NameServer, 'N', id, v->getId() );  // new vending machine
    return v;
}  // NameServer::getMachine

VendingMachine **NameServer::getMachineList() {
    return vlist;
}  // NameServer::getMachineList

// -----------------------------------
//  Task Main
// ----------------------------------
void NameServer::main() {
    prt.print( Printer::Kind::NameServer, 'S' );  // starting

    for ( unsigned int i = 0; i < numVendingMachines; i++ ) {
        _Accept( VMregister );
    }  // for

    for ( ;; ) {
        _Accept( ~NameServer ) {
            break;
        }
        or _Accept( getMachine, getMachineList );
    }  // for

    prt.print( Printer::Kind::NameServer, 'F' );  // finished
}  // NameServer::main
