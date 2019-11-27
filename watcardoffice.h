#ifndef WATOFFICE_H
#define WATOFFICE_H

#include <queue>
#include <vector>
#include "bank.h"
#include "printer.h"
#include "watcard.h"

_Task WATCardOffice {
    Printer &    prt;
    Bank &       bank;
    unsigned int numCouriers;

    unsigned int recentSID;     // after create/transfer, save the sid in here for printer
    unsigned int recentAmount;  // after create/transfer, save the amount in here for printer

    struct Args {
        unsigned int sid;     // student ID
        unsigned int amount;  // amount to create/transfer
        WATCard *    card;    // student's WATCard

        Args( unsigned int sid, unsigned int amount, WATCard *card );
    };  // Args struct

    // marshalled arguments and return future
    struct Job {
        Args              args;    // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;  // return future
        Job( Args args );
    };  // Job struct

    std::queue< Job * >      jobQueue;      // jobs available for the couriers
    std::vector< WATCard * > createdCards;  // cards that the WATCardOffice has created, needs to
                                            // be dynamically allocated because we can't copy WATCard

    // communicates with bank
    _Task Courier {
        Printer &      prt;         // to print
        Bank &         bank;        // to withdraw
        WATCardOffice &cardOffice;  // to requestWork
        unsigned int   id;          // local identifier of a Courier

        void main();

       public:
        Courier( Printer & prt, Bank & bank, WATCardOffice & cardOffice, unsigned int id );
    };  // Courier Task

    Courier **couriers;  // a fixed-size courier pool

    void main();

   public:
    _Event Lost{};  // lost WATCard
    WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
    ~WATCardOffice();

    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *             requestWork();
};  // WATCardOffice Task

#endif
