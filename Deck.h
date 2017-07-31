/* Deck.h - Deck ADT Module header file
   This module defines a pointer to deck type and declares some data manipulation functions
   The deck is implemented as a linked list */
   
#ifndef DECK_H
#define DECK_H
#define Deck_Size 52


typedef struct Card_t* Card;

typedef enum {Fail , Success} Result;

typedef enum {playerOne = 1 , playerTwo} Winner;

/* Name of the cards, also used as value */
typedef enum {
	
	Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace
	
}card_name;

/* Kind of the cards */
typedef enum {
	
	Spades, Clubs, Diamonds, Hearts
	
}card_kind;

/* Creates a player by allocating 26 cards' lined list, Returned value is a pointer to head of the list */
Card Create(Card Head , short PlayerNumber);

/* Shuffles the list, shuffling the two players a different number of times is recommended (Ex: player one - one shuffle. player two - two shuffles) */ 
Result Shuffle(Card Head);

/* Prints the list */
Result Print(Card Head , short PlayerNum);

/* Compares two players' first card, Returned value is the player with the higher card value */
Winner OpenCard(Card Headplayer1 , Card Headplayer2);

/* Adds both winner and loser opened cards from their decks to the winner's pot, using ptr to ptr is necessary - three list heads are being changed */
void Add_Cards(Winner winner , Card* Head1 , Card* Head2 , Card* HeadPot1 , Card* HeadPot2);

/* In case same cards had been opened - players are to open 3 cards face down and another face up - which will determine the winner of the war */
void War(Card* Head1 , Card* Head2 , Card* HeadPot1 , Card* HeadPot2);

/* In case player has reached the end of his deck, he takes his pot and uses it as his new deck (Shuffle of the pot is made inside the function) */
void End_of_Deck(Card* Head1, Card* Head2 , Card* HeadPot1 , Card* HeadPot2);

/* Finds the winner, Declares his name to the screen and prints his cards */
Result Find_Winner(Card Head1 , Card Head2 , Card HeadPot1 , Card HeadPot2);

/* Frees the list from memory*/
Result FreeList(Card Head);

#endif
