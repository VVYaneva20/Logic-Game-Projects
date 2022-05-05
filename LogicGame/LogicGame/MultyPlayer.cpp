#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "MultyPlayer.h"
#include "LogicGame.h"

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition; // used for goto

int cards[48];
int playerOneCards[5], playerTwoCards[5];
int chosenCard;
int counter;
bool boolCardValuesP1[6], boolCardValuesP2[6];
bool cardValuesP1[15], cardValuesP2[15];
bool isOccupiedP1[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool isOccupiedP2[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//takes coordinates
void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

//reorders all cards
void shuffleBoolCards()
{
    bool cards[6];
    int pixelsX = 77;
    int pixelsY = 2;

    srand(time(NULL));

    for (int i = 0; i < 6; i++)
    {
        cards[i] = rand() % 2;
    }

    for (int i = 0; i < 6; i++)
    {
        if (cards[i] == 0)
        {
            cardZero(pixelsX, pixelsY);
            cardOne(pixelsX + 15, pixelsY);
            boolCardValuesP1[i] = 0;
            boolCardValuesP2[i] = 1;
        }
        else
        {
            cardOne(pixelsX, pixelsY);
            cardZero(pixelsX + 15, pixelsY);
            boolCardValuesP1[i] = 1;
            boolCardValuesP2[i] = 0;
        }
        pixelsY += 8;
    }
}
//reorders bool cards
void shuffleCards()
{
    for (int i = 0; i < 48; i++)
    {
        cards[i] = i + 1;
    }

    int temp;
    srand(time(NULL));

    for (int i = 47; i > 0; --i)
    {
        int j = rand() % i;
        temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

//discard a card
void removeCard(int card, int* player)
{
    for (int i = card - 1; i < 5; ++i)
    {
        player[i] = player[i + 1];
    }
}
//the player gets cards
void takeCards(int cardsNeeded, int* player)
{
    if (cardsNeeded != 1)
    {
        for (int i = 0; i < cardsNeeded; i++)
        {
            player[i] = cards[i];
        }
    }
    else
    {
        player[4] = cards[0];
    }

    for (int i = 0; i < cardsNeeded; i++)
    {
        int temp = cards[0];
        for (int j = 0; j < 47; j++)
        {
            cards[j] = cards[j + 1];
        }
        cards[47] = temp;
    }
}
//the player selects a card
void chooseCard(int* player)
{
    int Set[] = { 12, 7, 7, 7, 7 };
    counter = 1;
    char key;

    while (true)
    {
        gotoXY(189, 6);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[0]);
        cout << ">";

        gotoXY(189, 15);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[1]);
        cout << ">";

        gotoXY(189, 24);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[2]);
        cout << ">";

        gotoXY(189, 33);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[3]);
        cout << ">";

        gotoXY(189, 44);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[4]);
        cout << ">";

        key = _getch();

        if (key == 72) // up arrow key
        {
            if (counter == 1)
            {
                counter = 5;
            }
            else
            {
                counter--;
            }
        }
        if (key == 80) // down arrow key
        {
            if (counter == 5)
            {
                counter = 1;
            }
            else
            {
                counter++;
            }
        }
        if (key == 's')// select card
        {
            if (counter == 1)
            {
                chosenCard = player[0];
                break;
            }
            if (counter == 2)
            {
                chosenCard = player[1];
                break;
            }
            if (counter == 3)
            {
                chosenCard = player[2];
                break;
            }
            if (counter == 4)
            {
                chosenCard = player[3];
                break;
            }
            if (counter == 5)
            {
                chosenCard = player[4];
                break;
            }
        }
        if (key == 27)// enter
        {
            startProgram();
            break;
        }

        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;

        if (counter == 1)
        {
            Set[0] = 12;
        }
        if (counter == 2)
        {
            Set[1] = 12;
        }
        if (counter == 3)
        {
            Set[2] = 12;
        }
        if (counter == 4)
        {
            Set[3] = 12;
        }
        if (counter == 5)
        {
            Set[4] = 12;
        }
    }

    Sleep(150);
}

