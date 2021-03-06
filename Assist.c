#include "Assist.h"


Choice PLAYorQUIT() {
	
	printf("\n		--	C  A  R	D  S	W  A  R      --\n\nWelcome!\n\n");
	int choice;
	do {		
		
		printf("Please choose option:\n\n[1] Start simulation \t [2] Exit\n");			
		choice = getchar();															
		fflush(stdin);															
		if ((choice != 50) && (choice != 49))		// 50, 49 are ASCII values for 1, 2
			printf("Incorrect input\n\n");											
	}																				
	while((choice != 50) && (choice != 49));		
			
	if(choice == 50) {																
																					
		printf("\nGood Bye !\n\n");
		return Quit;
	}
	return Play;
}


void Get_Kind(card_kind kind) {
	
	if (kind == 0)
		printf("Spades");
	else if (kind == 1)
		printf("Clubs");
	else if (kind == 2)
		printf("Diamonds");
	else if (kind == 3)
		printf("Hearts");
}

void Get_Name(card_name name) {
	
	if (name == 2)
		printf("Two");
	else if (name == 3)
		printf("Three");
	else if (name == 4)
		printf("Four");
	else if (name == 5)
		printf("Five");
	else if (name == 6)
		printf("Six");
	else if (name == 7)
		printf("Seven");
	else if (name == 8)
		printf("Eight");
	else if (name == 9)
		printf("Nine");
	else if (name == 10)
		printf("Ten");
	else if (name == 11)
		printf("Jack");
	else if (name == 12)
		printf("Queen");
	else if (name == 13)
		printf("King");
	else if (name == 14)
		printf("Ace");
}
