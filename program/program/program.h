#pragma once
#define PROGRAM_H_INCLUDED

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

extern int cards[48], cardsWithNotCard[56];
extern int playerOneCards[5], playerTwoCards[5];
extern int chosenCard;
extern int counter;
extern bool boolCardValuesP1[6], boolCardValuesP2[6];
extern bool cardValuesP1[15], cardValuesP2[15];
extern bool isOccupiedP1[15], isOccupiedP2[15];

void gotoXY(int x, int y);
void cardOrZero(int x, int y);
void cardAndZero(int x, int y);
void cardXorZero(int x, int y);
void cardAndOne(int x, int y);
void cardOrOne(int x, int y);
void cardXorOne(int x, int y);
void cardOne(int x, int y);
void cardZero(int x, int y);
void notCard(int x, int y);
void ShowConsoleCursor(bool showFlag);
void shuffleBoolCards();
void shuffleCards(int numberOfCards);
void removeCard(int card, int* player);
void takeCards(int cardsNeeded, int* player, int numberOfCards);
void chooseCard(int* player, bool returned);
void instructions();
void startProgram();