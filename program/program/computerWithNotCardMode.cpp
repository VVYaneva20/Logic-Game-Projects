#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "program.h"
#include "computerWithNotCardMode.h"

using namespace std;

int cardsPlayer[15], cardsComputer[15];
bool skipTurnPlayer = 0, skipTurnPC = 0;

//array of pointers to the card functions
void (*pointToCardNotCardWithComputer[6])(int x, int y) = { printCardOrZero, printCardXorZero, printCardAndZero, printCardOrOne, printCardXorOne, printCardAndOne };

//display the empty positions
void printPositionsNotCardWithComputer(int player, bool* isOccupied, int* values)
{
    int inColumn = 4;
    int position = 6;
    int xFirstFive, y, x;
    int posCoordinatesNotCardWithComputer[15][3] = { {60, 107, 4}, {60, 107, 13}, {60, 107, 22}, {60, 107, 31}, {60, 107, 40},
                          {47, 122, 8}, {47, 122, 18}, {47, 122, 28}, {47, 122, 38},
                          {32, 137, 12}, {32, 137, 23}, {32, 137, 34},
                          {17, 152, 17}, {17, 152, 29},
                          {2, 167}
    };

    if (player == 1)
    {
        xFirstFive = 60;
    }
    else
    {
        xFirstFive = 107;
    }

    for (int i = 0; i < 5; i++)
    {
        y = posCoordinatesNotCardWithComputer[i][2];

        if (!isOccupied[i])
        {
            gotoXY(xFirstFive, y++); cout << " _______________" << endl;
            gotoXY(xFirstFive, y++); cout << "|    POSITION   |" << endl;
            gotoXY(xFirstFive, y++); cout << "|               |" << endl;
            gotoXY(xFirstFive, y++); cout << "|               |" << endl;
            gotoXY(xFirstFive, y++); cout << "|       " << i + 1 << "       |" << endl;
            gotoXY(xFirstFive, y++); cout << "|               |" << endl;
            gotoXY(xFirstFive, y++); cout << "|               |" << endl;
            gotoXY(xFirstFive, y++); cout << "|               |" << endl;
            gotoXY(xFirstFive, y++); cout << "|_______________|" << endl;
        }
        else if (isOccupied[i])
        {
            if (values[i] == 8)
            {
                printCardOrZero(xFirstFive, y);
            }
            else if (values[i] == 9)
            {
                printCardXorZero(xFirstFive, y);
            }
            else if (values[i] == 10)
            {
                printCardAndZero(xFirstFive, y);
            }
            else if (values[i] == 11)
            {
                printCardOrOne(xFirstFive, y);
            }
            else if (values[i] == 12)
            {
                printCardXorOne(xFirstFive, y);
            }
            else if (values[i] == 7)
            {
                printCardAndOne(xFirstFive, y);
            }
        }
    }

    for (int i = 5; i < 15; i++)
    {
        x = posCoordinatesNotCardWithComputer[i][player - 1];
        y = posCoordinatesNotCardWithComputer[i][2];

        if (i == 9)
        {
            position = 1;
        }

        if ((isOccupied[i - inColumn] and isOccupied[i - inColumn - 1] and (!isOccupied[i])))
        {
            gotoXY(x, y++); cout << " _______________" << endl;
            gotoXY(x, y++); cout << "|    POSITION   |" << endl;
            gotoXY(x, y++); cout << "|               |" << endl;
            gotoXY(x, y++); cout << "|               |" << endl;
            gotoXY(x, y++); cout << "|       " << position << "       |" << endl;
            gotoXY(x, y++); cout << "|               |" << endl;
            gotoXY(x, y++); cout << "|               |" << endl;
            gotoXY(x, y++); cout << "|               |" << endl;
            gotoXY(x, y++); cout << "|_______________|" << endl;
        }
        else if (isOccupied[i])
        {
            if (values[i] == 8)
            {
                printCardOrZero(x, y);
            }
            else if (values[i] == 9)
            {
                printCardXorZero(x, y);
            }
            else if (values[i] == 10)
            {
                printCardAndZero(x, y);
            }
            else if (values[i] == 11)
            {
                printCardOrOne(x, y);
            }
            else if (values[i] == 12)
            {
                printCardXorOne(x, y);
            }
            else if (values[i] == 7)
            {
                printCardAndOne(x, y);
            }
        }

        position++;

        if (i == 8 or i == 11 or i == 13)
        {
            inColumn--;
        }
    }
}

