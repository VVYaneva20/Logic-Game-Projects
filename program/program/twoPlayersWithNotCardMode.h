#pragma once
#define TWOPLAYERSWITHNOTCARD_H_INCLUDED

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

void shuffleBoolCards();
void shuffleCards();
void notCard(int x, int y);
void printPositionsNotCard(int player, bool* isOccupied, int* values);
void notCardCheck(int* values, bool* isOccupied, bool* initialCardValues, int playerNum);
void removeCard(int card, int* player);
void takeCards(int cardsNotCardNeeded, int* player);
void chooseCard(int* player, bool returned);
void printcardsNotCard(int cardsNotCardNeeded, int* player);
void printInitialPositions();
void printInitialCards(int position, bool reverse, int player);
void placeCardNotCard(bool* occupiedPositions, int index, int pointerIndex, int x, int y, bool* boolValues, bool value, int* cardValues, int cardValue, int* playersCards);
void checkCardNotCard(int* playersCards, bool* initialValues, int player, bool* occupiedPositions, bool* boolValues, int* cardValues);
void playerOne();
void playerTwo();
void beginningOfTheGameWithTwoPLayersNotCard();
