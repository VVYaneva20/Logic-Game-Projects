#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "WithComputer.h"
#include "LogicGame.h"

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

HANDLE consoleComputerMode = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPositionComputerMode; // used for goto

int cardsComputerMode[48];
int playerCards[5], computerCards[5];
int chosenCardComputerMode;
int counterComputerMode;
bool boolCardValuesPlayer[6], boolCardValuesPC[6];
bool cardValuesPlayer[15], cardValuesPC[15];
bool isOccupiedPlayer[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool isOccupiedPC[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//takes coordinates
void gotoXYComputerMode(int x, int y)
{
    CursorPositionComputerMode.X = x;
    CursorPositionComputerMode.Y = y;
    SetConsoleCursorPosition(consoleComputerMode, CursorPositionComputerMode);
}

//reorders bool cards
void shuffleBoolCardsComputerMode()
{
    bool cardsComputerMode[6];
    int pixelsX = 77;
    int pixelsY = 2;

    srand(time(NULL));

    for (int i = 0; i < 6; i++)
    {
        cardsComputerMode[i] = rand() % 2;
    }

    for (int i = 0; i < 6; i++)
    {
        if (cardsComputerMode[i] == 0)
        {
            cardZero(pixelsX, pixelsY);
            cardOne(pixelsX + 15, pixelsY);
            boolCardValuesPlayer[i] = 0;
            boolCardValuesPC[i] = 1;
        }
        else
        {
            cardOne(pixelsX, pixelsY);
            cardZero(pixelsX + 15, pixelsY);
            boolCardValuesPlayer[i] = 1;
            boolCardValuesPC[i] = 0;
        }
        pixelsY += 8;
    }
}
//reorders all cards
void shuffleCardsComputerMode()
{
    for (int i = 0; i < 48; i++)
    {
        cardsComputerMode[i] = i + 1;
    }

    int temp;
    srand(time(NULL));

    for (int i = 47; i > 0; --i)
    {
        int j = rand() % i;
        temp = cardsComputerMode[i];
        cardsComputerMode[i] = cardsComputerMode[j];
        cardsComputerMode[j] = temp;
    }
}

//discard a card
void removeCardComputerMode(int card, int* player)
{
    for (int i = card - 1; i < 5; ++i)
    {
        player[i] = player[i + 1];
    }
}

//the player gets cardsComputerMode
void takeCardsComputerMode(int cardsNeeded, int* player)
{
    if (cardsNeeded != 1)
    {
        for (int i = 0; i < cardsNeeded; i++)
        {
            player[i] = cardsComputerMode[i];
        }
    }
    else
    {
        player[4] = cardsComputerMode[0];
    }

    for (int i = 0; i < cardsNeeded; i++)
    {
        int temp = cardsComputerMode[0];
        for (int j = 0; j < 47; j++)
        {
            cardsComputerMode[j] = cardsComputerMode[j + 1];
        }
        cardsComputerMode[47] = temp;
    }
}

//player selects a card
void chooseCardComputerMode(int* player)
{
    int Set[] = { 12, 7, 7, 7, 7 };
    counterComputerMode = 1;
    char key;

    while (true)
    {
        gotoXYComputerMode(189, 6);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[0]);
        cout << ">";

        gotoXYComputerMode(189, 15);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[1]);
        cout << ">";

        gotoXYComputerMode(189, 24);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[2]);
        cout << ">";

        gotoXYComputerMode(189, 33);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[3]);
        cout << ">";

        gotoXYComputerMode(189, 44);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[4]);
        cout << ">";

        key = _getch();

        if (key == 72) // up arrow key
        {
            if (counterComputerMode == 1)
            {
                counterComputerMode = 5;
            }
            else
            {
                counterComputerMode--;
            }
        }
        if (key == 80) // down arrow key
        {
            if (counterComputerMode == 5)
            {
                counterComputerMode = 1;
            }
            else
            {
                counterComputerMode++;
            }
        }
        if (key == 's')// select card
        {
            if (counterComputerMode == 1)
            {
                chosenCardComputerMode = player[0];
                break;
            }
            if (counterComputerMode == 2)
            {
                chosenCardComputerMode = player[1];
                break;
            }
            if (counterComputerMode == 3)
            {
                chosenCardComputerMode = player[2];
                break;
            }
            if (counterComputerMode == 4)
            {
                chosenCardComputerMode = player[3];
                break;
            }
            if (counterComputerMode == 5)
            {
                chosenCardComputerMode = player[4];
                break;
            }
        }
        if (key == 27)// esc key ASCII value
        {
            startProgram();
            break;
        }

        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;

        if (counterComputerMode == 1)
        {
            Set[0] = 12;
        }
        if (counterComputerMode == 2)
        {
            Set[1] = 12;
        }
        if (counterComputerMode == 3)
        {
            Set[2] = 12;
        }
        if (counterComputerMode == 4)
        {
            Set[3] = 12;
        }
        if (counterComputerMode == 5)
        {
            Set[4] = 12;
        }
    }

    Sleep(150);
}

