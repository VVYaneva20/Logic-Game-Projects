#pragma once
#define COMPUTERWITHNOTCARD_H_INCLUDED

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

void printPositionsNotCardWithComputer(int player, bool* isOccupied, int* values);
void notCardWithComputerCheck(int* values, bool* isOccupied, bool* initialCardValues, int playerNum);
void chooseCardNotCardComputer(int* player);
void printInitialCardsWithComputer(int position, bool reverse, int player);
void placeCardNotCardWithComputer(bool* occupiedPositions, int index, int pointerIndex, int x, int y, bool* boolValues, bool value, int* cardValues, int cardValue, int* playersCards);
void checkCardNotCardWithComputer(int* playerscardsNotCard, bool* initialvalues, int player, bool* occupiedPositions, bool* values, int* cardValues);
void checkCardComputer(int* playersallCards, bool* initialvalues, int player, bool* occupiedPositions, bool* values, int* cardValues);
void playerTurn();
void computerTurn();
void beginningOfTheGameWithComputerNotCard();