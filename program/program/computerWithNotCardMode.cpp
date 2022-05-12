#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "program.h"
#include "computerWithNotCardMode.h"

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

HANDLE consoleNotCardWithComputer = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPositionNotCardWithComputer; // used for goto

int allCards[56];
int playerCardsComputerNot[5], computerCardsNotCard[5];
int choosenCard;
int counterNotCardComputerMode;
bool initialCardValuesPlayer[6], initialcardValuesPC[6];
bool valuesPlayer[15], valuesPC[15];
bool occupiedPlayer[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool occupiedPC[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int cardsPlayer[15];
int cardsComputer[15];
int posCoordinatesNotCardWithComputer[15][3] = { {60, 107, 4}, {60, 107, 13}, {60, 107, 22}, {60, 107, 31}, {60, 107, 40},
                          {47, 122, 8}, {47, 122, 18}, {47, 122, 28}, {47, 122, 38},
                          {32, 137, 12}, {32, 137, 23}, {32, 137, 34},
                          {17, 152, 17}, {17, 152, 29},
                          {2, 167}
};

bool isNotCardComputerMode = true;
bool skipTurnPlayer = 0, skipTurnPC = 0;

void gotoXYNotCardWithComputer(int x, int y)
{
    CursorPositionNotCardWithComputer.X = x;
    CursorPositionNotCardWithComputer.Y = y;
    SetConsoleCursorPosition(consoleNotCardWithComputer, CursorPositionNotCardWithComputer);
}

void shuffleBooleanCards()
{
    bool allCards[6];
    int pixelsX = 77;
    int pixelsY = 2;
    srand(time(NULL));
    for (int i = 0; i < 6; i++)
    {
        allCards[i] = rand() % 2;
    }
    for (int i = 0; i < 6; i++)
    {
        if (allCards[i] == 0)
        {
            cardZero(pixelsX, pixelsY);
            cardOne(pixelsX + 15, pixelsY);
            initialCardValuesPlayer[i] = 0;
            initialcardValuesPC[i] = 1;
        }
        else
        {
            cardOne(pixelsX, pixelsY);
            cardZero(pixelsX + 15, pixelsY);
            initialCardValuesPlayer[i] = 1;
            initialcardValuesPC[i] = 0;
        }
        pixelsY += 8;
    }
}

void shuffleAllCards()
{
    for (int i = 0; i < 56; i++)
    {
        allCards[i] = i + 1;
    }
    int temp;
    srand(time(NULL));
    for (int i = 55; i > 0; --i)
    {
        int j = rand() % i;
        temp = allCards[i];
        allCards[i] = allCards[j];
        allCards[j] = temp;
    }
}
//Player one
void playerOne()
{
    
}
//Player two
void playerTwo()
{
    
}

//start the game
void beginningOfTheGameWithTwoPLayersNotCard()
{
    
}