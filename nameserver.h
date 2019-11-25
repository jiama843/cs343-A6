#ifndef NAME_SERVER_H
#define NAME_SERVER_H

_Task NameServer {
	Printer &prt;
	int numVendingMachines;
	int numStudents;
	VendingMachine ** vlist;

	void main();

public:
	NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
	void VMregister( VendingMachine * vendingmachine );
	VendingMachine * getMachine( unsigned int id );
	VendingMachine ** getMachineList();
};

#endif