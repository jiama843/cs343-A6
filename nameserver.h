#ifndef NAME_SERVER_H
#define NAME_SERVER_H

#include "printer.h"

_Task NameServer {
	Printer &prt;
	unsigned int numVendingMachines;
	unsigned int numStudents;
	VendingMachine ** vlist;

	unsigned int *student_incr; // incremental modulo for each student

	void main();

public:
	NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
	void VMregister( VendingMachine * vendingmachine );
	VendingMachine * getMachine( unsigned int id );
	VendingMachine ** getMachineList();
};

#endif