//computer selects a card
void chooseCardComputer(int* player)
{
    if (counterComputerMode == 1)
    {
        chosenCardComputerMode = player[0];
    }
    if (counterComputerMode == 2)
    {
        chosenCardComputerMode = player[1];
    }
    if (counterComputerMode == 3)
    {
        chosenCardComputerMode = player[2];
    }
    if (counterComputerMode == 4)
    {
        chosenCardComputerMode = player[3];
    }
    if (counterComputerMode == 5)
    {
        chosenCardComputerMode = player[4];
    }
    if (counterComputerMode == 6)
    {
        chosenCardComputerMode = player[rand() % 4];
    }
}

//display cards 
void printCardsComputerMode(int cardsComputerModeNeeded, int* player)
{
    int cardcounterComputerMode = 0;
    int pixelsX = 191;
    int pixelsY = 2;
    
    gotoXYComputerMode(30, 3); cout << YELLOW << "Player 1's side" << RESET;
    gotoXYComputerMode(139, 3); cout << YELLOW << "Computer's side" << RESET;

    for (int i = 0; i < 52; i++)
    {
        gotoXYComputerMode(187, i); cout << "|";
    }
    for (int i = 0; i < 5; i++)
    {
        if (player[i] % 6 == 1)
        {
            cardOrZero(pixelsX, pixelsY);
        }
        else if (player[i] % 6 == 2)
        {
            cardXorZero(pixelsX, pixelsY);
        }
        else if (player[i] % 6 == 3)
        {
            cardAndZero(pixelsX, pixelsY);
        }
        else if (player[i] % 6 == 4)
        {
            cardOrOne(pixelsX, pixelsY);
        }
        else if (player[i] % 6 == 5)
        {
            cardXorOne(pixelsX, pixelsY);
        }
        else if (player[i] % 6 == 0)
        {
            cardAndOne(pixelsX, pixelsY);
        }
        cardcounterComputerMode++;
        pixelsY += 9;
        if (cardcounterComputerMode == 4)
        {
            pixelsY += 2;
        }
    }
}
//display the empty positions
void printPositionsComputerMode()
{
    int posCoordinates[15][3] = { {60, 107, 4}, {60, 107, 13}, {60, 107, 22}, {60, 107, 31}, {60, 107, 40},
                              {47, 122, 8}, {47, 122, 18}, {47, 122, 28}, {47, 122, 38},
                              {32, 137, 12}, {32, 137, 23}, {32, 137, 34},
                              {17, 152, 17}, {17, 152, 29},
                              {2, 167, 23}
    };

    int xP1, xPC, y;

    for (int i = 0; i < 5; i++)
    {
        y = posCoordinates[i][2];

        if (!isOccupiedPlayer[i])
        {
            gotoXYComputerMode(60, y++); cout << " _______________" << endl;
            gotoXYComputerMode(60, y++); cout << "|    POSITION   |" << endl;
            gotoXYComputerMode(60, y++); cout << "|               |" << endl;
            gotoXYComputerMode(60, y++); cout << "|               |" << endl;
            gotoXYComputerMode(60, y++); cout << "|       " << i + 1 << "       |" << endl;
            gotoXYComputerMode(60, y++); cout << "|               |" << endl;
            gotoXYComputerMode(60, y++); cout << "|               |" << endl;
            gotoXYComputerMode(60, y++); cout << "|               |" << endl;
            gotoXYComputerMode(60, y++); cout << "|_______________|" << endl;
        }

        y = posCoordinates[i][2];

        if (!isOccupiedPC[i])
        {
            gotoXYComputerMode(107, y++); cout << " _______________" << endl;
            gotoXYComputerMode(107, y++); cout << "|    POSITION   |" << endl;
            gotoXYComputerMode(107, y++); cout << "|               |" << endl;
            gotoXYComputerMode(107, y++); cout << "|               |" << endl;
            gotoXYComputerMode(107, y++); cout << "|       " << i + 1 << "       |" << endl;
            gotoXYComputerMode(107, y++); cout << "|               |" << endl;
            gotoXYComputerMode(107, y++); cout << "|               |" << endl;
            gotoXYComputerMode(107, y++); cout << "|               |" << endl;
            gotoXYComputerMode(107, y++); cout << "|_______________|" << endl;
        }
    }

    int inColumn = 4;
    int posP1 = 6, posPC = 6;

    for (int i = 5; i < 15; i++)
    {
        xP1 = posCoordinates[i][0];
        xPC = posCoordinates[i][1];
        y = posCoordinates[i][2];

        if (i == 9)
        {
            posP1 = 1;
            posPC = 1;
        }

        if (isOccupiedPlayer[i - inColumn] and isOccupiedPlayer[i - inColumn - 1] and (!isOccupiedPlayer[i]))
        {
            gotoXYComputerMode(xP1, y++); cout << " _______________" << endl;
            gotoXYComputerMode(xP1, y++); cout << "|    POSITION   |" << endl;
            gotoXYComputerMode(xP1, y++); cout << "|               |" << endl;
            gotoXYComputerMode(xP1, y++); cout << "|               |" << endl;
            gotoXYComputerMode(xP1, y++); cout << "|       " << posP1 << "       |" << endl;
            gotoXYComputerMode(xP1, y++); cout << "|               |" << endl;
            gotoXYComputerMode(xP1, y++); cout << "|               |" << endl;
            gotoXYComputerMode(xP1, y++); cout << "|               |" << endl;
            gotoXYComputerMode(xP1, y++); cout << "|_______________|" << endl;
        }

        y = posCoordinates[i][2];

        if (isOccupiedPC[i - inColumn] and isOccupiedPC[i - inColumn - 1] and (!isOccupiedPC[i]))
        {
            gotoXYComputerMode(xPC, y++); cout << " _______________" << endl;
            gotoXYComputerMode(xPC, y++); cout << "|    POSITION   |" << endl;
            gotoXYComputerMode(xPC, y++); cout << "|               |" << endl;
            gotoXYComputerMode(xPC, y++); cout << "|               |" << endl;
            gotoXYComputerMode(xPC, y++); cout << "|       " << posPC << "       |" << endl;
            gotoXYComputerMode(xPC, y++); cout << "|               |" << endl;
            gotoXYComputerMode(xPC, y++); cout << "|               |" << endl;
            gotoXYComputerMode(xPC, y++); cout << "|               |" << endl;
            gotoXYComputerMode(xPC, y++); cout << "|_______________|" << endl;
        }

        posP1++; posPC++;

        if (i == 8 or i == 11 or i == 13)
        {
            inColumn--;
        }
    }
}
//put down a card in a chosen position
void placeCardComputerMode(int* playerscardsComputerMode, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues)
{
    int pixelsX;
    int pixelsY;

    int asciiValue;
    char keyPress;

    while (true)
    {
        keyPress = _getch();
        asciiValue = keyPress - 48;
        
        if (asciiValue == 66 && player == 1)// 'r' ASCII value
        {
            gotoXYComputerMode(195, 50); cout << "PLAYER " << player << "  ";

            chooseCardComputerMode(playerscardsComputerMode);
            placeCardComputerMode(playerscardsComputerMode, boolCardValues, 1, occupiedPositions, cardValues);

            break;
        }
        if (asciiValue == 52)// 'd' ASCII value
        {
            removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
            break;
        }
        if (asciiValue == 27)// esc ASCII value
        {
            startProgram();
            break;
        }

        if (asciiValue == 1) // '1' ASCII code
        {
            if (occupiedPositions[0] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 60;
                }
                else
                {
                    pixelsX = 107;
                }
                pixelsY = 4;
                if (chosenCardComputerMode % 6 == 1 && !(boolCardValues[0] || boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(boolCardValues[0] ^ boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(boolCardValues[0] && boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (boolCardValues[0] || boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (boolCardValues[0] ^ boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (boolCardValues[0] && boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;

                    continue;
                }
            }
            else if (occupiedPositions[9] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 32;
                }
                else
                {
                    pixelsX = 137;
                }
                pixelsY = 12;
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[5] || cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[5] ^ cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[5] && cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[5] || cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[5] ^ cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[5] && cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
            }
        }
        else if (asciiValue == 2)  // '2' ASCII code
        {
            if (occupiedPositions[1] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 60;
                }
                else
                {
                    pixelsX = 107;
                }
                pixelsY = 13;
                if (chosenCardComputerMode % 6 == 1 && !(boolCardValues[1] || boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(boolCardValues[1] ^ boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(boolCardValues[1] && boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (boolCardValues[1] || boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (boolCardValues[1] ^ boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (boolCardValues[1] && boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else if (occupiedPositions[10] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 32;
                }
                else
                {
                    pixelsX = 137;
                }
                pixelsY = 23;
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[6] || cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[6] ^ cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[6] && cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[6] || cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[6] ^ cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[6] && cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
            }
        }
        else if (asciiValue == 3) // '3' ASCII code
        {
            if (occupiedPositions[2] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 60;
                }
                else
                {
                    pixelsX = 107;
                }
                pixelsY = 22;
                if (chosenCardComputerMode % 6 == 1 && !(boolCardValues[2] || boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(boolCardValues[2] ^ boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(boolCardValues[2] && boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (boolCardValues[2] || boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (boolCardValues[2] ^ boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (boolCardValues[2] && boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else if (occupiedPositions[11] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 32;
                }
                else
                {
                    pixelsX = 137;
                }
                pixelsY = 34;
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[7] || cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[7] ^ cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[7] && cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[7] || cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[7] ^ cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[7] && cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                ;
            }
        }
        else if (asciiValue == 4) // '4' ASCII code
        {
            if (occupiedPositions[3] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 60;
                }
                else
                {
                    pixelsX = 107;
                }
                pixelsY = 31;
                if (chosenCardComputerMode % 6 == 1 && !(boolCardValues[3] || boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(boolCardValues[3] ^ boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(boolCardValues[3] && boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (boolCardValues[3] || boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (boolCardValues[3] ^ boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (boolCardValues[3] && boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else if (occupiedPositions[12] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 17;
                }
                else
                {
                    pixelsX = 152;
                }
                pixelsY = 17;
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[9] || cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[9] ^ cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[9] && cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[9] || cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[9] ^ cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[9] && cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                ;
            }
        }
        else if (asciiValue == 5) // '5' ASCII code
        {
            if (occupiedPositions[4] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 60;
                }
                else
                {
                    pixelsX = 107;
                }
                pixelsY = 40;
                if (chosenCardComputerMode % 6 == 1 && !(boolCardValues[4] || boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(boolCardValues[4] ^ boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(boolCardValues[4] && boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (boolCardValues[4] || boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (boolCardValues[4] ^ boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (boolCardValues[4] && boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else if (occupiedPositions[13] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 17;
                }
                else
                {
                    pixelsX = 152;
                }
                pixelsY = 29;
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[10] || cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[10] ^ cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[10] && cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[10] || cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[10] ^ cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[10] && cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                ;
            }
        }
        else if (asciiValue == 6) // '6' ASCII code
        {
            if (occupiedPositions[5] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 47;
                }
                else
                {
                    pixelsX = 122;
                }
                pixelsY = 8;
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[0] || cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[0] ^ cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[0] && cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[0] || cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[0] ^ cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[0] && cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else if (occupiedPositions[14] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 2;
                }
                else
                {
                    pixelsX = 167;
                }
                pixelsY = 23;
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[12] || cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[12] ^ cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[12] && cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[12] || cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[12] ^ cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[12] && cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                ;
            }
        }
        if (asciiValue == 7 && occupiedPositions[6] == 0) // '7' ASCII code
        {
            if (player == 1)
            {
                pixelsX = 47;
            }
            else
            {
                pixelsX = 122;
            }
            pixelsY = 18;
            if (chosenCardComputerMode % 6 == 1 && !(cardValues[1] || cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 2 && !(cardValues[1] ^ cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 3 && !(cardValues[1] && cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 4 && (cardValues[1] || cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 5 && (cardValues[1] ^ cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 0 && (cardValues[1] && cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else
            {
                gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                continue;
            }
        }
        else
        {
            gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
        }
        if (asciiValue == 8 && occupiedPositions[7] == 0) // '8' ASCII code
        {
            if (player == 1)
            {
                pixelsX = 47;
            }
            else
            {
                pixelsX = 122;
            }
            pixelsY = 28;
            if (chosenCardComputerMode % 6 == 1 && !(cardValues[2] || cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 2 && !(cardValues[2] ^ cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 3 && !(cardValues[2] && cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 4 && (cardValues[2] || cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 5 && (cardValues[2] ^ cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 0 && (cardValues[2] && cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else
            {
                gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                continue;
            }
        }
        else
        {
            gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
        }
        if (asciiValue == 9 && occupiedPositions[8] == 0) // '9' ASCII code
        {
            if (player == 1)
            {
                pixelsX = 47;
            }
            else
            {
                pixelsX = 122;
            }
            pixelsY = 38;
            if (chosenCardComputerMode % 6 == 1 && !(cardValues[3] || cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 2 && !(cardValues[3] ^ cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 3 && !(cardValues[3] && cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 4 && (cardValues[3] || cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 5 && (cardValues[3] ^ cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 0 && (cardValues[3] && cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else
            {
                gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
                continue;
            }
        }
        else
        {
            gotoXYComputerMode(195, 50); cout << RED << "Invalid!" << RESET;
        }

    }
}

void placeCardComputer(int* playerscardsComputerMode, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues)
{
    int pixelsX;
    int pixelsY;

    int asciiValue = 1;
    
    while (true)
    {
        asciiValue++;

        if (counterComputerMode == 6)
        {
            removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
            break;
        }
        if (asciiValue == 10)
        {
            counterComputerMode++;
            chooseCardComputer(computerCards);
            asciiValue = 1;
        }
        
        if (asciiValue == 1) // '1' ASCII code
        {
            if (occupiedPositions[0] == 0)
            {
                pixelsX = 107;
                pixelsY = 4;

                if (chosenCardComputerMode % 6 == 1 && !(boolCardValues[0] || boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(boolCardValues[0] ^ boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(boolCardValues[0] && boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (boolCardValues[0] || boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (boolCardValues[0] ^ boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (boolCardValues[0] && boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
            else if (occupiedPositions[9] == 0)
            {
                pixelsX = 137;
                pixelsY = 12;
                
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[5] || cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[5] ^ cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[5] && cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[5] || cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[5] ^ cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[5] && cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
        }
        else if (asciiValue == 2)  // '2' ASCII code
        {
            if (occupiedPositions[1] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 60;
                }
                else
                {
                    pixelsX = 107;
                }
                pixelsY = 13;
                if (chosenCardComputerMode % 6 == 1 && !(boolCardValues[1] || boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(boolCardValues[1] ^ boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(boolCardValues[1] && boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (boolCardValues[1] || boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (boolCardValues[1] ^ boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (boolCardValues[1] && boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
            else if (occupiedPositions[10] == 0)
            {
                if (player == 1)
                {
                    pixelsX = 32;
                }
                else
                {
                    pixelsX = 137;
                }
                pixelsY = 23;
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[6] || cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[6] ^ cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[6] && cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[6] || cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[6] ^ cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[6] && cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
        }
        else if (asciiValue == 3) // '3' ASCII code
        {
            if (occupiedPositions[2] == 0)
            {
                pixelsX = 107;
                pixelsY = 22;
                
                if (chosenCardComputerMode % 6 == 1 && !(boolCardValues[2] || boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(boolCardValues[2] ^ boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(boolCardValues[2] && boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (boolCardValues[2] || boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (boolCardValues[2] ^ boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (boolCardValues[2] && boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
            else if (occupiedPositions[11] == 0)
            {
                pixelsX = 137;
                pixelsY = 34;
                
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[7] || cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[7] ^ cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[7] && cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[7] || cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[7] ^ cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[7] && cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
        }
        else if (asciiValue == 4) // '4' ASCII code
        {
            if (occupiedPositions[3] == 0)
            {
                pixelsX = 107;
                pixelsY = 31;
                
                if (chosenCardComputerMode % 6 == 1 && !(boolCardValues[3] || boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(boolCardValues[3] ^ boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(boolCardValues[3] && boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (boolCardValues[3] || boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (boolCardValues[3] ^ boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (boolCardValues[3] && boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
            else if (occupiedPositions[12] == 0)
            {
                pixelsX = 152;
                pixelsY = 17;
                
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[9] || cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[9] ^ cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[9] && cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[9] || cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[9] ^ cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[9] && cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
        }
        else if (asciiValue == 5) // '5' ASCII code
        {
            if (occupiedPositions[4] == 0)
            {
                pixelsX = 107;
                pixelsY = 40;
                
                if (chosenCardComputerMode % 6 == 1 && !(boolCardValues[4] || boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(boolCardValues[4] ^ boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(boolCardValues[4] && boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (boolCardValues[4] || boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (boolCardValues[4] ^ boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (boolCardValues[4] && boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
            else if (occupiedPositions[13] == 0)
            {
                pixelsX = 152;
                pixelsY = 29;
                
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[10] || cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[10] ^ cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[10] && cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[10] || cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[10] ^ cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[10] && cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
        }
        else if (asciiValue == 6) // '6' ASCII code
        {
            if (occupiedPositions[5] == 0)
            {
                pixelsX = 122;
                pixelsY = 8;
                
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[0] || cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[0] ^ cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[0] && cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[0] || cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[0] ^ cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[0] && cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
            else if (occupiedPositions[14] == 0)
            {
                pixelsX = 167;
                pixelsY = 23;
                
                if (chosenCardComputerMode % 6 == 1 && !(cardValues[12] || cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 2 && !(cardValues[12] ^ cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 3 && !(cardValues[12] && cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 4 && (cardValues[12] || cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 5 && (cardValues[12] ^ cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
                else if (chosenCardComputerMode % 6 == 0 && (cardValues[12] && cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                    break;
                }
            }
        }
        if (asciiValue == 7 && occupiedPositions[6] == 0) // '7' ASCII code
        {
            pixelsX = 122;
            pixelsY = 18;
            
            if (chosenCardComputerMode % 6 == 1 && !(cardValues[1] || cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 2 && !(cardValues[1] ^ cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 3 && !(cardValues[1] && cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 4 && (cardValues[1] || cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 5 && (cardValues[1] ^ cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 0 && (cardValues[1] && cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
        }
        if (asciiValue == 8 && occupiedPositions[7] == 0) // '8' ASCII code
        {
            pixelsX = 122;
            pixelsY = 28;
            
            if (chosenCardComputerMode % 6 == 1 && !(cardValues[2] || cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 2 && !(cardValues[2] ^ cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 3 && !(cardValues[2] && cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 4 && (cardValues[2] || cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 5 && (cardValues[2] ^ cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 0 && (cardValues[2] && cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
        }
        if (asciiValue == 9 && occupiedPositions[8] == 0) // '9' ASCII code
        {
            pixelsX = 122;
            pixelsY = 38;
            
            if (chosenCardComputerMode % 6 == 1 && !(cardValues[3] || cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 2 && !(cardValues[3] ^ cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 3 && !(cardValues[3] && cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 4 && (cardValues[3] || cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 5 && (cardValues[3] ^ cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
            else if (chosenCardComputerMode % 6 == 0 && (cardValues[3] && cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCardComputerMode(counterComputerMode, playerscardsComputerMode);
                break;
            }
        }
        
    }
}

//Player
void player()
{
    printCardsComputerMode(5, playerCards);
    chooseCardComputerMode(playerCards);
    placeCardComputerMode(playerCards, boolCardValuesPlayer, 1, isOccupiedPlayer, cardValuesPlayer);
}
//Computer
void computer()
{
    printCardsComputerMode(5, computerCards);
    counterComputerMode = 1;
    chooseCardComputer(computerCards);
    Sleep(2000);
    placeCardComputer(computerCards, boolCardValuesPC, 2, isOccupiedPC, cardValuesPC);
}

//start the game
void beginningOfTheGameWithComputer()
{
    fill_n(cardsComputerMode, 48, 0);
    fill_n(playerCards, 5, 0);
    fill_n(computerCards, 5, 0);
    fill_n(boolCardValuesPlayer, 6, 0);
    fill_n(boolCardValuesPC, 6, 0);
    fill_n(cardValuesPlayer, 15, 0);
    fill_n(cardValuesPC, 15, 0);
    fill_n(isOccupiedPlayer, 15, 0);
    fill_n(isOccupiedPC, 15, 0);
    chosenCardComputerMode = 0;

    shuffleBoolCardsComputerMode();
    shuffleCardsComputerMode();

    takeCardsComputerMode(4, playerCards);
    takeCardsComputerMode(4, computerCards);

    while (true)
    {
        printPositionsComputerMode();
        gotoXYComputerMode(195, 50); cout << "PLAYER 1";
        takeCardsComputerMode(1, playerCards);
        player();

        printPositionsComputerMode();
        gotoXYComputerMode(195, 50); cout << "COMPUTER";
        takeCardsComputerMode(1, computerCards);
        computer();

        if (isOccupiedPlayer[14] == 1 || isOccupiedPC[14] == 1)
        {
            system("cls");
            break;
        }
    }

    if (isOccupiedPlayer[14] == 1 && isOccupiedPC[14] == 1)
    {
        system("cls");

        gotoXYComputerMode(90, 20); cout << "    ___  __    _  __    __ " << endl;
        gotoXYComputerMode(90, 21); cout << "   /   \\/__\\  /_\\/ / /\\ \\ \\" << endl;
        gotoXYComputerMode(90, 22); cout << "  / /\\ / \\// //_\\\\ \\/  \\/ /" << endl;
        gotoXYComputerMode(90, 23); cout << " / /_// _  \\/  _  \\  /\\  / " << endl;
        gotoXYComputerMode(90, 24); cout << "/___,'\\/ \\_/\\_/ \\_/\\/  \\/" << endl;
        Sleep(3000);
        startProgram();
    }
    else if (isOccupiedPlayer[14] == 1)
    {
        system("cls");

        gotoXYComputerMode(73, 20); cout << "   ___  __    _         __  __    _    __    __ _____    __  __" << endl;
        gotoXYComputerMode(73, 21); cout << "  / _ \\/ /   /_\\ /\\_/\\ /__\\/__\\  / |  / / /\\ \\ \\\\_   \\/\\ \\ \\/ _\\" << endl;
        gotoXYComputerMode(73, 22); cout << " / /_)/ /   //_\\\\\\_ _//_\\ / \\//  | |  \\ \\/  \\/ / / /\\/  \\/ /\\ \\" << endl;
        gotoXYComputerMode(73, 23); cout << "/ ___/ /___/  _  \\/ \\//__/ _  \\  | |   \\  /\\  /\\/ /_/ /\\  / _\\ \\" << endl;
        gotoXYComputerMode(73, 24); cout << "\\/   \\____/\\_/ \\_/\\_/\\__/\\/ \\_/  |_|    \\/  \\/\\____/\\_\\ \\/  \\__/" << endl;
        Sleep(3000);
        startProgram();
    }
    else if (isOccupiedPC[14] == 1)
    {
        system("cls");

        gotoXYComputerMode(70, 20); cout << "   ___  __    _         __  __    ____     __    __ _____    __  __ " << endl;
        gotoXYComputerMode(70, 21); cout << "  / _ \\/ /   /_\\ /\\_/\\ /__\\/__\\  |___ \\   / / /\\ \\ \\\\_   \\/\\ \\ \\/ _\\" << endl;
        gotoXYComputerMode(70, 22); cout << " / /_)/ /   //_\\\\\\_ _//_\\ / \\//    __) |  \\ \\/  \\/ / / /\\/  \\/ /\\ \\" << endl;
        gotoXYComputerMode(70, 23); cout << "/ ___/ /___/  _  \\/ \\//__/ _  \\   / __/    \\  /\\  /\\/ /_/ /\\  / _\\ \\" << endl;
        gotoXYComputerMode(70, 24); cout << "\\/   \\____/\\_/ \\_/\\_/\\__/\\/ \\_/  |_____|    \\/  \\/\\____/\\_\\ \\/  \\__/" << endl;
        Sleep(3000);
        startProgram();
    }
}