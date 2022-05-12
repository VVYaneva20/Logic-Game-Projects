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

void notCardWithComputer(int x, int y)
{
    gotoXYNotCardWithComputer(x, y++); cout << RESET << " _______________" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|      " << RED << "NOT " << RESET << "     |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|  ___________  |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|  \\         /  |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|   \\       /   |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|    \\     /    |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|     \\   /     |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|      \\ /      |" << endl;
    gotoXYNotCardWithComputer(x, y++); cout << "|_______________|" << endl;
}

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
            else if (values[i] % 7 == 2)
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