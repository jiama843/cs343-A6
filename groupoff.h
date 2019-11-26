#ifndef GROUP_H
#define GROUP_H

#include <vector>

#include "MPRNG.h"
#include "printer.h"
#include "watcard.h"

extern MPRNG mprng;

_Task Groupoff {
	int num_assigned = 0;
	vector<WATCard::FWATCard> fcards; // list of future watcards
	void main();

public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	WATCard::FWATCard giftCard();

private:
	WATCard::FWATCard fcard;
};

#endif