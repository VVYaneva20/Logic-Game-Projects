#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "computerMode.h"
#include "program.h"

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

//computer selects a card
void chooseCardComputer(int* player)
{
    int yCoordinates[5] = { 6, 15, 24, 33, 44 };

    for (int i = 0; i < 5; i++)
    {
        gotoXY(189, yCoordinates[i]); cout << " ";
    }
    if (counter == 1)
    {
        chosenCard = player[0];
    }
    if (counter == 2)
    {
        chosenCard = player[1];
    }
    if (counter == 3)
    {
        chosenCard = player[2];
    }
    if (counter == 4)
    {
        chosenCard = player[3];
    }
    if (counter == 5)
    {
        chosenCard = player[4];
    }
    if (counter == 6)
    {
        chosenCard = player[rand() % 4];
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
            gotoXY(xPC, y++); cout << " _______________" << endl;
            gotoXY(xPC, y++); cout << "|    POSITION   |" << endl;
            gotoXY(xPC, y++); cout << "|               |" << endl;
            gotoXY(xPC, y++); cout << "|               |" << endl;
            gotoXY(xPC, y++); cout << "|       " << posPC << "       |" << endl;
            gotoXY(xPC, y++); cout << "|               |" << endl;
            gotoXY(xPC, y++); cout << "|               |" << endl;
            gotoXY(xPC, y++); cout << "|               |" << endl;
            gotoXY(xPC, y++); cout << "|_______________|" << endl;
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
            gotoXY(195, 50); cout << "PLAYER " << player << "  ";

            chooseCard(playerscardsComputerMode, 1);
            placeCardComputerMode(playerscardsComputerMode, boolCardValues, 1, occupiedPositions, cardValues);

            break;
        }
        if (asciiValue == 52)// 'd' ASCII value
        {
            removeCard(counter, playerscardsComputerMode);
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
                if (chosenCard % 6 == 1 && !(boolCardValues[0] || boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[0] ^ boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[0] && boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[0] || boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[0] ^ boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[0] && boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCard(counter, playerscardsComputerMode);
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
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[5] ^ cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[5] && cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[5] || cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[5] ^ cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[5] && cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(boolCardValues[1] || boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[1] ^ boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[1] && boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[1] || boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[1] ^ boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[1] && boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCard(counter, playerscardsComputerMode);
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
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[6] ^ cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[6] && cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[6] || cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[6] ^ cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[6] && cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(boolCardValues[2] || boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[2] ^ boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[2] && boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[2] || boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[2] ^ boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[2] && boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(cardValues[7] || cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[7] ^ cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[7] && cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[7] || cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[7] ^ cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[7] && cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(boolCardValues[3] || boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[3] ^ boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[3] && boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[3] || boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[3] ^ boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[3] && boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(cardValues[9] || cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[9] ^ cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[9] && cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[9] || cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[9] ^ cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[9] && cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(boolCardValues[4] || boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[4] ^ boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[4] && boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[4] || boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[4] ^ boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[4] && boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(cardValues[10] || cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[10] ^ cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[10] && cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[10] || cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[10] ^ cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[10] && cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(cardValues[0] || cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[0] ^ cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[0] && cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[0] || cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[0] ^ cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[0] && cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (chosenCard % 6 == 1 && !(cardValues[12] || cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[12] ^ cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[12] && cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[12] || cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[12] ^ cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[12] && cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    ;
                    continue;
                }
            }
            else
            {
                gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
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
            if (chosenCard % 6 == 1 && !(cardValues[1] || cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 2 && !(cardValues[1] ^ cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 3 && !(cardValues[1] && cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 4 && (cardValues[1] || cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 5 && (cardValues[1] ^ cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 0 && (cardValues[1] && cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCard(counter, playerscardsComputerMode);
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
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 2 && !(cardValues[2] ^ cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 3 && !(cardValues[2] && cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 4 && (cardValues[2] || cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 5 && (cardValues[2] ^ cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 0 && (cardValues[2] && cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCard(counter, playerscardsComputerMode);
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
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 2 && !(cardValues[3] ^ cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 3 && !(cardValues[3] && cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 4 && (cardValues[3] || cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 5 && (cardValues[3] ^ cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 0 && (cardValues[3] && cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCard(counter, playerscardsComputerMode);
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
}

void placeCardComputer(int* playerscardsComputerMode, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues)
{
    int pixelsX;
    int pixelsY;

    int asciiValue = 0;

    while (true)
    {
        asciiValue++;

        if (counter == 6)
        {
            removeCard(counter, playerscardsComputerMode);
            break;
        }
        if (asciiValue == 10)
        {
            counter++;
            chooseCardComputer(playerTwoCards);
            asciiValue = 1;
        }

        if (asciiValue == 1) // '1' ASCII code
        {
            if (occupiedPositions[0] == 0)
            {
                pixelsX = 107;
                pixelsY = 4;

                if (chosenCard % 6 == 1 && !(boolCardValues[0] || boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[0] ^ boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[0] && boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[0] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[0] || boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[0] ^ boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[0] && boolCardValues[1]))
                {
                    occupiedPositions[0] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[0] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
            }
            else if (occupiedPositions[9] == 0)
            {
                pixelsX = 137;
                pixelsY = 12;

                if (chosenCard % 6 == 1 && !(cardValues[5] || cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[5] ^ cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[5] && cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[9] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[5] || cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[5] ^ cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[5] && cardValues[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[9] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[9] = 1;
                    removeCard(counter, playerscardsComputerMode);
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
                if (chosenCard % 6 == 1 && !(boolCardValues[1] || boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[1] ^ boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[1] && boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[1] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[1] || boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[1] ^ boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[1] && boolCardValues[2]))
                {
                    occupiedPositions[1] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[1] = 1;
                    removeCard(counter, playerscardsComputerMode);
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
                if (chosenCard % 6 == 1 && !(cardValues[6] || cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[6] ^ cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[6] && cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[10] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[6] || cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[6] ^ cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[6] && cardValues[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                {
                    occupiedPositions[10] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[10] = 1;
                    removeCard(counter, playerscardsComputerMode);
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

                if (chosenCard % 6 == 1 && !(boolCardValues[2] || boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[2] ^ boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[2] && boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[2] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[2] || boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[2] ^ boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[2] && boolCardValues[3]))
                {
                    occupiedPositions[2] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[2] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
            }
            else if (occupiedPositions[11] == 0)
            {
                pixelsX = 137;
                pixelsY = 34;

                if (chosenCard % 6 == 1 && !(cardValues[7] || cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[7] ^ cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[7] && cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[11] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[7] || cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[7] ^ cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[7] && cardValues[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                {
                    occupiedPositions[11] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[11] = 1;
                    removeCard(counter, playerscardsComputerMode);
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

                if (chosenCard % 6 == 1 && !(boolCardValues[3] || boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[3] ^ boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[3] && boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[3] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[3] || boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[3] ^ boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[3] && boolCardValues[4]))
                {
                    occupiedPositions[3] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[3] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
            }
            else if (occupiedPositions[12] == 0)
            {
                pixelsX = 152;
                pixelsY = 17;

                if (chosenCard % 6 == 1 && !(cardValues[9] || cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[9] ^ cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[9] && cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[12] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[9] || cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[9] ^ cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[9] && cardValues[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[12] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[12] = 1;
                    removeCard(counter, playerscardsComputerMode);
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

                if (chosenCard % 6 == 1 && !(boolCardValues[4] || boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(boolCardValues[4] ^ boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(boolCardValues[4] && boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[4] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (boolCardValues[4] || boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (boolCardValues[4] ^ boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (boolCardValues[4] && boolCardValues[5]))
                {
                    occupiedPositions[4] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[4] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
            }
            else if (occupiedPositions[13] == 0)
            {
                pixelsX = 152;
                pixelsY = 29;

                if (chosenCard % 6 == 1 && !(cardValues[10] || cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[10] ^ cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[10] && cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[13] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[10] || cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[10] ^ cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[10] && cardValues[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                {
                    occupiedPositions[13] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[13] = 1;
                    removeCard(counter, playerscardsComputerMode);
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

                if (chosenCard % 6 == 1 && !(cardValues[0] || cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[0] ^ cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[0] && cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    cardValues[5] = 0;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[0] || cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[0] ^ cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[0] && cardValues[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                {
                    occupiedPositions[5] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    cardValues[5] = 1;
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
            }
            else if (occupiedPositions[14] == 0)
            {
                pixelsX = 167;
                pixelsY = 23;

                if (chosenCard % 6 == 1 && !(cardValues[12] || cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 2 && !(cardValues[12] ^ cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 3 && !(cardValues[12] && cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 4 && (cardValues[12] || cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 5 && (cardValues[12] ^ cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
                else if (chosenCard % 6 == 0 && (cardValues[12] && cardValues[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                {
                    occupiedPositions[14] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    removeCard(counter, playerscardsComputerMode);
                    break;
                }
            }
        }
        if (asciiValue == 7 && occupiedPositions[6] == 0) // '7' ASCII code
        {
            pixelsX = 122;
            pixelsY = 18;

            if (chosenCard % 6 == 1 && !(cardValues[1] || cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 2 && !(cardValues[1] ^ cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 3 && !(cardValues[1] && cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[6] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 4 && (cardValues[1] || cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 5 && (cardValues[1] ^ cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 0 && (cardValues[1] && cardValues[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
            {
                occupiedPositions[6] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[6] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
        }
        if (asciiValue == 8 && occupiedPositions[7] == 0) // '8' ASCII code
        {
            pixelsX = 122;
            pixelsY = 28;

            if (chosenCard % 6 == 1 && !(cardValues[2] || cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 2 && !(cardValues[2] ^ cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 3 && !(cardValues[2] && cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[7] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 4 && (cardValues[2] || cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 5 && (cardValues[2] ^ cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 1 && (cardValues[2] && cardValues[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[7] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[7] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
        }
        if (asciiValue == 9 && occupiedPositions[8] == 0) // '9' ASCII code
        {
            pixelsX = 122;
            pixelsY = 38;

            if (chosenCard % 6 == 1 && !(cardValues[3] || cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardOrZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 2 && !(cardValues[3] ^ cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardXorZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 3 && !(cardValues[3] && cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardAndZero(pixelsX, pixelsY);
                cardValues[8] = 0;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 4 && (cardValues[3] || cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardOrOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 5 && (cardValues[3] ^ cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardXorOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
            else if (chosenCard % 6 == 0 && (cardValues[3] && cardValues[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
            {
                occupiedPositions[8] = 1;
                cardAndOne(pixelsX, pixelsY);
                cardValues[8] = 1;
                removeCard(counter, playerscardsComputerMode);
                break;
            }
        }

    }
}

//Player
void player()
{
    int yCoords[5] = { 6, 15, 24, 33, 44 };
    printCards(playerOneCards);
    chooseCard(playerOneCards, 0);
    placeCardComputerMode(playerOneCards, boolCardValuesP1, 1, isOccupiedP1, cardValuesP1);

    gotoXY(189, yCoords[counter]); cout << " ";
}
//Computer
void computer()
{
    int yCoords[5] = { 6, 15, 24, 33, 44 };
    printCards(playerTwoCards);
    counter = 1;
    
    chooseCardComputer(playerTwoCards);
    Sleep(2000);
    placeCardComputer(playerTwoCards, boolCardValuesP2, 2, isOccupiedP2, cardValuesP2);

    gotoXY(189, yCoords[counter]); cout << " ";
}

//start the game
void beginningOfTheGameWithComputer()
{
    fill_n(cards, 48, 0);
    fill_n(playerOneCards, 7, 0);
    fill_n(playerTwoCards, 5, 0);
    fill_n(boolCardValuesP1, 6, 0);
    fill_n(boolCardValuesP2, 6, 0);
    fill_n(cardValuesP1, 15, 0);
    fill_n(cardValuesP2, 15, 0);
    fill_n(isOccupiedP1, 15, 0);
    fill_n(isOccupiedP2, 15, 0);
    chosenCard = 0;

    shuffleBoolCards();
    shuffleCards(48);

    takeCards(4, playerOneCards, 48);
    takeCards(4, playerTwoCards, 48);


    gotoXY(30, 3); cout << YELLOW << " Player's side " << RESET;
    gotoXY(139, 3); cout << YELLOW << "Computer's side" << RESET;

    while (true)
    {
        printPositionsComputerMode();
        gotoXY(195, 50); cout << "PLAYER 1";
        takeCards(1, playerOneCards, 48);
        player();

        printPositionsComputerMode();
        gotoXY(195, 50); cout << "COMPUTER";
        takeCards(1, playerTwoCards, 48);
        computer();

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

        gotoXY(67, 20); cout << "   ___   ___          ___       _____  __  __    __    __ _____    __  __ " << endl;
        gotoXY(67, 21); cout << "  / __\\ /___\\/\\/\\    / _ \\/\\ /\\/__   \\/__\\/__\\  / / /\\ \\ \\\\_   \\/\\ \\ \\/ _\\" << endl;
        gotoXY(67, 22); cout << " / /   //  //    \\  / /_)/ / \\ \\ / /\\/_\\ / \\//  \\ \\/  \\/ / / /\\/  \\/ /\\ \\" << endl;
        gotoXY(67, 23); cout << "/ /___/ \\_// /\\/\\ \\/ ___/\\ \\_/ // / //__/ _  \\   \\  /\\  /\\/ /_/ /\\  / _\\ \\" << endl;
        gotoXY(67, 24); cout << "\\____/\\___/\\/    \\/\\/     \\___/ \\/  \\__/\\/ \\_/    \\/  \\/\\____/\\_\\ \\/  \\__/" << endl;
        Sleep(3000);
        startProgram();
    }
}