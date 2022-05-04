#pragma once
#define MULTYPLAYER_H_INCLUDED

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[1m\033[33m" 

void gotoXY(int x, int y);
void shuffleBoolCards();
void shuffleCards();
void removeCard(int card, int* player);
void takeCards(int cardsNeeded, int* player);
void chooseCard(int* player);
void printCards(int cardsNeeded, int* player);
void printPositions();
void placeCard(int* playersCards, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues);
void firstPlayer();
void secondPlayer();
void beginningOfTheGameWithTwoPLayers();