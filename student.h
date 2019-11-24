#ifndef STUDENT_H
#define STUDENT_H

// TODO: Includes

_Task Student {
    Printer &prt;
	NameServer &nameServer; 
	WATCardOffice &cardOffice;
	Groupoff &groupoff;
    unsigned int id;
	unsigned int maxPurchases;

	void main();

   public:
	Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
			 unsigned int id, unsigned int maxPurchases );
};

#endif