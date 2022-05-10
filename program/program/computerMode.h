#pragma once
#define COMPUTERMODE_H_INCLUDED

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[1m\033[33m" 

void gotoXYComputerMode(int x, int y);
void shuffleBoolCardsComputerMode();
void shuffleCardsComputerMode();
void removeCardComputerMode(int card, int* player);
void takeCardsComputerMode(int cardsNeeded, int* player);
void chooseCardComputerMode(int* player);
void printCardsComputerMode(int cardsNeeded, int* player);
void printPositionsComputerMode();
void placeCardComputerMode(int* playersCards, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues);
void player();
void computer();
void beginningOfTheGameWithComputer();