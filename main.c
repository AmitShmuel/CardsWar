#include <stdlib.h>
#include "Deck.h"
#include "Assist.h"

int main() {

	if(PLAYorQUIT() == Quit)
		return 1;
	
	Card Player1 = NULL, Player2 = NULL;
	if (((Player1 = Create(Player1 , 1)) == NULL) || ((Player2 = Create(Player2 , 2)) == NULL))
		return 1;
	
	if ((Shuffle(Player1) == Fail) || (Shuffle(Player2) == Fail) || (Shuffle(Player1) == Fail))
		return 1;
		
	if ((Print(Player1 , 1) == Fail)  || (Print(Player2 , 2) == Fail))
		return 1;
	
	Card Player1_Pot = NULL , Player2_Pot = NULL;
	Winner winner;
	
	do
	{
		if ((winner = OpenCard(Player1 , Player2)) > 0)
			Add_Cards(winner , &Player1 , &Player2 , &Player1_Pot , &Player2_Pot);
			
		else 	
			War(&Player1 , &Player2 , &Player1_Pot , &Player2_Pot);
			
		
		if ((Player1 == NULL) || (Player2 == NULL))
			End_of_Deck(&Player1, &Player2 , &Player1_Pot , &Player2_Pot);											
	}
	while((Player1 != NULL) && (Player2 != NULL));
		
	if (Find_Winner(Player1 , Player2 , Player1_Pot , Player2_Pot) == Fail)
		return 1;
	
	system("PAUSE");
	return 0;
}
