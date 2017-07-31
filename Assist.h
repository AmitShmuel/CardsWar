/* Assist.h - Header file which declares some assistance function */
#ifndef ASSIST_H
#define ASSIST_H
#include <stdio.h>
#include "Deck.h"

typedef enum {Quit , Play} Choice;

/* Prints to the screen a menu of two options - play and quit */
Choice PLAYorQUIT();

/* Assists the "Print" fuction by finding the kind of the requested card */
void Get_Kind(card_kind kind);

/* Assists the "Print" fuction by finding the name of the requested card */
void Get_Name(card_name name);

#endif
