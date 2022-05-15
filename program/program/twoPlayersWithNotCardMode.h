#pragma once
#define TWOPLAYERSWITHNOTCARD_H_INCLUDED

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

void printPositionsNotCard(int player, bool* isOccupied, int* values);
void notCardCheck(int* values, bool* isOccupied, bool* initialCardValues, int playerNum);
void printInitialCards(int position, bool reverse, int player);
void checkCardNotCard(int* playerscardsNotCard, bool* initialvalues, int player, bool* occupiedPositions, bool* values, int* cardValues);
void playerOne();
void playerTwo();
void beginningOfTheGameWithTwoPLayersNotCard();