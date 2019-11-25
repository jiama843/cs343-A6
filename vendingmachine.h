#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include "watcard.h"

_Task VendingMachine {
	int id;
	int sodaCost;
	Printer &prt;
	NameServer &nameServer;

	int * stock[4] = {0};

	void main();

public:
	enum Flavours { A, B, C, D }; 				// flavours of soda (YOU DEFINE)
	_Event Free {};						// free, advertisement
	_Event Funds {};					// insufficient funds
	_Event Stock {};					// out of stock for particular flavour
	VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost );
	void buy( Flavours flavour, WATCard & card );
	unsigned int * inventory();
	void restocked();
	_Nomutex unsigned int cost() const;
	_Nomutex unsigned int getId() const;

private:
	// Local variables
	WATCard card;
	Flavours flavour;
};

#endif