#pragma once
#define TWOPLAYERSMODE_H_INCLUDED

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[1m\033[33m" 

void printPositions(int player, bool* isOccupied);
void placeCard(bool* occupiedPositions, int index, int pointerIndex, int x, int y, bool* cardValues, bool value, int* playersCards);
void checkCard(int* playersCards, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues);
void executeTurn(int* playerCards, bool* boolCardValues, int player, bool* isOccupied, bool* cardValues);
void beginningOfTheGameWithTwoPLayers();