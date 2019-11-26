#ifndef STUDENT_H
#define STUDENT_H

// TODO: Includes
#include "MPRNG.h"
#include "printer.h"
#include "nameserver.h"
#include "watcardoffice.h"
#include "watcard.h"
#include "groupoff.h"
#include "vendingmachine.h"

extern MPRNG mprng;

_Task Student {
    Printer &      prt;
    NameServer &   nameServer;
    WATCardOffice &cardOffice;
    Groupoff &     groupoff;
    unsigned int   id;
    unsigned int   maxPurchases;

    void main();

   public:
    Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff, unsigned int id, unsigned int maxPurchases );
};

#endif