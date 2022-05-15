#pragma once
#define TWOPLAYERSWITHNOTCARD_H_INCLUDED

using namespace std;

void printPositionsNotCardMode(int player, bool* isOccupied, int* values);
void notCardCheck(int* values, bool* isOccupied, bool* initialCardValues, int playerNum);
void printInitialCards(int position, bool reverse, int player);
void checkCardNotCard(int* playerscardsNotCard, bool* initialvalues, int player, bool* occupiedPositions, bool* values, int* cardValues);
void playerOne();
void playerTwo();
void startTheGameWithTwoPLayersNotCard();