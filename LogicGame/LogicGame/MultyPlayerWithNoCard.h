#pragma once
#define MULTYPLAYERWITHNOCARD_H_INCLUDED

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[1m\033[33m" 


void gotoXYNotCard(int x, int y);
void shuffleBoolcardsNotCard();
void shufflecardsNotCard();
void removeCardNotCard(int card, int* player);
void takecardsNotCard(int cardsNotCardNeeded, int* player);
void chooseCardNotCard(int* player);
void printcardsNotCard(int cardsNotCardNeeded, int* player);
void printPositionsNotCard();
void printInitialPositions();
void placeCardNotCard(int* playerscardsNotCard, bool* initialvalues, int player, bool* occupiedPositions, bool* values);
void playerOne();
void playerTwo();
void beginningOfTheGameWithTwoPLayersNotCard();