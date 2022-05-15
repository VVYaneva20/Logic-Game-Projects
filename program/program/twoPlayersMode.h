#pragma once
#define TWOPLAYERSMODE_H_INCLUDED

using namespace std;

void printPositions(int player, bool* isOccupied);
void placeCard(bool* occupiedPositions, int index, int pointerIndex, int x, int y, bool* cardValues, bool value, int* playersCards);
void checkCard(int* playersCards, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues);
void executeTurn(int* playerCards, bool* boolCardValues, int player, bool* isOccupied, bool* cardValues);
void beginningOfTheGameWithTwoPLayers();