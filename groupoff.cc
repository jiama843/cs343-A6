#include "groupoff.h"

// TODO:
/*

  main:
  - Accept calls from each student to get future giftcard (probably loop)
  - Assign random WATCard to random future gift card w/ value soda cost (loop)
    - likely need to yield randomly
    - Inside this loop, likely have _Accept(destructor), _Else{ assign }

*/

Groupoff::Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay )
    : prt( prt ), numStudents( numStudents ), sodaCost( sodaCost ), groupoffDelay( groupoffDelay ) {}

Groupoff::~Groupoff() {
    for ( unsigned int i = 0; i < cardlist.size(); i++ ) {
        delete cardlist[i];
    }  // for
}  // Groupoff::~Groupoff

void Groupoff::main() {
    prt.print( Printer::Kind::Groupoff, 'S' );
    for ( unsigned int i = 0; i < numStudents; i++ ) {
        _Accept( giftCard );
    }  // for

    for ( ;; ) {
        _Accept( ~Groupoff ) {
            break;
        }
        _Else {
            if ( fcards.empty() ) break;

            yield( groupoffDelay );

            // Choose future watcard that has not yet been assigned
            unsigned int card_no = mprng( fcards.size() - 1 );

            prt.print( Printer::Kind::Groupoff, 'D', sodaCost );

            // Put real WATCard into random card
            WATCard *card = new WATCard();
            card->deposit( sodaCost );
            cardlist.push_back( card );

            fcards[card_no].delivery( card );
            fcards.erase( fcards.begin() + card_no );
        }  // _Accept

    }  // for

    prt.print( Printer::Kind::Groupoff, 'F' );
}  // Groupoff::main

WATCard::FWATCard Groupoff::giftCard() {
    WATCard::FWATCard fcard;
    fcards.push_back( fcard );
    return fcard;
}  // Groupoff::giftcard