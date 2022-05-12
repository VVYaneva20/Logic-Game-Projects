#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "program.h"
#include "twoPlayersWithNotCardMode.h"

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
//takes coordinates
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

void notCardWithComputer(int x, int y)
{
    gotoXYNotCardWithComputer(x, y++); cout << RESET << " _______________" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|               |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|               |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|      " << RED << "NOT" << RESET << "      |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|     " << RED << "CARD" << RESET << "      |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|               |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|               |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|               |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|_______________|" << endl;
}

//display the empty positions
void printPositionsNotCardWithComputer(int player, bool* isOccupied, int* values)
{
    int xFirstFive, y, x, xP2;
    if (player == 1)
        xFirstFive = 60;
    else
        xFirstFive = 107;
    for (int i = 0; i < 5; i++)
    {
        y = posCoordinatesNotCardWithComputer[i][2];
        if (!isOccupied[i] && isNotCardComputerMode)
        {
            gotoXYNotCardWithComputer(xFirstFive, y++); cout << " _______________" << endl;
            gotoXYNotCardWithComputer(xFirstFive, y++); cout << "|    POSITION   |" << endl;
            gotoXYNotCardWithComputer(xFirstFive, y++); cout << "|               |" << endl;
            gotoXYNotCardWithComputer(xFirstFive, y++); cout << "|               |" << endl;
            gotoXYNotCardWithComputer(xFirstFive, y++); cout << "|       " << i + 1 << "       |" << endl;
            gotoXYNotCardWithComputer(xFirstFive, y++); cout << "|               |" << endl;
            gotoXYNotCardWithComputer(xFirstFive, y++); cout << "|               |" << endl;
            gotoXYNotCardWithComputer(xFirstFive, y++); cout << "|               |" << endl;
            gotoXYNotCardWithComputer(xFirstFive, y++); cout << "|_______________|" << endl;
        }
        else if (isOccupied[i])
        {
            if (values[i] % 7 == 1)
            {
                cardOrZero(xFirstFive, y);
            }
            else if (values[i] % 7 == 3)
            {
                cardXorZero(xFirstFive, y);
            }
            else if (values[i] % 7 == 3)
            {
                cardAndZero(xFirstFive, y);
            }
            else if (values[i] % 7 == 4)
            {
                cardOrOne(xFirstFive, y);
            }
            else if (values[i] % 7 == 5)
            {
                cardXorOne(xFirstFive, y);
            }
            else if (values[i] % 7 == 6)
            {
                notCardWithComputer(xFirstFive, y);
            }
            else if (values[i] % 7 == 1)
            {
                cardAndOne(xFirstFive, y);
            }
        }
    }
    int inColumn = 4;
    int position = 6;
    for (int i = 5; i < 15; i++)
    {
        x = posCoordinatesNotCardWithComputer[i][player - 1];
        y = posCoordinatesNotCardWithComputer[i][2];
        if (i == 9)
        {
            position = 1;
        }
        if ((isOccupied[i - inColumn] and isOccupied[i - inColumn - 2] and (!isOccupied[i])))
        {
            gotoXYNotCardWithComputer(x, y++); cout << " _______________" << endl;
            gotoXYNotCardWithComputer(x, y++); cout << "|    POSITION   |" << endl;
            gotoXYNotCardWithComputer(x, y++); cout << "|               |" << endl;
            gotoXYNotCardWithComputer(x, y++); cout << "|               |" << endl;
            gotoXYNotCardWithComputer(x, y++); cout << "|       " << position << "       |" << endl;
            gotoXYNotCardWithComputer(x, y++); cout << "|               |" << endl;
            gotoXYNotCardWithComputer(x, y++); cout << "|               |" << endl;
            gotoXYNotCardWithComputer(x, y++); cout << "|               |" << endl;
            gotoXYNotCardWithComputer(x, y++); cout << "|_______________|" << endl;
        }
        else if (isOccupied[i] && isNotCardComputerMode)
        {
            if (values[i] % 7 == 1)
            {
                cardOrZero(x, y);
            }
            else if (values[i] % 7 == 2)
            {
                cardXorZero(x, y);
            }
            else if (values[i] % 7 == 3)
            {
                cardAndZero(x, y);
            }
            else if (values[i] % 7 == 4)
            {
                cardOrOne(x, y);
            }
            else if (values[i] % 7 == 5)
            {
                cardXorOne(x, y);
            }
            else if (values[i] % 7 == 10)
            {
                notCardWithComputer(x, y);
            }
            else if (values[i] % 7 == 0)
            {
                cardAndOne(x, y);
            }
        }
        position++;
        if (i == 8 or i == 11 or i == 13)
        {
            inColumn--;
        }
    }
}

