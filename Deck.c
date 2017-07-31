#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Deck.h"
#include "Assist.h"


struct Card_t {
	
	card_name name;
	card_kind kind;
	struct Card_t *Next;
	
};

Card Create(Card Head, short PlayerNumber) {	/* Player one is getting the black half of the deck, player two getting the red half */
	
	int i, j, k = 0;
	if (PlayerNumber == 2)
		k = 2;
	for(i = 0, j = 2; i < Deck_Size/2; i++, j++)
    {
    	Card New_Card = (Card)malloc(sizeof(struct Card_t));
    	if (New_Card == NULL)
    	{
    		printf("Allocation Error!\n\n");
			return Fail;	
		}
    	New_Card->kind = k;
    	New_Card->name = j;
    	if (j == 14)	// when j = 14 : Two - Ace are dealt
		{
			j = 1;	// will be incremented to "Two" at the start of the second loop
			k++;	// second kind
		}	
        New_Card->Next = Head;
        Head = New_Card;
    }
    return Head;
}


Result Shuffle(Card Head) {
    
    srand(time(NULL));	// Changes the seed
    
    Card tempHead = Head;
    int counter = 0;
    while(tempHead != NULL)	// counts num of cards in order to put upper bound to rand() later (num of cards not always 26 - shuffle being made also when player takes his pot) 
    {
        tempHead = tempHead->Next;
        counter++;
    }
        	  
    struct Card_t temp;
    tempHead = Head;
    int end, i;
    
    while(tempHead != NULL)		
    {	
    	end = (rand() % counter-2) +1;	// end will be the upper bound in the for loop
      
        for(i = 0; i < end; i++) {		
		
        	tempHead = tempHead->Next;	// Advancing with temphead to later compare its values with the original head - creating the shuffle
    	}
        	
        temp = *Head;					// only values are being assigned , not Next
        Head->name = tempHead->name;
        Head->kind = tempHead->kind;
        tempHead->name = temp.name;
        tempHead->kind = temp.kind;
        tempHead = Head->Next;	// tempHead moving to the second card and so on..
        Head = Head->Next;
        counter--;
    }

    if (tempHead == NULL)
    	return Success;
    	
    printf("Shuffling Error!\n\n");
    return Fail;
}


Winner OpenCard(Card Headplayer1 , Card Headplayer2) {	// name also used as value (enum)
	
	if (Headplayer1->name > Headplayer2->name)
		return playerOne;
	if (Headplayer1->name < Headplayer2->name)
		return playerTwo;
	return 0; // in main - if returned value < 0 there's a call to "Add_Cards" , else "War" is being called
}


void Add_Cards(Winner winner , Card* Head1 , Card* Head2 , Card* HeadPot1 , Card* HeadPot2) {	// connecting the opened cards with the winning pot's head
	
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

void War(Card* Head1 , Card* Head2 , Card* HeadPot1 , Card* HeadPot2) {
	
	int quit_loop, counter1 = 0, counter2 = 0, i;	
	Card war1 = *Head1;		// Creating two temp pointers that will advance through the cards that need to be opened in the war 	
	Card war2 = *Head2;	
	Card tmp;
	
	do{
	
		quit_loop = 1;
		while( ( (war1->Next != NULL) && (war2->Next != NULL) ) && (counter1 != 4) ) 
		{
			war1 = war1->Next;	// pointers advance 3 cards face down, and one more face up
			war2 = war2->Next;	// in case player reached his final card, pointer cease to advance 
			counter1++;
		}
		counter2 += counter1;
		
		if(war1->name > war2->name)		// Player 1 wins the war!
		{									// adding and removing the number of cards the pointer has advanced
			for(i = 0; i <= counter2; i++)
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
		}
			
		else if(war1->name < war2->name) 	// Player 2 wins the war!
		{										// adding and removing the number of cards the pointer has advance
			for(i = 0; i <= counter2; i++)
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
	
		else // another war
		{
			if((war1->Next == NULL) || (war2->Next == NULL))	// if next card is the end of the list, another war cant be placed - each player retrieves his war cards
			{
				for(i = 0; i <= counter2; i++)	
				{
					tmp = *Head1;
					*Head1 = (*Head1)->Next;
					tmp->Next = *HeadPot1;
					*HeadPot1 = tmp;
					
					tmp = *Head2;
					*Head2 = (*Head2)->Next;
					tmp->Next = *HeadPot2;
					*HeadPot2 = tmp;
				}
			}
		
			else
			{
				quit_loop = 0;	// creating another loop
				counter1 = 0;
			}
		}
	}
	while(quit_loop == 0);
}


void End_of_Deck(Card* Head1, Card* Head2 , Card* HeadPot1 , Card* HeadPot2) {	// player take his pot and uses it as his new deck
	
	if(*Head1 == NULL)
	{
		Shuffle(*HeadPot1);		           							
   		*Head1 = *HeadPot1;  		     
		*HeadPot1 = NULL;
	}
	
	if(*Head2 == NULL)
	{
		Shuffle(*HeadPot2);		           							
   		*Head2 = *HeadPot2;  		     
		*HeadPot2 = NULL;
	}
}

Result Find_Winner(Card Head1 , Card Head2 , Card HeadPot1 , Card HeadPot2) {
	
	if (Head1 == NULL) {
		printf("\n\n\n\t\t*****PLAYER TWO WINS*****\n\n"); 
		Print(Head2 , 2); Print(HeadPot2 , 0);
		
		if ((FreeList(Head2)) || (FreeList(HeadPot2)) == Fail)		
			return Fail;
		return Success;
	}		
		
	else {
		printf("\n\n\n\t\t*****PLAYER ONE WINS*****\n\n"); 
		Print(Head1 , 1); Print(HeadPot1 , 0);
		
		if ((FreeList(Head1)) || (FreeList(HeadPot1)) == Fail)
			return Fail;
		return Success;
	}
	
	printf("Error finding winner!\n\n");
	return Fail;
}


Result Print(Card Head , short PlayerNum) {
	
	if (PlayerNum == 1)
		printf("\nPLAYER ONE'S CARDS\n\n");
	else if (PlayerNum == 2)
		printf("\nPLAYER TWO'S CARDS\n\n");
		
	int counter = 0;
	while (Head != NULL)
	{
		printf("[%d] \t ", counter); Get_Name(Head->name); printf(" of "); Get_Kind(Head->kind); printf("\n");
		Head = Head->Next;
		counter++;
	}
	if (Head == NULL)
		return Success;
	printf("Printing Error!\n\n");
	return Fail;
}

Result FreeList(Card Head) {
	
	Card to_free;
	while (Head != NULL)
	{
		to_free = Head;
		Head = Head->Next;
		free(to_free);
	}
	if (Head == NULL)
		return Success;
	
	printf("Error freeing the list!\n\n");
	return Fail;
}

