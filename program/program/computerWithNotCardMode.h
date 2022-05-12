#pragma once
#define COMPUTERWITHNOTCARD_H_INCLUDED

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

void gotoXYNotCardWithComputer(int x, int y);
void shuffleBooleanCards();
void shuffleAllCards();
void notCardWithComputer(int x, int y);
void printPositionsNotCardWithComputer(int player, bool* isOccupied, int* values);
void notCardWithComputerCheck(int* values, bool* isOccupied, bool* initialCardValues, int playerNum);
void removeCardNotCardWithComputer(int card, int* player);
void takeCardsWithComputer(int cardsNotCardNeeded, int* player);
void chooseCardNotCardWithComputer(int* player, bool returned);
void printCardsWithComputer(int cardsNotCardNeeded, int* player);
void printInitialPositionsWithComputer();
void printInitialCardsWithComputer(int position, bool reverse, int player);
void placeCardNotCardWithComputer(bool* occupiedPositions, int index, int pointerIndex, int x, int y, bool* cardValues, int* cards, int cardValue, bool value, int* playersCards);