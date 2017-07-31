#include <stdio.h>
#include <stdlib.h>
#include "Deck.h"
#include "InGame.h"


struct Card_t {
	
	card_name name;
	card_kind kind;
	struct Card_t *Next;
	
};

Winner OpenCard(Card Headplayer1 , Card Headplayer2) {
	
	if (Headplayer1->name > Headplayer2->name)
		return playerOne;
	if (Headplayer1->name < Headplayer2->name)
		return playerTwo;
	return 0;
}


void Add_Cards(Winner winner , Card* Head1 , Card* Head2 , Card* HeadPot1 , Card* HeadPot2) {
	
	Card tmp = NULL;
	if (winner == 1)
	{
		tmp = *Head2;
		*Head2 = (*Head2)->Next;
		tmp->Next = *HeadPot1;
		*HeadPot1 = tmp;
		
		tmp = *Head1;
		*Head1 = (*Head1)->Next;
		tmp->Next = *HeadPot1;
		*HeadPot1 = tmp;	
	}
	
	else
	{
		tmp = *Head1;
		*Head1 = (*Head1)->Next;
		tmp->Next = *HeadPot2;
		*HeadPot2 = tmp;
		
		tmp = *Head2;
		*Head2 = (*Head2)->Next;
		tmp->Next = *HeadPot2;
		*HeadPot2 = tmp;
	}
}


