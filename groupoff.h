#ifndef GROUP_H
#define GROUP_H

#include <vector>

#include "MPRNG.h"
#include "printer.h"
#include "watcard.h"

extern MPRNG mprng;

_Task Groupoff {
	Printer &prt;
	unsigned int numStudents;
	unsigned int sodaCost;
	unsigned int groupoffDelay;

	vector<WATCard::WATCard*> cardlist; // list of pointers to watcards
	vector<WATCard::FWATCard> fcards; // list of future watcards
	void main();

public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	~Groupoff();
	WATCard::FWATCard giftCard();
};

#endif