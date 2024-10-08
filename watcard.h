#ifndef WATCARD_H
#define WATCARD_H

#include <uFuture.h>

class WATCard {
    unsigned int balance;

    WATCard( const WATCard & ) = delete;  // prevent copying
    WATCard &operator=( const WATCard & ) = delete;

   public:
    typedef Future_ISM< WATCard * > FWATCard;  // future watcard pointer
    WATCard();

    void         deposit( unsigned int amount );
    void         withdraw( unsigned int amount );
    unsigned int getBalance();
};

#endif