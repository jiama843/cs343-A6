#include "groupoff.h"

// TODO:
/*

  main:
  - Accept calls from each student to get future giftcard (probably loop)
  - Assign random WATCard to random future gift card w/ value soda cost (loop)
    - likely need to yield randomly
    - Inside this loop, likely have _Accept(destructor), _Else{ assign }

*/

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay )
: prt(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay),
cards(new WATCard::WATCard[numStudents]) {}

void Groupoff::main(){
  for(int i = 0; i < numStudents; i++){
    _Accept(giftCard);
  }

  for(;;){
    _Accept(~Groupoff){
      break;
    }
    _Else{
      yield(groupoffDelay);

      // Choose future watcard that has not yet been assigned
      unsigned int card_no = mprng(fcards.size() - 1);

      // Put real WATCard into random card
      WATCard::WATCard *card = new WATCard();
      card->deposit(sodaCost);
      fcards[i].delivery(card);
      fcards.erase(fcards.begin() + card_no);
    }
  }
}

WATCard::FWATCard Groupoff::giftCard(){
  fcard = WATCard::FWATCard;
  fcards.push_back(fcard);
  return fcard;
}