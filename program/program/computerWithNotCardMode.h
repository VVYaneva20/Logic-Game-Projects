#pragma once
#define COMPUTERWITHNOTCARD_H_INCLUDED

using namespace std;

void printPositionsNotCardWithComputer(int player, bool* isOccupied, int* values);
void notCardWithComputerCheck(int* values, bool* isOccupied, bool* initialCardValues, int playerNum);
void chooseCardNotCardComputer(int* player);
void printInitialCardsWithComputer(int position, bool reverse, int player);
void placeCardNotCardWithComputer(bool* occupiedPositions, int index, int pointerIndex, int x, int y, bool* boolValues, bool value, int* cardValues, int cardValue, int* playersCards);
void checkCardPlayer(int* playerscardsNotCard, bool* initialvalues, int player, bool* occupiedPositions, bool* values, int* cardValues);
void checkCardComputer(int* playersallCards, bool* initialvalues, int player, bool* occupiedPositions, bool* values, int* cardValues);
void playerTurn();
void computerTurn();
void startTheGameWithComputerNotCard();