//display cards 
void printCards(int cardsNeeded, int* player)
{
    int cardCounter = 0;
    int pixelsX = 191;
    int pixelsY = 2;
    gotoXY(30, 3); cout << YELLOW << "Player 1's side" << RESET;
    gotoXY(139, 3); cout << YELLOW << "Player 2's side" << RESET;
    for (int i = 0; i < 52; i++)
    {
        gotoXY(187, i); cout << "|";
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
        cardCounter++;
        pixelsY += 9;
        if (cardCounter == 4)
        {
            pixelsY += 2;
        }
    }
}
//display the empty positions
void printPositions()
{
    int posCoordinates[15][3] = { {60, 107, 4}, {60, 107, 13}, {60, 107, 22}, {60, 107, 31}, {60, 107, 40},
                              {47, 122, 8}, {47, 122, 18}, {47, 122, 28}, {47, 122, 38},
                              {32, 137, 12}, {32, 137, 23}, {32, 137, 34},
                              {17, 152, 17}, {17, 152, 29},
                              {2, 167, 23}
    };

    int xP1, xP2, y;

    for (int i = 0; i < 5; i++)
    {
        y = posCoordinates[i][2];

        if (!isOccupiedP1[i])
        {
            gotoXY(60, y++); cout << " _______________" << endl;
            gotoXY(60, y++); cout << "|    POSITION   |" << endl;
            gotoXY(60, y++); cout << "|               |" << endl;
            gotoXY(60, y++); cout << "|               |" << endl;
            gotoXY(60, y++); cout << "|       " << i + 1 << "       |" << endl;
            gotoXY(60, y++); cout << "|               |" << endl;
            gotoXY(60, y++); cout << "|               |" << endl;
            gotoXY(60, y++); cout << "|               |" << endl;
            gotoXY(60, y++); cout << "|_______________|" << endl;
        }

        y = posCoordinates[i][2];

        if (!isOccupiedP2[i])
        {
            gotoXY(107, y++); cout << " _______________" << endl;
            gotoXY(107, y++); cout << "|    POSITION   |" << endl;
            gotoXY(107, y++); cout << "|               |" << endl;
            gotoXY(107, y++); cout << "|               |" << endl;
            gotoXY(107, y++); cout << "|       " << i + 1 << "       |" << endl;
            gotoXY(107, y++); cout << "|               |" << endl;
            gotoXY(107, y++); cout << "|               |" << endl;
            gotoXY(107, y++); cout << "|               |" << endl;
            gotoXY(107, y++); cout << "|_______________|" << endl;
        }
    }

    int inColumn = 4;
    int posP1 = 6, posP2 = 6;

    for (int i = 5; i < 15; i++)
    {
        xP1 = posCoordinates[i][0];
        xP2 = posCoordinates[i][1];
        y = posCoordinates[i][2];

        if (i == 9)
        {
            posP1 = 1;
            posP2 = 1;
        }

        if (isOccupiedP1[i - inColumn] and isOccupiedP1[i - inColumn - 1] and (!isOccupiedP1[i]))
        {
            gotoXY(xP1, y++); cout << " _______________" << endl;
            gotoXY(xP1, y++); cout << "|    POSITION   |" << endl;
            gotoXY(xP1, y++); cout << "|               |" << endl;
            gotoXY(xP1, y++); cout << "|               |" << endl;
            gotoXY(xP1, y++); cout << "|       " << posP1 << "       |" << endl;
            gotoXY(xP1, y++); cout << "|               |" << endl;
            gotoXY(xP1, y++); cout << "|               |" << endl;
            gotoXY(xP1, y++); cout << "|               |" << endl;
            gotoXY(xP1, y++); cout << "|_______________|" << endl;
        }

        y = posCoordinates[i][2];

        if (isOccupiedP2[i - inColumn] and isOccupiedP2[i - inColumn - 1] and (!isOccupiedP2[i]))
        {
            gotoXY(xP2, y++); cout << " _______________" << endl;
            gotoXY(xP2, y++); cout << "|    POSITION   |" << endl;
            gotoXY(xP2, y++); cout << "|               |" << endl;
            gotoXY(xP2, y++); cout << "|               |" << endl;
            gotoXY(xP2, y++); cout << "|       " << posP2 << "       |" << endl;
            gotoXY(xP2, y++); cout << "|               |" << endl;
            gotoXY(xP2, y++); cout << "|               |" << endl;
            gotoXY(xP2, y++); cout << "|               |" << endl;
            gotoXY(xP2, y++); cout << "|_______________|" << endl;
        }

        posP1++; posP2++;

        if (i == 8 or i == 11 or i == 13)
        {
            inColumn--;
        }
    }
}
//put down a card in a chosen position
void placeCard(int* playersCards, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues)
{
    int pixelsX;
    int pixelsY;



    while (true)
    {
        char keyPress;
        keyPress = _getch();
        int asciiValue = keyPress - 48;


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
                if (chosenCard % 6 == 1 && !(boolCardValues[0] || boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[0] ^ boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[0] && boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[0] || boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[0] ^ boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[0] && boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(cardValues[5] || cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[5] ^ cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[5] && cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[5] || cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[5] ^ cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[5] && cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
            }
        }
        if (asciiValue == 2)  // '2' ASCII code
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
                if (chosenCard % 6 == 1 && !(boolCardValues[1] || boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[1] ^ boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[1] && boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[1] || boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[1] ^ boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[1] && boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(cardValues[6] || cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[6] ^ cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[6] && cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[6] || cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[6] ^ cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[6] && cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
            }
        }
        if (asciiValue == 3) // '3' ASCII code
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
                if (chosenCard % 6 == 1 && !(boolCardValues[2] || boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[2] ^ boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[2] && boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[2] || boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[2] ^ boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[2] && boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(cardValues[7] || cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[7] ^ cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[7] && cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[7] || cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[7] ^ cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[7] && cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
            }
        }
        if (asciiValue == 4) // '4' ASCII code
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
                if (chosenCard % 6 == 1 && !(boolCardValues[3] || boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[3] ^ boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[3] && boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[3] || boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[3] ^ boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[3] && boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(cardValues[9] || cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[9] ^ cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[9] && cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[9] || cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[9] ^ cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[9] && cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
            }
        }
        if (asciiValue == 5) // '5' ASCII code
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
                if (chosenCard % 6 == 1 && !(boolCardValues[4] || boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[4] ^ boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[4] && boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[4] || boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[4] ^ boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[4] && boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(cardValues[10] || cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[10] ^ cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[10] && cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[10] || cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[10] ^ cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[10] && cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
            }
        }
        if (asciiValue == 6) // '6' ASCII code
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
                if (chosenCard % 6 == 1 && !(cardValues[0] || cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[0] ^ cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[0] && cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[0] || cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[0] ^ cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[0] && cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(cardValues[12] || cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[12] ^ cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[12] && cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[12] || cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[12] ^ cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    removeCard(counter, playersCards);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[12] && cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    removeCard(counter, playersCards);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
            if (chosenCard % 6 == 1 && !(cardValues[1] || cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 2 && !(cardValues[1] ^ cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 3 && !(cardValues[1] && cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 4 && (cardValues[1] || cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 5 && (cardValues[1] ^ cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 0 && (cardValues[1] && cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCard(counter, playersCards);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                continue;
            }
        }
        else
        {
            gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
            if (chosenCard % 6 == 1 && !(cardValues[2] || cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 2 && !(cardValues[2] ^ cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 3 && !(cardValues[2] && cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 4 && (cardValues[2] || cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 5 && (cardValues[2] ^ cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 0 && (cardValues[2] && cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCard(counter, playersCards);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                continue;
            }
        }
        else
        {
            gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
            if (chosenCard % 6 == 1 && !(cardValues[3] || cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 2 && !(cardValues[3] ^ cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 3 && !(cardValues[3] && cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 4 && (cardValues[3] || cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 5 && (cardValues[3] ^ cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCard(counter, playersCards);
                break;
            }
            else if (chosenCard % 6 == 0 && (cardValues[3] && cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCard(counter, playersCards);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                continue;
            }
        }
        else
        {
            gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
        }
        if (asciiValue == 66)// 'r' ASCII value
        {
            gotoXY(195, 50); cout << "PLAYER " << player << "  ";

            chooseCard(playersCards);

            if (player == 1)
            {
                placeCard(playersCards, boolCardValues, 1, occupiedPositions, cardValues);
            }
            else
            {
                placeCard(playersCards, boolCardValues, 2, occupiedPositions, cardValues);
            }
            break;
        }
        if (asciiValue == 52)// 'd' ASCII value
        {
            removeCard(counter, playersCards);
            break;
        }
        if (asciiValue == 27)// escape ASCII value
        {
            startProgram();
            break;
        }
    }
}

//Player one
void firstPlayer()
{
    printCards(5, playerOneCards);
    chooseCard(playerOneCards);
    placeCard(playerOneCards, boolCardValuesP1, 1, isOccupiedP1, cardValuesP1);
}
//Player two
void secondPlayer()
{
    printCards(5, playerTwoCards);
    chooseCard(playerTwoCards);
    placeCard(playerTwoCards, boolCardValuesP2, 2, isOccupiedP2, cardValuesP2);
}

//start the game
void beginningOfTheGameWithTwoPLayers()
{
    fill_n(cards, 48, 0);
    fill_n(playerOneCards, 5, 0);
    fill_n(playerTwoCards, 5, 0);
    fill_n(boolCardValuesP1, 6, 0);
    fill_n(boolCardValuesP2, 6, 0);
    fill_n(cardValuesP1, 15, 0);
    fill_n(cardValuesP2, 15, 0);
    fill_n(isOccupiedP1, 15, 0);
    fill_n(isOccupiedP2, 15, 0);
    chosenCard = 0;

    shuffleBoolCards();
    shuffleCards();

    takeCards(5, playerOneCards);
    takeCards(5, playerTwoCards);

    while (true)
    {
        printPositions();
        gotoXY(195, 50); cout << "PLAYER 1";
        takeCards(1, playerOneCards);
        firstPlayer();

        printPositions();
        gotoXY(195, 50); cout << "PLAYER 2";
        takeCards(1, playerTwoCards);
        secondPlayer();

        if (isOccupiedP1[14] == 1 || isOccupiedP2[14] == 1)
        {
            system("cls");
            break;
        } 
    }

    if (isOccupiedP1[14] == 1 && isOccupiedP2[14] == 1)
    {
        system("cls");

        gotoXY(90, 20); cout << "    ___  __    _  __    __ " << endl;
        gotoXY(90, 21); cout << "   /   \\/__\\  /_\\/ / /\\ \\ \\" << endl;
        gotoXY(90, 22); cout << "  / /\\ / \\// //_\\\\ \\/  \\/ /" << endl;
        gotoXY(90, 23); cout << " / /_// _  \\/  _  \\  /\\  / " << endl;
        gotoXY(90, 24); cout << "/___,'\\/ \\_/\\_/ \\_/\\/  \\/" << endl;
        Sleep(3000);
        startProgram();
    }
    else if (isOccupiedP1[14] == 1)
    {
        system("cls");

        gotoXY(73, 20); cout << "   ___  __    _         __  __    _    __    __ _____    __  __" << endl;
        gotoXY(73, 21); cout << "  / _ \\/ /   /_\\ /\\_/\\ /__\\/__\\  / |  / / /\\ \\ \\\\_   \\/\\ \\ \\/ _\\" << endl;
        gotoXY(73, 22); cout << " / /_)/ /   //_\\\\\\_ _//_\\ / \\//  | |  \\ \\/  \\/ / / /\\/  \\/ /\\ \\" << endl;
        gotoXY(73, 23); cout << "/ ___/ /___/  _  \\/ \\//__/ _  \\  | |   \\  /\\  /\\/ /_/ /\\  / _\\ \\" << endl;
        gotoXY(73, 24); cout << "\\/   \\____/\\_/ \\_/\\_/\\__/\\/ \\_/  |_|    \\/  \\/\\____/\\_\\ \\/  \\__/" << endl;
        Sleep(3000);
        startProgram();
    }
    else if (isOccupiedP2[14] == 1)
    {
        system("cls");

        gotoXY(70, 20); cout << "   ___  __    _         __  __    ____     __    __ _____    __  __ " << endl;
        gotoXY(70, 21); cout << "  / _ \\/ /   /_\\ /\\_/\\ /__\\/__\\  |___ \\   / / /\\ \\ \\\\_   \\/\\ \\ \\/ _\\" << endl;
        gotoXY(70, 22); cout << " / /_)/ /   //_\\\\\\_ _//_\\ / \\//    __) |  \\ \\/  \\/ / / /\\/  \\/ /\\ \\" << endl;
        gotoXY(70, 23); cout << "/ ___/ /___/  _  \\/ \\//__/ _  \\   / __/    \\  /\\  /\\/ /_/ /\\  / _\\ \\" << endl;
        gotoXY(70, 24); cout << "\\/   \\____/\\_/ \\_/\\_/\\__/\\/ \\_/  |_____|    \\/  \\/\\____/\\_\\ \\/  \\__/" << endl;
        Sleep(3000);
        startProgram();
    }
}