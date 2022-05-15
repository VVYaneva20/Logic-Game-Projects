#pragma once
#define PROGRAM_H_INCLUDED

//define colors
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
void printCardOrZero(int x, int y);
void printCardAndZero(int x, int y);
void printCardXorZero(int x, int y);
void printCardAndOne(int x, int y);
void printCardOrOne(int x, int y);
void printCardXorOne(int x, int y);
void printInitialCardOne(int x, int y);
void printInitialCardZero(int x, int y);
void printNotCard(int x, int y);
void emptyVariables(int cards);
void printGoodbye();
void showConsoleCursor(bool showFlag);
void shuffleInitialCards();
void shuffleCards(int numberOfCards);
void removeCard(int card, int* player);
void takeCards(int cardsNeeded, int* player, int numberOfCards);
void printCards(int* player);
void printCardsWithNotCard(int* player);
void printTruthTable(int x, int y);
void printPositionsWithNotCard(int player, bool* isOccupied, int* values);
void printInitialPositions();
void chooseCard(int* player, bool returned, bool notCard);
void printInstructions();
void startProgram();