//check if the placed cards are valid after Not card has been used
void notCardWithComputerCheck(int* values, bool* isOccupied, bool* initialCardValues, int playerNum)
{
    int pixelsX;
    int pixelsY;
    string spaces = "                 ";
    int posCoordinatesNotCardWithComputer[15][3] = { {60, 107, 4}, {60, 107, 13}, {60, 107, 22}, {60, 107, 31}, {60, 107, 40},
                          {47, 122, 8}, {47, 122, 18}, {47, 122, 28}, {47, 122, 38},
                          {32, 137, 12}, {32, 137, 23}, {32, 137, 34},
                          {17, 152, 17}, {17, 152, 29},
                          {2, 167}
    };

    for (int i = 0; i < 5; i++)
    {
        if ((values[i] == 8 and isOccupied[i] == 1 and (initialCardValues[i] || initialCardValues[i + 1])) or
            (values[i] == 9 and isOccupied[i] == 1 and (initialCardValues[i] ^ initialCardValues[i + 1])) or
            (values[i] == 10 and isOccupied[i] == 1 and (initialCardValues[i] && initialCardValues[i + 1])) or
            (values[i] == 11 and isOccupied[i] == 1 and !(initialCardValues[i] || initialCardValues[i + 1])) or
            (values[i] == 12 and isOccupied[i] == 1 and !(initialCardValues[i] ^ initialCardValues[i + 1])) or
            (values[i] == 7 and isOccupied[i] == 1 and !(initialCardValues[i] && initialCardValues[i + 1])))
        {
            isOccupied[i] = 0;
            values[i] = 0;

            printPositionsNotCardWithComputer(playerNum, isOccupied, values);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        pixelsX = posCoordinatesNotCardWithComputer[i + 5][playerNum - 1];
        pixelsY = posCoordinatesNotCardWithComputer[i + 5][2];

        if (isOccupied[i] == 0 || isOccupied[i + 1] == 0)
        {
            isOccupied[i + 5] = 0;

            for (int i = 0; i < 9; i++)
            {
                gotoXY(pixelsX, pixelsY++); cout << spaces;
            }
        }
    }

    for (int i = 5; i < 8; i++)
    {
        pixelsX = posCoordinatesNotCardWithComputer[i + 4][playerNum - 1];
        pixelsY = posCoordinatesNotCardWithComputer[i + 4][2];

        if (isOccupied[i] == 0 || isOccupied[i + 1] == 0)
        {
            isOccupied[i + 4] = 0;

            for (int i = 0; i < 9; i++)
            {
                gotoXY(pixelsX, pixelsY++); cout << spaces;
            }
        }
    }

    for (int i = 9; i < 11; i++)
    {
        pixelsX = posCoordinatesNotCardWithComputer[i + 3][playerNum - 1];
        pixelsY = posCoordinatesNotCardWithComputer[i + 3][2];

        if (isOccupied[i] == 0 || isOccupied[i + 1] == 0)
        {
            isOccupied[i + 3] = 0;

            for (int i = 0; i < 9; i++)
            {
                gotoXY(pixelsX, pixelsY++); cout << spaces;
            }
        }
    }

    for (int i = 12; i < 13; i++)
    {
        pixelsX = posCoordinatesNotCardWithComputer[i + 2][playerNum - 1];
        pixelsY = posCoordinatesNotCardWithComputer[i + 2][2];

        if (isOccupied[i] == 0 || isOccupied[i + 1] == 0)
        {
            isOccupied[i + 2] = 0;

            for (int i = 0; i < 9; i++)
            {
                gotoXY(pixelsX, pixelsY++); cout << spaces;
            }
        }
    }

    printPositionsNotCardWithComputer(1, isOccupiedP1, cardsPlayer);
    printPositionsNotCardWithComputer(2, isOccupiedP2, cardsComputer);
}

//the computer chooses a card
void chooseCardNotCardComputer(int* player)
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

//display Initial cards after Not card has been used
void printInitialCardsWithComputer(int position, bool reverse, int player)
{
    int pixelsX = 77;
    int pixelsY = 2;

    bool flag = 0;
    int temp;

    char keyPress;
    int asciiValue;

    if (reverse)
    {
        if (player == 1)
        {
            for (int i = 0; i < 5; i++)
            {
                if (playerTwoCards[i] % 7 == 6)
                {
                    temp = i;
                    flag = 1;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < 5; i++)
            {
                if (playerOneCards[i] % 7 == 6)
                {
                    temp = i;
                    flag = 1;
                    break;
                }
            }
        }

        if (flag)
        {
            if (player == 2)
            {
                gotoXY(18, 7); cout << "Do you want to use your not card?(y/n)";
            }
            else
            {
                gotoXY(130, 7); cout << "Do you want to use your not card?(y/n)";
            }

            while (true)
            {
                if (player == 2)
                {
                    keyPress = _getch();
                    asciiValue = keyPress;
                }
                else
                {
                    asciiValue = rand() % 2;
                    if (asciiValue == 1)
                    {
                        asciiValue = 121;
                        gotoXY(130, 7); cout << "Computer used NOT card and nothing changed!";
                    }
                    else
                    {
                        asciiValue = 110;
                    }

                    Sleep(1000);
                }

                if (asciiValue == 110) // n
                {
                    if (player == 2)
                    {
                        gotoXY(18, 7); cout << "                                       ";
                    }
                    else
                    {
                        gotoXY(130, 7); cout << "                                           ";
                    }
                    boolCardValuesP1[position] = !boolCardValuesP1[position];
                    boolCardValuesP2[position] = !boolCardValuesP2[position];

                    break;
                }
                else if (asciiValue == 121) // y
                {
                    if (player == 1)
                    {
                        gotoXY(130, 7); cout << "                                           ";
                        skipTurnPC = 1;
                        removeCard(temp + 1, playerTwoCards);
                    }
                    else
                    {
                        gotoXY(18, 7); cout << "                                             ";
                        skipTurnPlayer = 1;
                        removeCard(temp + 1, playerOneCards);
                    }
                    break;
                }
            }
        }
        else
        {
            boolCardValuesP1[position] = !boolCardValuesP1[position];
            boolCardValuesP2[position] = !boolCardValuesP2[position];
        }
    }

    for (int i = 0; i < 6; i++)
    {
        if (boolCardValuesP1[i] == 0)
        {
            printInitialCardZero(pixelsX, pixelsY);
            printInitialCardOne(pixelsX + 15, pixelsY);
            boolCardValuesP1[i] = 0;
            boolCardValuesP2[i] = 1;
        }
        else
        {
            printInitialCardOne(pixelsX, pixelsY);
            printInitialCardZero(pixelsX + 15, pixelsY);
            boolCardValuesP1[i] = 1;
            boolCardValuesP2[i] = 0;
        }

        pixelsY += 8;
    }
}

//put down a card in a chosen position
void placeCardNotCardWithComputer(bool* occupiedPositions, int index, int pointerIndex, int x, int y, bool* boolValues, bool value, int* cardValues, int cardValue, int* playersCards)
{
    occupiedPositions[index] = 1;
    pointToCardNotCardWithComputer[pointerIndex](x, y);
    boolValues[index] = value;
    cardValues[index] = cardValue;
    removeCard(counter, playersCards);
}

//put down a card in a chosen position
void checkCardPlayer(int* playerscardsNotCard, bool* initialvalues, int player, bool* occupiedPositions, bool* values, int* cardValues)
{
    int pixelsX;
    int pixelsY;

    while (true)
    {
        if (chosenCard % 7 != 6)
        {
            char keyPress;
            keyPress = _getch();
            int asciiValue = keyPress - 48;//discard 48 from key's ASCII value
            if (asciiValue == 1)
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
                    if (chosenCard % 7 == 1 && !(initialvalues[0] || initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 8;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(initialvalues[0] ^ initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 9;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(initialvalues[0] && initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 10;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (initialvalues[0] || initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 11;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (initialvalues[0] ^ initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 12;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (initialvalues[0] && initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 7;
                        removeCard(counter, playerscardsNotCard);
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
                    if (chosenCard % 7 == 1 && !(values[5] || values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 8;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[5] ^ values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 9;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[5] && values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 10;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[5] || values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 11;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[5] ^ values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 12;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[5] && values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 0;
                        removeCard(counter, playerscardsNotCard);
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
            if (asciiValue == 2) 
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
                    if (chosenCard % 7 == 1 && !(initialvalues[1] || initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[1] = 0;
                        cardValues[1] = 8;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(initialvalues[1] ^ initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[1] = 0;
                        cardValues[1] = 9;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(initialvalues[1] && initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardValues[1] = 10;
                        printCardAndZero(pixelsX, pixelsY);
                        values[1] = 0;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (initialvalues[1] || initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 11;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (initialvalues[1] ^ initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 12;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (initialvalues[1] && initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 7;
                        removeCard(counter, playerscardsNotCard);
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
                    if (chosenCard % 7 == 1 && !(values[6] || values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 8;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[6] ^ values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 9;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[6] && values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 10;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[6] || values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 11;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[6] ^ values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 12;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[6] && values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 7;
                        removeCard(counter, playerscardsNotCard);
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
            if (asciiValue == 3) 
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
                    if (chosenCard % 7 == 1 && !(initialvalues[2] || initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 8;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(initialvalues[2] ^ initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 9;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(initialvalues[2] && initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 10;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (initialvalues[2] || initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 11;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (initialvalues[2] ^ initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 12;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (initialvalues[2] && initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 7;
                        removeCard(counter, playerscardsNotCard);
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
                    if (chosenCard % 7 == 1 && !(values[7] || values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 8;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[7] ^ values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 9;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[7] && values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 10;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[7] || values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 11;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[7] ^ values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 12;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[7] && values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 7;
                        removeCard(counter, playerscardsNotCard);
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
            if (asciiValue == 4)
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
                    if (chosenCard % 7 == 1 && !(initialvalues[3] || initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 8;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(initialvalues[3] ^ initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 9;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(initialvalues[3] && initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 10;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (initialvalues[3] || initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 11;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (initialvalues[3] ^ initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 12;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (initialvalues[3] && initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 7;
                        removeCard(counter, playerscardsNotCard);
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
                    if (chosenCard % 7 == 1 && !(values[9] || values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 8;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[9] ^ values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 9;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[9] && values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 10;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[9] || values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 11;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[9] ^ values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 12;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[9] && values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 7;
                        removeCard(counter, playerscardsNotCard);
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
            if (asciiValue == 5)
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
                    if (chosenCard % 7 == 1 && !(initialvalues[4] || initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 8;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(initialvalues[4] ^ initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 9;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(initialvalues[4] && initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 10;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (initialvalues[4] || initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 11;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (initialvalues[4] ^ initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 12;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (initialvalues[4] && initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 7;
                        removeCard(counter, playerscardsNotCard);
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
                    if (chosenCard % 7 == 1 && !(values[10] || values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 8;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[10] ^ values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 9;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[10] && values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 10;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[10] || values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 11;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[10] ^ values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 12;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[10] && values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 7;
                        removeCard(counter, playerscardsNotCard);
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
            if (asciiValue == 6)
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
                    if (chosenCard % 7 == 1 && !(values[0] || values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 8;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[0] ^ values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 9;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[0] && values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 10;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[0] || values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 11;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[0] ^ values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 12;
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[0] && values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 0;
                        removeCard(counter, playerscardsNotCard);
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
                    if (chosenCard % 7 == 1 && !(values[12] || values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 8;
                        occupiedPositions[14] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[12] ^ values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 9;
                        occupiedPositions[14] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[12] && values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 10;
                        occupiedPositions[14] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[12] || values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 11;
                        occupiedPositions[14] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[12] ^ values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 12;
                        occupiedPositions[14] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        removeCard(counter, playerscardsNotCard);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[12] && values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 7;
                        occupiedPositions[14] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        removeCard(counter, playerscardsNotCard);
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
            if (asciiValue == 7 && occupiedPositions[6] == 0)
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
                if (chosenCard % 7 == 1 && !(values[1] || values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 8;
                    occupiedPositions[6] = 1;
                    printCardOrZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 2 && !(values[1] ^ values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 9;
                    occupiedPositions[6] = 1;
                    printCardXorZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 3 && !(values[1] && values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 10;
                    occupiedPositions[6] = 1;
                    printCardAndZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 4 && (values[1] || values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 11;
                    occupiedPositions[6] = 1;
                    printCardOrOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 5 && (values[1] ^ values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 12;
                    occupiedPositions[6] = 1;
                    printCardXorOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 0 && (values[1] && values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 7;
                    occupiedPositions[6] = 1;
                    printCardAndOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCard(counter, playerscardsNotCard);
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
            if (asciiValue == 8 && occupiedPositions[7] == 0) 
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
                if (chosenCard % 7 == 1 && !(values[2] || values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 8;
                    occupiedPositions[7] = 1;
                    printCardOrZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 2 && !(values[2] ^ values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 9;
                    occupiedPositions[7] = 1;
                    printCardXorZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 3 && !(values[2] && values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 10;
                    occupiedPositions[7] = 1;
                    printCardAndZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 4 && (values[2] || values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 11;
                    occupiedPositions[7] = 1;
                    printCardOrOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 5 && (values[2] ^ values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 12;
                    occupiedPositions[7] = 1;
                    printCardXorOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 0 && (values[2] && values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 7;
                    occupiedPositions[7] = 1;
                    printCardAndOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCard(counter, playerscardsNotCard);
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
            if (asciiValue == 9 && occupiedPositions[8] == 0)
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
                if (chosenCard % 7 == 1 && !(values[3] || values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 8;
                    occupiedPositions[8] = 1;
                    printCardOrZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 2 && !(values[3] ^ values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 9;
                    occupiedPositions[8] = 1;
                    printCardXorZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 3 && !(values[3] && values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 10;
                    occupiedPositions[8] = 1;
                    printCardAndZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 4 && (values[3] || values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 11;
                    occupiedPositions[8] = 1;
                    printCardOrOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 5 && (values[3] ^ values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 12;
                    occupiedPositions[8] = 1;
                    printCardXorOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCard(counter, playerscardsNotCard);
                    break;
                }
                else if (chosenCard % 7 == 0 && (values[3] && values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 7;
                    occupiedPositions[8] = 1;
                    printCardAndOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCard(counter, playerscardsNotCard);
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
            if (asciiValue == 66)// 'r' 
            {
                gotoXY(195, 50); cout << " PLAYER   ";
                chooseCard(playerscardsNotCard, 1, 1);
                if (player == 1)
                {
                    checkCardPlayer(playerscardsNotCard, initialvalues, 1, occupiedPositions, values, cardValues);
                }
                else
                {
                    checkCardPlayer(playerscardsNotCard, initialvalues, 2, occupiedPositions, values, cardValues);
                }
                break;
            }
            if (asciiValue == 52)// 'd' 
            {
                removeCard(counter, playerscardsNotCard);
                break;
            }
            if (asciiValue == -21)
            {
                startProgram();
                break;
            }
        }
        else
        {
            printInitialPositions();

            char press;

            int ascii;
            int cardPosition = 10;
            int x = 1;

            while (true)
            {
                press = _getch();
                ascii = press - 48;//discard 48 from key's ASCII value

                if (ascii == 1) 
                {
                    cardPosition = 0;
                    break;
                }
                else if (ascii == 2)
                {
                    cardPosition = 1;
                    break;
                }
                else if (ascii == 3)
                {
                    cardPosition = 2;
                    break;
                }
                else if (ascii == 4)
                {
                    cardPosition = 3;
                    break;
                }
                else if (ascii == 5)
                {
                    cardPosition = 4;
                    break;
                }
                else if (ascii == 6)
                {
                    cardPosition = 5;
                    break;
                }
                else if (ascii == 52) // 'd' is pressed
                {
                    x = 0;
                    removeCard(counter, playerscardsNotCard);
                    printInitialCardsWithComputer(cardPosition, x, player);
                    break;
                }
                else if (ascii == 66)// 'r' is pressed
                {
                    x = 0;
                    printInitialCardsWithComputer(cardPosition, x, player);
                    gotoXY(195, 50); cout << " PLAYER ";
                    chooseCard(playerscardsNotCard, 1, 1);

                    checkCardPlayer(playerscardsNotCard, initialvalues, 1, occupiedPositions, values, cardValues);
                    
                    break;
                }
                else if (ascii == -21)
                {
                    startProgram();
                    break;
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                }
            }

            removeCard(counter, playerscardsNotCard);
            printInitialCardsWithComputer(cardPosition, x, player);
            notCardWithComputerCheck(cardsPlayer, isOccupiedP1, boolCardValuesP1, 1);
            notCardWithComputerCheck(cardsComputer, isOccupiedP2, boolCardValuesP2, 2);
            break;
        }
    }
}
void checkCardComputer(int* playersallCards, bool* initialvalues, int player, bool* occupiedPositions, bool* values, int* cardValues)
{
    int placedCards[6] = { 0, 0, 0, 0, 0, 0 };

    int pixelsX;
    int pixelsY; 
    
    int flag = 0;
    int max = placedCards[0];

    int asciiValue = 0;

    if (isOccupiedP1[0] == 1)
    {
        placedCards[0]++;
        placedCards[1]++;
    }
    else if (isOccupiedP1[1] == 1)
    {
        placedCards[1]++;
        placedCards[2]++;
    }
    else if (isOccupiedP1[2] == 1)
    {
        placedCards[2]++;
        placedCards[3]++;
    }
    else if (isOccupiedP1[3] == 1)
    {
        placedCards[3]++;
        placedCards[4]++;
    }
    else if (isOccupiedP1[4] == 1)
    {
        placedCards[4]++;
        placedCards[5]++;
    }
    else if (isOccupiedP1[5] == 1)
    {
        placedCards[0]++;
        placedCards[1]++;
    }
    else if (isOccupiedP1[6] == 1)
    {
        placedCards[1]++;
        placedCards[2]++;
        placedCards[3]++;
    }
    else if (isOccupiedP1[7] == 1)
    {
        placedCards[2]++;
        placedCards[3]++;
        placedCards[4]++;
    }
    else if (isOccupiedP1[8] == 1)
    {
        placedCards[3]++;
        placedCards[4]++;
        placedCards[5]++;
    }
    else if (isOccupiedP1[9] == 1)
    {
        placedCards[0]++;
        placedCards[1]++;
        placedCards[2]++;
        placedCards[3]++;
    }
    else if (isOccupiedP1[10] == 1)
    {
        placedCards[1]++;
        placedCards[2]++;
        placedCards[3]++;
        placedCards[4]++;
    }
    else if (isOccupiedP1[11] == 1)
    {
        placedCards[2]++;
        placedCards[3]++;
        placedCards[4]++;
        placedCards[5]++;
    }
    else if (isOccupiedP1[12] == 1)
    {

        placedCards[0]++;
        placedCards[1]++;
        placedCards[2]++;
        placedCards[3]++;
        placedCards[4]++;
    }
    else if (isOccupiedP1[13] == 1)
    {
        placedCards[1]++;
        placedCards[2]++;
        placedCards[3]++;
        placedCards[4]++;
        placedCards[5]++;
    }

    max = placedCards[0];

    while (true)
    {
        asciiValue++;

        if (chosenCard % 7 != 6)
        {
            if (counter == 6)
            {
                removeCard(counter, playersallCards);
                break;
            }
            if (asciiValue == 10)
            {
                counter++;
                chooseCardNotCardComputer(playerTwoCards);
                asciiValue = 1;
            }

            if (asciiValue == 1) 
            {
                if (occupiedPositions[0] == 0)
                {
                    pixelsY = 4;

                    if (player == 1)
                    {
                        pixelsX = 60;
                    }
                    else
                    {
                        pixelsX = 107;
                    }

                    if (chosenCard % 7 == 1 && !(initialvalues[0] || initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 8;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(initialvalues[0] ^ initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 9;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(initialvalues[0] && initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 10;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (initialvalues[0] || initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 11;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (initialvalues[0] ^ initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 12;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (initialvalues[0] && initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 7;
                        removeCard(counter, playersallCards);
                        break;
                    }
                }
                else if (occupiedPositions[9] == 0)
                {
                    pixelsY = 12;

                    if (player == 1)
                    {
                        pixelsX = 32;
                    }
                    else
                    {
                        pixelsX = 137;
                    }

                    if (chosenCard % 7 == 1 && !(values[5] || values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 8;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[5] ^ values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 9;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[5] && values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 10;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[5] || values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 11;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[5] ^ values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 12;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[5] && values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 0;
                        removeCard(counter, playersallCards);
                        break;
                    }
                }
            }
            if (asciiValue == 2) 
            {
                if (occupiedPositions[1] == 0)
                {
                    pixelsY = 13;

                    if (player == 1)
                    {
                        pixelsX = 60;
                    }
                    else
                    {
                        pixelsX = 107;
                    }

                    if (chosenCard % 7 == 1 && !(initialvalues[1] || initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[1] = 0;
                        cardValues[1] = 8;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(initialvalues[1] ^ initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[1] = 0;
                        cardValues[1] = 9;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(initialvalues[1] && initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardValues[1] = 10;
                        printCardAndZero(pixelsX, pixelsY);
                        values[1] = 0;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (initialvalues[1] || initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 11;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (initialvalues[1] ^ initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 12;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (initialvalues[1] && initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 7;
                        removeCard(counter, playersallCards);
                        break;
                    }
                }
                else if (occupiedPositions[10] == 0)
                {
                    pixelsY = 23;

                    if (player == 1)
                    {
                        pixelsX = 32;
                    }
                    else
                    {
                        pixelsX = 137;
                    }

                    if (chosenCard % 7 == 1 && !(values[6] || values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 8;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[6] ^ values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 9;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[6] && values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 10;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[6] || values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 11;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[6] ^ values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 12;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[6] && values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 7;
                        removeCard(counter, playersallCards);
                        break;
                    }
                }
            }
            if (asciiValue == 3) 
            {
                if (occupiedPositions[2] == 0)
                {
                    pixelsY = 22;

                    if (player == 1)
                    {
                        pixelsX = 60;
                    }
                    else
                    {
                        pixelsX = 107;
                    }

                    if (chosenCard % 7 == 1 && !(initialvalues[2] || initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 8;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(initialvalues[2] ^ initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 9;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(initialvalues[2] && initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 10;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (initialvalues[2] || initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 11;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (initialvalues[2] ^ initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 12;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (initialvalues[2] && initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 7;
                        removeCard(counter, playersallCards);
                        break;
                    }
                }
                else if (occupiedPositions[11] == 0)
                {
                    pixelsY = 34;

                    if (player == 1)
                    {
                        pixelsX = 32;
                    }
                    else
                    {
                        pixelsX = 137;
                    }

                    if (chosenCard % 7 == 1 && !(values[7] || values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 8;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[7] ^ values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 9;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[7] && values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 10;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[7] || values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 11;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[7] ^ values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 12;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[7] && values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 7;
                        removeCard(counter, playersallCards);
                        break;
                    }
                }
            }
            if (asciiValue == 4) 
            {
                if (occupiedPositions[3] == 0)
                {
                    pixelsY = 31;

                    if (player == 1)
                    {
                        pixelsX = 60;
                    }
                    else
                    {
                        pixelsX = 107;
                    }
                    
                    if (chosenCard % 7 == 1 && !(initialvalues[3] || initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 8;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(initialvalues[3] ^ initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 9;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(initialvalues[3] && initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 10;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (initialvalues[3] || initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 11;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (initialvalues[3] ^ initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 12;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (initialvalues[3] && initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 7;
                        removeCard(counter, playersallCards);
                        break;
                    }
                }
                else if (occupiedPositions[12] == 0)
                {
                    pixelsY = 17;

                    if (player == 1)
                    {
                        pixelsX = 17;
                    }
                    else
                    {
                        pixelsX = 152;
                    }

                    if (chosenCard % 7 == 1 && !(values[9] || values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 8;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[9] ^ values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 9;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[9] && values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 10;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[9] || values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 11;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[9] ^ values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 12;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[9] && values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 7;
                        removeCard(counter, playersallCards);
                        break;
                    }
                }
            }
            if (asciiValue == 5) 
            {
                if (occupiedPositions[4] == 0)
                {
                    pixelsY = 40;

                    if (player == 1)
                    {
                        pixelsX = 60;
                    }
                    else
                    {
                        pixelsX = 107;
                    }

                    if (chosenCard % 7 == 1 && !(initialvalues[4] || initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 8;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(initialvalues[4] ^ initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 9;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(initialvalues[4] && initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 10;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (initialvalues[4] || initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 11;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (initialvalues[4] ^ initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 12;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (initialvalues[4] && initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 7;
                        removeCard(counter, playersallCards);
                        break;
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
                    if (chosenCard % 7 == 1 && !(values[10] || values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 8;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[10] ^ values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 9;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[10] && values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 10;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[10] || values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 11;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[10] ^ values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 12;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[10] && values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 7;
                        removeCard(counter, playersallCards);
                        break;
                    }
                }
            }
            if (asciiValue == 6) 
            {
                if (occupiedPositions[5] == 0)
                {
                    pixelsY = 8;

                    if (player == 1)
                    {
                        pixelsX = 47;
                    }
                    else
                    {
                        pixelsX = 122;
                    }

                    if (chosenCard % 7 == 1 && !(values[0] || values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 8;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[0] ^ values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 9;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[0] && values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 10;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[0] || values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 11;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[0] ^ values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 12;
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[0] && values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 0;
                        removeCard(counter, playersallCards);
                        break;
                    }
                }
                else if (occupiedPositions[14] == 0)
                {
                    pixelsY = 23;

                    if (player == 1)
                    {
                        pixelsX = 2;
                    }
                    else
                    {
                        pixelsX = 167;
                    }

                    if (chosenCard % 7 == 1 && !(values[12] || values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 8;
                        occupiedPositions[14] = 1;
                        printCardOrZero(pixelsX, pixelsY);
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 2 && !(values[12] ^ values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 9;
                        occupiedPositions[14] = 1;
                        printCardXorZero(pixelsX, pixelsY);
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 3 && !(values[12] && values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 10;
                        occupiedPositions[14] = 1;
                        printCardAndZero(pixelsX, pixelsY);
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 4 && (values[12] || values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 11;
                        occupiedPositions[14] = 1;
                        printCardOrOne(pixelsX, pixelsY);
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 5 && (values[12] ^ values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 12;
                        occupiedPositions[14] = 1;
                        printCardXorOne(pixelsX, pixelsY);
                        removeCard(counter, playersallCards);
                        break;
                    }
                    else if (chosenCard % 7 == 0 && (values[12] && values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 7;
                        occupiedPositions[14] = 1;
                        printCardAndOne(pixelsX, pixelsY);
                        removeCard(counter, playersallCards);
                        break;
                    }
                }
            }
            if (asciiValue == 7 && occupiedPositions[6] == 0) 
            {
                pixelsY = 18;

                if (player == 1)
                {
                    pixelsX = 47;
                }
                else
                {
                    pixelsX = 122;
                }

                if (chosenCard % 7 == 1 && !(values[1] || values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 8;
                    occupiedPositions[6] = 1;
                    printCardOrZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 2 && !(values[1] ^ values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 9;
                    occupiedPositions[6] = 1;
                    printCardXorZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 3 && !(values[1] && values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 10;
                    occupiedPositions[6] = 1;
                    printCardAndZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 4 && (values[1] || values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 11;
                    occupiedPositions[6] = 1;
                    printCardOrOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 5 && (values[1] ^ values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 12;
                    occupiedPositions[6] = 1;
                    printCardXorOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 0 && (values[1] && values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 7;
                    occupiedPositions[6] = 1;
                    printCardAndOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCard(counter, playersallCards);
                    break;
                }
            }
            if (asciiValue == 8 && occupiedPositions[7] == 0) 
            {
                pixelsY = 28;

                if (player == 1)
                {
                    pixelsX = 47;
                }
                else
                {
                    pixelsX = 122;
                }

                if (chosenCard % 7 == 1 && !(values[2] || values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 8;
                    occupiedPositions[7] = 1;
                    printCardOrZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 2 && !(values[2] ^ values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 9;
                    occupiedPositions[7] = 1;
                    printCardXorZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 3 && !(values[2] && values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 10;
                    occupiedPositions[7] = 1;
                    printCardAndZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 4 && (values[2] || values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 11;
                    occupiedPositions[7] = 1;
                    printCardOrOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 5 && (values[2] ^ values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 12;
                    occupiedPositions[7] = 1;
                    printCardXorOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 0 && (values[2] && values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 7;
                    occupiedPositions[7] = 1;
                    printCardAndOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCard(counter, playersallCards);
                    break;
                }
            }
            if (asciiValue == 9 && occupiedPositions[8] == 0) 
            {
                pixelsY = 38;

                if (player == 1)
                {
                    pixelsX = 47;
                }
                else
                {
                    pixelsX = 122;
                }

                if (chosenCard % 7 == 1 && !(values[3] || values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 8;
                    occupiedPositions[8] = 1;
                    printCardOrZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 2 && !(values[3] ^ values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 9;
                    occupiedPositions[8] = 1;
                    printCardXorZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 3 && !(values[3] && values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 10;
                    occupiedPositions[8] = 1;
                    printCardAndZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 4 && (values[3] || values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 11;
                    occupiedPositions[8] = 1;
                    printCardOrOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 5 && (values[3] ^ values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 12;
                    occupiedPositions[8] = 1;
                    printCardXorOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCard(counter, playersallCards);
                    break;
                }
                else if (chosenCard % 7 == 0 && (values[3] && values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 7;
                    occupiedPositions[8] = 1;
                    printCardAndOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCard(counter, playersallCards);
                    break;
                }
            }
        }
        else
        {
            int cardPosition = 0;

            for (int i = 0; i < 6; i++)
            {
                if (placedCards[i] >= max)
                {
                    max = placedCards[i];
                    flag = i + 1;
                }
            }

            asciiValue = flag;

            switch (asciiValue)
            {
                case 1:
                {
                    cardPosition = 0;
                    break;
                }
                case 2:
                {
                    cardPosition = 1;
                    break;
                }
                case 3:
                {
                    cardPosition = 2;
                    break;
                }
                case 4:
                {
                    cardPosition = 3;
                    break;
                }
                case 5:
                {
                    cardPosition = 4;
                    break;
                }
                case 6:
                {
                    cardPosition = 5;
                    break;
                }
            }

            removeCard(counter, playersallCards);
            printInitialCardsWithComputer(cardPosition, 1, player);
            notCardWithComputerCheck(cardsPlayer, isOccupiedP1, boolCardValuesP1, 1);
            notCardWithComputerCheck(cardsComputer, isOccupiedP2, boolCardValuesP2, 2);
            break;
        }
    }
}

//Player's turn
void playerTurn()
{
    int yCoords[5] = { 6, 15, 24, 33, 44 };

    printCardsWithNotCard(playerOneCards);
    chooseCard(playerOneCards, 0, 1);
    checkCardPlayer(playerOneCards, boolCardValuesP1, 1, isOccupiedP1, cardValuesP1, cardsPlayer);
}
//Computer's turn
void computerTurn()
{
    int yCoords[5] = { 6, 15, 24, 33, 44 };

    printCardsWithNotCard(playerTwoCards);

    counter = 1;

    chooseCardNotCardComputer(playerTwoCards);
    Sleep(3500);
    checkCardComputer(playerTwoCards, boolCardValuesP2, 2, isOccupiedP2, cardValuesP2, cardsComputer);
}

//beginning of the game withcomputer with Not card
void startTheGameWithComputerNotCard()
{
    emptyVariables(56);

    chosenCard = 0;

    shuffleInitialCards();
    shuffleCards(56);

    takeCards(5, playerOneCards, 56);
    takeCards(5, playerTwoCards, 56);

    gotoXY(32, 3); cout << YELLOW << "Player's side " << RESET;
    gotoXY(139, 3); cout << YELLOW << "Computer's side" << RESET;

    while (true)
    {
        if (skipTurnPlayer == 0)
        {
            skipTurnPC = 0;
            gotoXY(18, 7); cout << "                                      ";
            printPositionsNotCardWithComputer(1, isOccupiedP1, cardsPlayer);
            printPositionsNotCardWithComputer(2, isOccupiedP2, cardsComputer);

            gotoXY(195, 50); cout << " PLAYER ";
            takeCards(1, playerOneCards, 56);
            playerTurn();
        }

        if (skipTurnPC == 0)
        {
            skipTurnPlayer = 0;
            gotoXY(130, 7); cout << "                                      ";
            printPositionsNotCardWithComputer(1, isOccupiedP1, cardsPlayer);
            printPositionsNotCardWithComputer(2, isOccupiedP2, cardsComputer);

            gotoXY(195, 50); cout << "COMPUTER";
            takeCards(1, playerTwoCards, 56);
            computerTurn();
        }

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