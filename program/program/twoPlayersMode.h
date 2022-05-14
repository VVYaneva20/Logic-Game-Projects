#pragma once
#define TWOPLAYERSMODE_H_INCLUDED

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[1m\033[33m" 

void gotoXY(int x, int y);
void shuffleBoolCards();
void shuffleCards();
void removeCard(int card, int* player);
void takeCards(int cardsNeeded, int* player);
void chooseCard(int* player, bool returned);
void printCards(int cardsNeeded, int* player);
void printPositions(int player, bool* isOccupied);
void placeCard(bool* occupiedPositions, int index, int pointerIndex, int x, int y, bool* cardValues, bool value, int* playersCards);
void executeTurn(int* playerCards, bool* boolCardValues, int player, bool* isOccupied, bool* cardValues);
void beginningOfTheGameWithTwoPLayers();