void notCardWithComputerCheck(int* values, bool* isOccupied, bool* initialCardValues, int playerNum)
{
    int pixelsX;
    int pixelsY;

    //notCardWithComputerCheck(cardsPlayer, occupiedPlayer, initialCardValuesPlayer, 1);
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
                gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << "                 ";
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
                gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << "                 ";
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
                gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << "                 ";
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
                gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << "                 ";
            }
        }
    }

    printPositionsNotCardWithComputer(1, occupiedPlayer, cardsPlayer);
    printPositionsNotCardWithComputer(2, occupiedPC, cardsComputer);
}

//discard a card
void removeCardNotCardWithComputer(int card, int* player)
{
    for (int i = card - 1; i < 5; ++i)
    {
        player[i] = player[i + 1];
    }
}

//the player gets allCards
void takeCardsWithComputer(int allCardsNeeded, int* player)
{
    if (allCardsNeeded != 1)
    {
        for (int i = 0; i < allCardsNeeded; i++)
        {
            player[i] = allCards[i];
        }
    }
    else
    {
        player[4] = allCards[0];
    }
    for (int i = 0; i < allCardsNeeded; i++)
    {
        int temp = allCards[0];
        for (int j = 0; j < 55; j++)
        {
            allCards[j] = allCards[j + 1];
        }
        allCards[55] = temp;
    }
}

//the player selects a card
void chooseCardNotCardWithComputer(int* player, bool returned)
{
    int Set[] = { 12, 7, 7, 7, 7 };
    counterNotCardComputerMode = 1;
    char key;
    while (true)
    {
        gotoXYNotCardWithComputer(189, 6);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[0]);
        cout << ">";
        gotoXYNotCardWithComputer(189, 15);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[1]);
        cout << ">";
        gotoXYNotCardWithComputer(189, 24);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[2]);
        cout << ">";
        gotoXYNotCardWithComputer(189, 33);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[3]);
        cout << ">";
        gotoXYNotCardWithComputer(189, 44);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[4]);
        cout << ">";
        key = _getch();
        if (key == 72) // up arrow key
        {
            if (counterNotCardComputerMode == 1)
            {
                counterNotCardComputerMode = 5;
            }
            else
            {
                counterNotCardComputerMode--;
            }
        }
        if (key == 80) // down arrow key
        {
            if (counterNotCardComputerMode == 5)
            {
                counterNotCardComputerMode = 1;
            }
            else
            {
                counterNotCardComputerMode++;
            }
        }
        if (key == 's')// select card
        {
            //player[counterNotCardComputerMode - 1] = choosenCard;
            if (counterNotCardComputerMode == 1)
            {
                choosenCard = player[0];
                break;
            }
            if (counterNotCardComputerMode == 2)
            {
                choosenCard = player[1];
                break;
            }
            if (counterNotCardComputerMode == 3)
            {
                choosenCard = player[2];
                break;
            }
            if (counterNotCardComputerMode == 4)
            {
                choosenCard = player[3];
                break;
            }
            if (counterNotCardComputerMode == 5)
            {
                choosenCard = player[4];
                break;
            }
        }
        if (key == 27)// esc
        {
            startProgram();
            break;
        }
        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;
        if (counterNotCardComputerMode == 1)
        {
            Set[0] = 12;
        }
        if (counterNotCardComputerMode == 2)
        {
            Set[1] = 12;
        }
        if (counterNotCardComputerMode == 3)
        {
            Set[2] = 12;
        }
        if (counterNotCardComputerMode == 4)
        {
            Set[3] = 12;
        }
        if (counterNotCardComputerMode == 5)
        {
            Set[4] = 12;
        }
    }
    Sleep(150);
}

//display allCards 
void printCardsWithComputer(int allCardsNeeded, int* player)
{
    int counter = 0;
    int pixelsX = 191;
    int pixelsY = 2;
    gotoXYNotCardWithComputer(30, 3); cout << YELLOW << "Player's side" << RESET;
    gotoXYNotCardWithComputer(139, 3); cout << YELLOW << "Computer's side" << RESET;
    for (int i = 0; i < 52; i++)
    {
        gotoXYNotCardWithComputer(187, i); cout << "|";
    }
    for (int i = 0; i < 5; i++)
    {
        if (player[i] % 7 == 1)
        {
            cardOrZero(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 2)
        {
            cardXorZero(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 3)
        {
            cardAndZero(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 4)
        {
            cardOrOne(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 5)
        {
            cardXorOne(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 6)
        {
            notCardWithComputer(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 0)
        {
            cardAndOne(pixelsX, pixelsY);
        }
        counter++;
        pixelsY += 9;
        if (counter == 4)
        {
            pixelsY += 2;
        }
    }
}

void printInitialPositionsWithComputer()
{
    int pixelsX = 77;
    int pixelsY = 2;
    int position = 1;
    for (int i = 0; i < 6; i++)
    {
        gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << RESET << " _____________";
        gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << "|             |";
        gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << "|             |";
        gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << "|             |";
        gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << "|      " << position << "      |";
        gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << "|             |";
        gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << "|             |";
        gotoXYNotCardWithComputer(pixelsX, pixelsY++); cout << "|_____________|";
        pixelsY -= 8;
        gotoXYNotCardWithComputer(pixelsX + 15, pixelsY++); cout << RESET << " _____________";
        gotoXYNotCardWithComputer(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXYNotCardWithComputer(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXYNotCardWithComputer(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXYNotCardWithComputer(pixelsX + 15, pixelsY++); cout << "|      " << position << "      |";
        gotoXYNotCardWithComputer(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXYNotCardWithComputer(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXYNotCardWithComputer(pixelsX + 15, pixelsY++); cout << "|_____________|";
        position++;
    }
}


void chooseCardNotCardComputer(int* player)
{
    if (counterNotCardComputerMode == 1)
    {
        choosenCard = player[0];
    }
    if (counterNotCardComputerMode == 2)
    {
        choosenCard = player[1];
    }
    if (counterNotCardComputerMode == 3)
    {
        choosenCard = player[2];
    }
    if (counterNotCardComputerMode == 4)
    {
        choosenCard = player[3];
    }
    if (counterNotCardComputerMode == 5)
    {
        choosenCard = player[4];
    }
    if (counterNotCardComputerMode == 6)
    {
        choosenCard = player[rand() % 4];
    }
}



void printInitialCardsWithComputer(int position, bool reverse, int player)
{
    int pixelsX = 77;
    int pixelsY = 2;

    if (reverse)
    {
        bool flag = 0;
        int temp;
        if (player == 1)
        {
            for (int i = 0; i < 5; i++)
            {
                if (computerCardsNotCard[i] % 7 == 6)
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
                if (playerCardsComputerNot[i] % 7 == 6)
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
                gotoXYNotCardWithComputer(18, 7); cout << "Do you want to use your not card?(y/n)";
            }
            else
            {
                gotoXYNotCardWithComputer(130, 7); cout << "Do you want to use your not card?(y/n)";
            }

            char keyPress;

            while (true)
            {
                keyPress = _getch();
                int asciiValue = keyPress;


                if (asciiValue == 110) // n
                {
                    if (player == 2)
                    {
                        gotoXYNotCardWithComputer(18, 7); cout << "                                      ";
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(130, 7); cout << "                                      ";
                    }
                    initialCardValuesPlayer[position] = !initialCardValuesPlayer[position];
                    initialcardValuesPC[position] = !initialcardValuesPC[position];

                    break;
                }
                else if (asciiValue == 121) // y
                {
                    if (player == 2)
                    {
                        gotoXYNotCardWithComputer(18, 7); cout << "                                      ";
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(130, 7); cout << "                                      ";
                    }
                    if (player == 1)
                    {
                        skipTurnPC = 1;
                        removeCardNotCardWithComputer(temp + 1, computerCardsNotCard);
                    }
                    else
                    {
                        skipTurnPlayer = 1;
                        removeCardNotCardWithComputer(temp + 1, playerCardsComputerNot);

                    }
                    break;
                }
            }


        }

    }

    for (int i = 0; i < 6; i++)
    {
        if (initialCardValuesPlayer[i] == 0)
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

void (*pointToCardNotCardWithComputer[6])(int x, int y) = { cardOrZero, cardXorZero, cardAndZero, cardOrOne, cardXorOne, cardAndOne };

void placeCardNotCardWithComputer(bool* occupiedPositions, int index, int pointerIndex, int x, int y, bool* cardValues, int* cards, int cardValue, bool value, int* playersCards)
{
    occupiedPositions[index] = 1;
    pointToCardNotCardWithComputer[pointerIndex](x, y);
    cardValues[index] = value;
    cards[index] = cardValue;
    removeCardNotCardWithComputer(counterNotCardComputerMode, playersCards);
}

//put down a card in a chosen position
void checkCardNotCardWithComputer(int* playersallCards, bool* initialvalues, int player, bool* occupiedPositions, bool* values, int* cardValues)
{
    int pixelsX;
    int pixelsY;

    while (true)
    {
        if (choosenCard % 7 != 6)
        {
            isNotCardComputerMode = false;
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
                    if (choosenCard % 7 == 1 && !(initialvalues[0] || initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(initialvalues[0] ^ initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(initialvalues[0] && initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (initialvalues[0] || initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (initialvalues[0] ^ initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (initialvalues[0] && initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                    if (choosenCard % 7 == 1 && !(values[5] || values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[5] ^ values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[5] && values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[5] || values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[5] ^ values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[5] && values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 0;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                    if (choosenCard % 7 == 1 && !(initialvalues[1] || initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[1] = 0;
                        cardValues[1] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(initialvalues[1] ^ initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[1] = 0;
                        cardValues[1] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(initialvalues[1] && initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardValues[1] = 10;
                        cardAndZero(pixelsX, pixelsY);
                        values[1] = 0;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (initialvalues[1] || initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (initialvalues[1] ^ initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (initialvalues[1] && initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                    if (choosenCard % 7 == 1 && !(values[6] || values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[6] ^ values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[6] && values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[6] || values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[6] ^ values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[6] && values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                    if (choosenCard % 7 == 1 && !(initialvalues[2] || initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(initialvalues[2] ^ initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(initialvalues[2] && initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (initialvalues[2] || initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (initialvalues[2] ^ initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (initialvalues[2] && initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                    if (choosenCard % 7 == 1 && !(values[7] || values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[7] ^ values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[7] && values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[7] || values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[7] ^ values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[7] && values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                    if (choosenCard % 7 == 1 && !(initialvalues[3] || initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(initialvalues[3] ^ initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(initialvalues[3] && initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (initialvalues[3] || initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (initialvalues[3] ^ initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (initialvalues[3] && initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                    if (choosenCard % 7 == 1 && !(values[9] || values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[9] ^ values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[9] && values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[9] || values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[9] ^ values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[9] && values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                    if (choosenCard % 7 == 1 && !(initialvalues[4] || initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(initialvalues[4] ^ initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(initialvalues[4] && initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (initialvalues[4] || initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (initialvalues[4] ^ initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (initialvalues[4] && initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                    if (choosenCard % 7 == 1 && !(values[10] || values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[10] ^ values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[10] && values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[10] || values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[10] ^ values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[10] && values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                    if (choosenCard % 7 == 1 && !(values[0] || values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[0] ^ values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[0] && values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[0] || values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[0] ^ values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[0] && values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 0;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                    if (choosenCard % 7 == 1 && !(values[12] || values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 8;
                        occupiedPositions[14] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[12] ^ values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 9;
                        occupiedPositions[14] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[12] && values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 10;
                        occupiedPositions[14] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[12] || values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 11;
                        occupiedPositions[14] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[12] ^ values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 12;
                        occupiedPositions[14] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[12] && values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 7;
                        occupiedPositions[14] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else
                    {
                        gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (choosenCard % 7 == 1 && !(values[1] || values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 8;
                    occupiedPositions[6] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 2 && !(values[1] ^ values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 9;
                    occupiedPositions[6] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 3 && !(values[1] && values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 10;
                    occupiedPositions[6] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 4 && (values[1] || values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 11;
                    occupiedPositions[6] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 5 && (values[1] ^ values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 12;
                    occupiedPositions[6] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 0 && (values[1] && values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 7;
                    occupiedPositions[6] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else
                {
                    gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (choosenCard % 7 == 1 && !(values[2] || values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 8;
                    occupiedPositions[7] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 2 && !(values[2] ^ values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 9;
                    occupiedPositions[7] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 3 && !(values[2] && values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 10;
                    occupiedPositions[7] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 4 && (values[2] || values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 11;
                    occupiedPositions[7] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 5 && (values[2] ^ values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 12;
                    occupiedPositions[7] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 0 && (values[2] && values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 7;
                    occupiedPositions[7] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else
                {
                    gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
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
                if (choosenCard % 7 == 1 && !(values[3] || values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 8;
                    occupiedPositions[8] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 2 && !(values[3] ^ values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 9;
                    occupiedPositions[8] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 3 && !(values[3] && values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 10;
                    occupiedPositions[8] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 4 && (values[3] || values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 11;
                    occupiedPositions[8] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 5 && (values[3] ^ values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 12;
                    occupiedPositions[8] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 0 && (values[3] && values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 7;
                    occupiedPositions[8] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else
                {
                    gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXYNotCardWithComputer(195, 50); cout << RED << "Invalid!" << RESET;
            }
            if (asciiValue == 66)// 'r' ASCII value
            {
                gotoXYNotCardWithComputer(195, 50); cout << "PLAYER " << player << "  ";
                chooseCardNotCardWithComputer(playersallCards, 1);
                if (player == 1)
                {
                    checkCardNotCardWithComputer(playersallCards, initialvalues, 1, occupiedPositions, values, cardValues);
                }
                else
                {
                    checkCardNotCardWithComputer(playersallCards, initialvalues, 2, occupiedPositions, values, cardValues);
                }
                break;
            }
            if (asciiValue == 52)// 'd' ASCII value
            {
                removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                break;
            }
            if (asciiValue == 27)// escape ASCII value
            {
                startProgram();
                break;
            }
        }
        else
        {
            isNotCardComputerMode = true;
            printInitialPositionsWithComputer();
            char press;
            press = _getch();
            int ascii = press - 48;
            int cardPosition = 0;
            if (ascii == 52)// 'd' ASCII value
            {
                removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                printInitialCardsWithComputer(cardPosition, 0, player);
                break;
            }
            if (ascii == 27)// escape ASCII value
            {
                startProgram();
                break;
            }
            switch (ascii)
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
            removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
            printInitialCardsWithComputer(cardPosition, 1, player);
            notCardWithComputerCheck(cardsPlayer, occupiedPlayer, initialCardValuesPlayer, 1);
            notCardWithComputerCheck(cardsComputer, occupiedPC, initialcardValuesPC, 2);
            break;
        }
    }
}


void checkCardComputer(int* playersallCards, bool* initialvalues, int player, bool* occupiedPositions, bool* values, int* cardValues)
{
    int pixelsX;
    int pixelsY;


    int asciiValue = 0;

    while (true)
    {
        asciiValue++;

        if (choosenCard % 7 != 6)
        {
            isNotCardComputerMode = false;

            if (counterNotCardComputerMode == 6)
            {
                removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                break;
            }
            if (asciiValue == 10)
            {
                counterNotCardComputerMode++;
                chooseCardNotCardComputer(computerCardsNotCard);
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
                    if (choosenCard % 7 == 1 && !(initialvalues[0] || initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(initialvalues[0] ^ initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(initialvalues[0] && initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (initialvalues[0] || initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (initialvalues[0] ^ initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (initialvalues[0] && initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
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
                    if (choosenCard % 7 == 1 && !(values[5] || values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[5] ^ values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[5] && values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[5] || values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[5] ^ values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[5] && values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 0;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
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
                    if (choosenCard % 7 == 1 && !(initialvalues[1] || initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[1] = 0;
                        cardValues[1] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(initialvalues[1] ^ initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[1] = 0;
                        cardValues[1] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(initialvalues[1] && initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardValues[1] = 10;
                        cardAndZero(pixelsX, pixelsY);
                        values[1] = 0;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (initialvalues[1] || initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (initialvalues[1] ^ initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (initialvalues[1] && initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
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
                    if (choosenCard % 7 == 1 && !(values[6] || values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[6] ^ values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[6] && values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[6] || values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[6] ^ values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[6] && values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
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
                    if (choosenCard % 7 == 1 && !(initialvalues[2] || initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(initialvalues[2] ^ initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(initialvalues[2] && initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (initialvalues[2] || initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (initialvalues[2] ^ initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (initialvalues[2] && initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
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
                    if (choosenCard % 7 == 1 && !(values[7] || values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[7] ^ values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[7] && values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[7] || values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[7] ^ values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[7] && values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
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
                    if (choosenCard % 7 == 1 && !(initialvalues[3] || initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(initialvalues[3] ^ initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(initialvalues[3] && initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (initialvalues[3] || initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (initialvalues[3] ^ initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (initialvalues[3] && initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
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
                    if (choosenCard % 7 == 1 && !(values[9] || values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[9] ^ values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[9] && values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[9] || values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[9] ^ values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[9] && values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }

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
                    if (choosenCard % 7 == 1 && !(initialvalues[4] || initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(initialvalues[4] ^ initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(initialvalues[4] && initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (initialvalues[4] || initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (initialvalues[4] ^ initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (initialvalues[4] && initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
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
                    if (choosenCard % 7 == 1 && !(values[10] || values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[10] ^ values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[10] && values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[10] || values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[10] ^ values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[10] && values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 7;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
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
                    if (choosenCard % 7 == 1 && !(values[0] || values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 8;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[0] ^ values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 9;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[0] && values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 10;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[0] || values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 11;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[0] ^ values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 12;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[0] && values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 0;
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
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
                    if (choosenCard % 7 == 1 && !(values[12] || values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 8;
                        occupiedPositions[14] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 2 && !(values[12] ^ values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 9;
                        occupiedPositions[14] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 3 && !(values[12] && values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 10;
                        occupiedPositions[14] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 4 && (values[12] || values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 11;
                        occupiedPositions[14] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 5 && (values[12] ^ values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 12;
                        occupiedPositions[14] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
                    else if (choosenCard % 7 == 0 && (values[12] && values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 7;
                        occupiedPositions[14] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                        break;
                    }
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
                if (choosenCard % 7 == 1 && !(values[1] || values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 8;
                    occupiedPositions[6] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 2 && !(values[1] ^ values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 9;
                    occupiedPositions[6] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 3 && !(values[1] && values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 10;
                    occupiedPositions[6] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 4 && (values[1] || values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 11;
                    occupiedPositions[6] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 5 && (values[1] ^ values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 12;
                    occupiedPositions[6] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 0 && (values[1] && values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 7;
                    occupiedPositions[6] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
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
                if (choosenCard % 7 == 1 && !(values[2] || values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 8;
                    occupiedPositions[7] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 2 && !(values[2] ^ values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 9;
                    occupiedPositions[7] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 3 && !(values[2] && values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 10;
                    occupiedPositions[7] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 4 && (values[2] || values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 11;
                    occupiedPositions[7] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 5 && (values[2] ^ values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 12;
                    occupiedPositions[7] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 0 && (values[2] && values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 7;
                    occupiedPositions[7] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
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
                if (choosenCard % 7 == 1 && !(values[3] || values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 8;
                    occupiedPositions[8] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 2 && !(values[3] ^ values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 9;
                    occupiedPositions[8] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 3 && !(values[3] && values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 10;
                    occupiedPositions[8] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 4 && (values[3] || values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 11;
                    occupiedPositions[8] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 5 && (values[3] ^ values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 12;
                    occupiedPositions[8] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
                else if (choosenCard % 7 == 0 && (values[3] && values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 7;
                    occupiedPositions[8] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
                    break;
                }
            }

        }
        else
        {
            isNotCardComputerMode = true;

            int cardPosition = 0;
            srand(time(NULL));

            int ascii = rand() % 6 + 1;

            switch (ascii)
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

            removeCardNotCardWithComputer(counterNotCardComputerMode, playersallCards);
            printInitialCardsWithComputer(cardPosition, 1, player);
            notCardWithComputerCheck(cardsPlayer, occupiedPlayer, initialCardValuesPlayer, 1);
            notCardWithComputerCheck(cardsComputer, occupiedPC, initialcardValuesPC, 2);
            break;
        }
    }
}


//Player one
void playerTurn()
{
    printCardsWithComputer(5, playerCardsComputerNot);
    chooseCardNotCardWithComputer(playerCardsComputerNot, 0);
    checkCardNotCardWithComputer(playerCardsComputerNot, initialCardValuesPlayer, 1, occupiedPlayer, valuesPlayer, cardsPlayer);
}
//Player two
void computerTurn()
{
    printCardsWithComputer(5, computerCardsNotCard);

    counterNotCardComputerMode = 1;
    chooseCardNotCardComputer(computerCardsNotCard);
    Sleep(2500);
    checkCardComputer(computerCardsNotCard, initialcardValuesPC, 2, occupiedPC, valuesPC, cardsComputer);

}
//start the game
void beginningOfTheGameWithComputerNotCard()
{
    fill_n(allCards, 48, 0);
    fill_n(playerCardsComputerNot, 5, 0);
    fill_n(computerCardsNotCard, 5, 0);
    fill_n(initialCardValuesPlayer, 6, 0);
    fill_n(initialcardValuesPC, 6, 0);
    fill_n(valuesPlayer, 15, 0);
    fill_n(valuesPC, 15, 0);
    fill_n(occupiedPlayer, 15, 0);
    fill_n(occupiedPC, 15, 0);
    choosenCard = 0;
    shuffleBooleanCards();
    shuffleAllCards();
    takeCardsWithComputer(5, playerCardsComputerNot);
    takeCardsWithComputer(5, computerCardsNotCard);

    while (true)
    {
        if (skipTurnPlayer == 0)
        {
            skipTurnPC = 0;

            printPositionsNotCardWithComputer(1, occupiedPlayer, cardsPlayer);
            printPositionsNotCardWithComputer(2, occupiedPC, cardsComputer);


            gotoXYNotCardWithComputer(195, 50); cout << "PLAYER 1";
            takeCardsWithComputer(1, playerCardsComputerNot);
            playerTurn();
        }

        if (skipTurnPC == 0)
        {
            skipTurnPlayer = 0;

            printPositionsNotCardWithComputer(1, occupiedPlayer, cardsPlayer);
            printPositionsNotCardWithComputer(2, occupiedPC, cardsComputer);

            gotoXYNotCardWithComputer(195, 50); cout << "PLAYER 2";
            takeCardsWithComputer(1, computerCardsNotCard);
            computerTurn();
        }




        if (occupiedPlayer[14] == 1 || occupiedPC[14] == 1)
        {
            system("cls");
            break;
        }
    }
    if (occupiedPlayer[14] == 1 && occupiedPC[14] == 1)
    {
        system("cls");
        gotoXYNotCardWithComputer(90, 20); cout << "    ___  __    _  __    __ " << endl;
        gotoXYNotCardWithComputer(90, 21); cout << "   /   \\/__\\  /_\\/ / /\\ \\ \\" << endl;
        gotoXYNotCardWithComputer(90, 22); cout << "  / /\\ / \\// //_\\\\ \\/  \\/ /" << endl;
        gotoXYNotCardWithComputer(90, 23); cout << " / /_// _  \\/  _  \\  /\\  / " << endl;
        gotoXYNotCardWithComputer(90, 24); cout << "/___,'\\/ \\_/\\_/ \\_/\\/  \\/" << endl;
        Sleep(3000);
        startProgram();
    }
    else if (occupiedPlayer[14] == 1)
    {
        system("cls");
        gotoXYNotCardWithComputer(73, 20); cout << "   ___  __    _         __  __    _    __    __ _____    __  __" << endl;
        gotoXYNotCardWithComputer(73, 21); cout << "  / _ \\/ /   /_\\ /\\_/\\ /__\\/__\\  / |  / / /\\ \\ \\\\_   \\/\\ \\ \\/ _\\" << endl;
        gotoXYNotCardWithComputer(73, 22); cout << " / /_)/ /   //_\\\\\\_ _//_\\ / \\//  | |  \\ \\/  \\/ / / /\\/  \\/ /\\ \\" << endl;
        gotoXYNotCardWithComputer(73, 23); cout << "/ ___/ /___/  _  \\/ \\//__/ _  \\  | |   \\  /\\  /\\/ /_/ /\\  / _\\ \\" << endl;
        gotoXYNotCardWithComputer(73, 24); cout << "\\/   \\____/\\_/ \\_/\\_/\\__/\\/ \\_/  |_|    \\/  \\/\\____/\\_\\ \\/  \\__/" << endl;
        Sleep(3000);
        startProgram();
    }
    else if (occupiedPC[14] == 1)
    {
        system("cls");
        gotoXYNotCardWithComputer(70, 20); cout << "   ___  __    _         __  __    ____     __    __ _____    __  __ " << endl;
        gotoXYNotCardWithComputer(70, 21); cout << "  / _ \\/ /   /_\\ /\\_/\\ /__\\/__\\  |___ \\   / / /\\ \\ \\\\_   \\/\\ \\ \\/ _\\" << endl;
        gotoXYNotCardWithComputer(70, 22); cout << " / /_)/ /   //_\\\\\\_ _//_\\ / \\//    __) |  \\ \\/  \\/ / / /\\/  \\/ /\\ \\" << endl;
        gotoXYNotCardWithComputer(70, 23); cout << "/ ___/ /___/  _  \\/ \\//__/ _  \\   / __/    \\  /\\  /\\/ /_/ /\\  / _\\ \\" << endl;
        gotoXYNotCardWithComputer(70, 24); cout << "\\/   \\____/\\_/ \\_/\\_/\\__/\\/ \\_/  |_____|    \\/  \\/\\____/\\_\\ \\/  \\__/" << endl;
        Sleep(3000);
        startProgram();
    }
}