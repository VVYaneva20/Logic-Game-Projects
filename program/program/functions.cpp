#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "program.h"
#include "twoPlayersMode.h"
#include "twoPlayersWithNotCardMode.h"
#include "computerMode.h"
#include "computerWithNotCardMode.h"

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorPosition; // used for goto

int cards[48], cardsWithNotCard[56];
int playerOneCards[5], playerTwoCards[5];
int chosenCard;
int counter;
bool boolCardValuesP1[6], boolCardValuesP2[6];
bool cardValuesP1[15], cardValuesP2[15];
bool isOccupiedP1[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool isOccupiedP2[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//takes coordinates from the console
void gotoXY(int x, int y)
{
    cursorPosition.X = x;
    cursorPosition.Y = y;
    SetConsoleCursorPosition(console, cursorPosition);
}

//display cards
void printCardOrZero(int x, int y)
{
    gotoXY(x, y++); cout << RESET << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "OR    " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "___" << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/ _ \\ " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | | " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | |  " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| |_| |   " << RESET << " |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "\\___/  " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void printCardAndZero(int x, int y)
{
    gotoXY(x, y++); cout << RESET << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "AND   " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "___" << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/ _ \\ " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | | " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | |  " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| |_| |   " << RESET << " |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "\\___/  " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void printCardXorZero(int x, int y)
{
    gotoXY(x, y++); cout << RESET << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "XOR    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "___" << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/ _ \\ " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | | " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | |  " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| |_| |   " << RESET << " |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "\\___/  " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void printCardAndOne(int x, int y)
{
    gotoXY(x, y++); cout << RESET << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "AND    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "__" << RESET << "       |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/_ | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |   " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << " |_|  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void printCardOrOne(int x, int y)
{
    gotoXY(x, y++); cout << RESET << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "OR     " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "__" << RESET << "       |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/_ | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |   " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << " |_|  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void printCardXorOne(int x, int y)
{
    gotoXY(x, y++); cout << RESET << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "XOR    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "__" << RESET << "       |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/_ | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |   " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << " |_|  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void printInitialCardOne(int x, int y)
{
    gotoXY(x, y++); cout << RESET << " _____________" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " __  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << "/_ |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " | |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " | |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " | |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " |_|" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|_____________|" << endl;
}
void printInitialCardZero(int x, int y)
{
    gotoXY(x, y++); cout << RESET << " _____________" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " ___ " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << "/ _ \\" << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|   " << YELLOW << "| | | |" << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|   " << YELLOW << "| | | |" << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|   " << YELLOW << "| |_| |" << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << "\\___/" << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|_____________|" << endl;
}
void printNotCard(int x, int y)
{
    gotoXY(x, y++); cout << RESET << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "NOT " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|  ___________  |" << endl;
    gotoXY(x, y++); cout << "|  \\         /  |" << endl;
    gotoXY(x, y++); cout << "|   \\       /   |" << endl;
    gotoXY(x, y++); cout << "|    \\     /    |" << endl;
    gotoXY(x, y++); cout << "|     \\   /     |" << endl;
    gotoXY(x, y++); cout << "|      \\ /      |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}

//reset variables
void emptyVariables(int numberOfcards)
{
    fill_n(cards, numberOfcards, 0);

    fill_n(playerOneCards, 5, 0);
    fill_n(playerTwoCards, 5, 0);

    fill_n(boolCardValuesP1, 6, 0);
    fill_n(boolCardValuesP2, 6, 0);

    fill_n(cardValuesP1, 15, 0);
    fill_n(cardValuesP2, 15, 0);

    fill_n(isOccupiedP1, 15, 0);
    fill_n(isOccupiedP2, 15, 0);
}

//displays "Goodbye" message
void printGoodbye()
{
    gotoXY(83, 15); cout << RESET << "   ___   ___  ___  ___  ___        __" << endl;
    gotoXY(83, 16); cout << "  / _ \\ /___\\/___\\/   \\/ __\\/\\_/\\ /__\\" << endl;
    gotoXY(83, 17); cout << " / /_\\///  ///  // /\\ /__\\//\\_ _//_\\" << endl;
    gotoXY(83, 18); cout << "/ /_\\\\/ \\_// \\_// /_// \\/  \\ / \\//__" << endl;
    gotoXY(83, 19); cout << "\\____/\\___/\\___/___/ \\_____/ \\_/\\__/" << endl;
}

//makes the cursor invisible
void showConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

//reorganise initial cards
void shuffleInitialCards()
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
//reorganise all cards
void shuffleCards(int numberOfCards)
{
    int temp;

    for (int i = 0; i < numberOfCards; i++)
    {
        cards[i] = i + 1;
    }
    
    srand(time(NULL));

    for (int i = numberOfCards - 1; i > 0; --i)
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
void takeCards(int cardsNeeded, int* player, int numberOfCards)
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

        for (int j = 0; j < numberOfCards - 1; j++)
        {
            cards[j] = cards[j + 1];
        }

        cards[numberOfCards - 1] = temp;
    }
}

//display player's cards 
void printCards(int* player)
{
    int cardCounter = 0;
    int pixelsX = 191;
    int pixelsY = 2;

    for (int i = 0; i < 52; i++)
    {
        gotoXY(187, i); cout << "|";
    }

    for (int i = 0; i < 5; i++)
    {
        if (player[i] % 6 == 1)
        {
            printCardOrZero(pixelsX, pixelsY);
        }
        else if (player[i] % 6 == 2)
        {
            printCardXorZero(pixelsX, pixelsY);
        }
        else if (player[i] % 6 == 3)
        {
            printCardAndZero(pixelsX, pixelsY);
        }
        else if (player[i] % 6 == 4)
        {
            printCardOrOne(pixelsX, pixelsY);
        }
        else if (player[i] % 6 == 5)
        {
            printCardXorOne(pixelsX, pixelsY);
        }
        else if (player[i] % 6 == 0)
        {
            printCardAndOne(pixelsX, pixelsY);
        }

        cardCounter++;
        pixelsY += 9;

        if (cardCounter == 4)
        {
            pixelsY += 2;
        }
    }
}
void printCardsWithNotCard(int* player)
{
    int counter = 0;
    int pixelsX = 191;
    int pixelsY = 2;

    for (int i = 0; i < 52; i++)
    {
        gotoXY(187, i); cout << "|";
    }

    for (int i = 0; i < 5; i++)
    {
        if (player[i] % 7 == 1)
        {
            printCardOrZero(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 2)
        {
            printCardXorZero(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 3)
        {
            printCardAndZero(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 4)
        {
            printCardOrOne(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 5)
        {
            printCardXorOne(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 6)
        {
            printNotCard(pixelsX, pixelsY);
        }
        else if (player[i] % 7 == 0)
        {
            printCardAndOne(pixelsX, pixelsY);
        }

        counter++;
        pixelsY += 9;

        if (counter == 4)
        {
            pixelsY += 2;
        }
    }
}

//display truth table
void printTruthTable(int x, int y)
{
    int yCoordinates[5] = { 6, 15, 24, 33, 44 };

    for (int i = 0; i < 5; i++)
    {
        gotoXY(189, yCoordinates[i]); cout << " ";
    }

    for (int i = 0; i < 10; i++)
    {
        gotoXY(x, y++); cout << "                     ";
    }
    gotoXY(x, y++); cout << "  ____________       ";
    gotoXY(x, y++); cout << " |    AND     |      ";
    gotoXY(x, y++); cout << " |------------|      ";
    gotoXY(x, y++); cout << " | 0 && 0 | 0 |      ";
    gotoXY(x, y++); cout << " | 0 && 1 | 0 |      ";
    gotoXY(x, y++); cout << " | 1 && 0 | 0 |      ";
    gotoXY(x, y++); cout << " | 1 && 1 | 1 |      ";
    gotoXY(x, y++); cout << " |____________|      ";
    gotoXY(x, y++); cout << "                     ";
    gotoXY(x, y++); cout << "  ____________       ";
    gotoXY(x, y++); cout << " |     OR     |      ";
    gotoXY(x, y++); cout << " |------------|      ";
    gotoXY(x, y++); cout << " | 0 || 0 | 0 |      ";
    gotoXY(x, y++); cout << " | 0 || 1 | 1 |      ";
    gotoXY(x, y++); cout << " | 1 || 0 | 1 |      ";
    gotoXY(x, y++); cout << " | 1 || 1 | 1 |      ";
    gotoXY(x, y++); cout << " |____________|      ";
    gotoXY(x, y++); cout << "                     ";
    gotoXY(x, y++); cout << "  ____________       ";
    gotoXY(x, y++); cout << " |    XOR     |      ";
    gotoXY(x, y++); cout << " |------------|      ";
    gotoXY(x, y++); cout << " | 0 ^ 0  | 0 |      ";
    gotoXY(x, y++); cout << " | 0 ^ 1  | 1 |      ";
    gotoXY(x, y++); cout << " | 1 ^ 0  | 1 |      ";
    gotoXY(x, y++); cout << " | 1 ^ 1  | 0 |      ";
    gotoXY(x, y++); cout << " |____________|      ";

    for (int i = 0; i < 12; i++)
    {
        gotoXY(x, y++); cout << "                     ";
    }
}

//display positions in modes with not card
void printPositionsWithNotCard(int player, bool* isOccupied, int* values)
{
    int inColumn = 4;
    int position = 6;
    int xFirstFive, y, x;
    int positionCoordinates[15][3] = { {60, 107, 4}, {60, 107, 13}, {60, 107, 22}, {60, 107, 31}, {60, 107, 40},
                          {47, 122, 8}, {47, 122, 18}, {47, 122, 28}, {47, 122, 38},
                          {32, 137, 12}, {32, 137, 23}, {32, 137, 34},
                          {17, 152, 17}, {17, 152, 29},
                          {2, 167, 23}
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
        y = positionCoordinates[i][2];

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
        x = positionCoordinates[i][player - 1];
        y = positionCoordinates[i][2];

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

//display the positions of the initial cards
void printInitialPositions()
{
    int pixelsX = 77;
    int pixelsY = 2;
    int position = 1;

    for (int i = 0; i < 6; i++)
    {
        gotoXY(pixelsX, pixelsY++); cout << RESET << " _____________";
        gotoXY(pixelsX, pixelsY++); cout << "|             |";
        gotoXY(pixelsX, pixelsY++); cout << "|             |";
        gotoXY(pixelsX, pixelsY++); cout << "|             |";
        gotoXY(pixelsX, pixelsY++); cout << "|      " << position << "      |";
        gotoXY(pixelsX, pixelsY++); cout << "|             |";
        gotoXY(pixelsX, pixelsY++); cout << "|             |";
        gotoXY(pixelsX, pixelsY++); cout << "|_____________|";

        pixelsY -= 8;

        gotoXY(pixelsX + 15, pixelsY++); cout << RESET << " _____________";
        gotoXY(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXY(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXY(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXY(pixelsX + 15, pixelsY++); cout << "|      " << position << "      |";
        gotoXY(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXY(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXY(pixelsX + 15, pixelsY++); cout << "|_____________|";

        position++;
    }
}

//the player selects a card
void chooseCard(int* player, bool returned, bool notCard)
{
    counter = 1;
    char key;
    int set[] = { 12, 7, 7, 7, 7 };

    while (true)
    {
        gotoXY(189, 6);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set[0]);
        cout << ">";

        gotoXY(189, 15);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set[1]);
        cout << ">";

        gotoXY(189, 24);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set[2]);
        cout << ">";

        gotoXY(189, 33);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set[3]);
        cout << ">";

        gotoXY(189, 44);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set[4]);
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

        if (key == 115)// select card
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

        if (key == 27)// esc key ASCII value
        {
            startProgram();
            break;
        }

        if (key == 105)// 'i' esc key ASCII value
        {
            printTruthTable(191, 2);

            while (true)
            {
                char pressI;
                pressI = _getch();
                if (pressI == 105)
                {
                    break;
                }
            }

            if (notCard)
            {
                printCardsWithNotCard(player);
            }
            else
            {
                printCards(player);
            }
            
        }

        set[0] = 7;
        set[1] = 7;
        set[2] = 7;
        set[3] = 7;
        set[4] = 7;

        if (counter == 1)
        {
            set[0] = 12;
        }

        if (counter == 2)
        {
            set[1] = 12;
        }

        if (counter == 3)
        {
            set[2] = 12;
        }

        if (counter == 4)
        {
            set[3] = 12;
        }

        if (counter == 5)
        {
            set[4] = 12;
        }
    }

    Sleep(150);
}

//display instructions
void printInstructions()
{

    cout << R"(


       _________________________________________________________
      |                                                         |
      |                      TRUTH TABLE                        |
      |                                                         |
      |  |    AND     |     |     OR     |      |    XOR     |  |
      |  |------------|     |------------|      |------------|  |
      |  | 0 && 0 | 0 |     | 0 || 0 | 0 |      | 0 ^ 0  | 0 |  |
      |  | 0 && 1 | 0 |     | 0 || 1 | 1 |      | 0 ^ 1  | 1 |  |
      |  | 1 && 0 | 0 |     | 1 || 0 | 1 |      | 1 ^ 0  | 1 |  |
      |  | 1 && 1 | 1 |     | 1 || 1 | 1 |      | 1 ^ 1  | 0 |  |
      |_________________________________________________________|
       _________________________________________________________
      |                                                         |
      |                       HOW TO PLAY                       |
      |                                                         |
      |       With arrow up and arrow down - choose card        |
      |            With the key 'S' - select a card             |
      |  With keys from '1' to '9' - choose a place for a card  |
      |        With the key 'D' - discard selected card         |
      |       With the key 'R'- return after wrong choce        |
      |         With the key 'I' - see the truth table          |
      |     With the key 'Esc' - stop the game and go back      |
      |_________________________________________________________|
       _________________________________________________________
      |                                                         |
      |             THE DECK CONSISTS OF 64 CARDS:              |
      |                                                         |
      |          ° 8 OR cards resolving to 1                    |
      |          ° 8 OR cards resolving to 0                    |
      |          ° 8 AND cards resolving to 1                   |
      |          ° 8 AND cards resolving to 0                   |
      |          ° 8 XOR cards resolving to 1                   |
      |          ° 8 XOR cards resolving to 0                   |
      |          ° 8 NOT cards                                  |
      |          ° 6 Initial Binary cards (0 / 1)               |
      |          ° 2 Truth Tables (used for reference)          |
      |_________________________________________________________|

    )" << endl;

    for (int i = 30; i <= 38; i++)
    {
        gotoXY(17, i); cout << char(248);
    }

    printCardAndZero(191, 3);
    printCardXorOne(191, 12);
    printCardOrOne(191, 21);
    printCardOrZero(191, 30);

    gotoXY(191, 41); cout << RESET << " _______________" << endl;
    gotoXY(191, 42); cout << "|    " << RED << "  ____  " << RESET << "   |" << endl;
    gotoXY(191, 43); cout << "|    " << RED << " / __ `." << RESET << "   |" << endl;
    gotoXY(191, 44); cout << "|    " << RED << "|_/__) |" << RESET << "   |" << endl;
    gotoXY(191, 45); cout << "|    " << RED << "  /  _.'" << RESET << "   |" << endl;
    gotoXY(191, 46); cout << "|    " << RED << "  |_|   " << RESET << "   |" << endl;
    gotoXY(191, 47); cout << "|    " << RED << "  (_)   " << RESET << "   |" << endl;
    gotoXY(191, 48); cout << "|_______________|" << endl;

    gotoXY(188, 3); cout << "/" << endl;
    gotoXY(187, 4); cout << "/" << endl;

    for (int i = 5; i <= 37; i++)
    {
        switch (i)
        {
        case 19:
            gotoXY(186, i); cout << "/" << endl;
            break;
        case 20:
            gotoXY(174, i); cout << "Cards that /" << endl;
            break;
        case 21:
            gotoXY(175, i); cout << "you have  \\" << endl;
            break;
        case 22:
            gotoXY(186, i); cout << "\\" << endl;
            break;
        default:
            gotoXY(186, i); cout << "|" << endl;
        }
    }

    gotoXY(187, 38); cout << "\\" << endl;
    gotoXY(188, 39); cout << "\\" << endl;

    gotoXY(166, 45); cout << "Random card that     ->" << endl;
    gotoXY(162, 46); cout << "is different every time" << endl;

    gotoXY(85, 3); cout << " _________________________________________________________" << endl;
    gotoXY(85, 4); cout << "|                                                         |" << endl;
    gotoXY(85, 5); cout << "|                         RULES:                          | " << endl;
    gotoXY(85, 6); cout << "|                                                         | " << endl;
    gotoXY(85, 7); cout << "|                                                         | " << endl;
    gotoXY(85, 8); cout << "|                       Game setup:                       | " << endl;
    gotoXY(85, 9); cout << "|                                                         | " << endl;
    gotoXY(85, 10); cout << "|   At the beginning of the game, all cards are shuffled  | " << endl;
    gotoXY(85, 11); cout << "|  and the six initial cards are placed so that the '1'   | " << endl;
    gotoXY(85, 12); cout << "|    side is facing the first player and the '0' side     | " << endl;
    gotoXY(85, 13); cout << "|                is facing the other.                     | " << endl;
    gotoXY(85, 14); cout << "|                                                         | " << endl;
    gotoXY(85, 15); cout << "|                                                         | " << endl;
    gotoXY(85, 16); cout << "|                      Game play:                         | " << endl;
    gotoXY(85, 17); cout << "|                                                         | " << endl;
    gotoXY(85, 18); cout << "|   During each turn, the player is given a random card.  | " << endl;
    gotoXY(85, 19); cout << "| Then they can choose one of their cards and what to do  | " << endl;
    gotoXY(85, 20); cout << "| with it - play it or discard it. When the card is being | " << endl;
    gotoXY(85, 21); cout << "|      placed, it must resolve to a valid input.          | " << endl;
    gotoXY(85, 22); cout << "|                                                         | " << endl;
    gotoXY(85, 23); cout << "|                                                         | " << endl;
    gotoXY(85, 24); cout << "|                      Not card:                          | " << endl;
    gotoXY(85, 25); cout << "|                                                         | " << endl;
    gotoXY(85, 26); cout << "|  To play a Not card, the player declares which initial  | " << endl;
    gotoXY(85, 27); cout << "| bit is the target and reverses that bit card. This will | " << endl;
    gotoXY(85, 28); cout << "|  cause the initial binaries for both players to change. | " << endl;
    gotoXY(85, 29); cout << "|This can cause gates using this bit as an input to become| " << endl;
    gotoXY(85, 30); cout << "|    invalid. A Not card can also be played on the        | " << endl;
    gotoXY(85, 31); cout << "|  opponent’s turn as a reaction to cancel the Not card.  | " << endl;
    gotoXY(85, 32); cout << "|                                                         | " << endl;
    gotoXY(85, 33); cout << "|                                                         | " << endl;
    gotoXY(85, 34); cout << "|                         Win:                            | " << endl;
    gotoXY(85, 35); cout << "|                                                         | " << endl;
    gotoXY(85, 36); cout << "|    Wins the player who first finishes their pyramid.    | " << endl;
    gotoXY(85, 37); cout << "|                                                         | " << endl;
    gotoXY(85, 38); cout << "|                                                         | " << endl;
    gotoXY(85, 37); cout << "|                                                         | " << endl;
    gotoXY(85, 38); cout << "|                                                         | " << endl;
    gotoXY(85, 39); cout << "|_________________________________________________________|" << endl;

    char pressEscToGoBack;

    while (true)
    {
        pressEscToGoBack = _getch();

        if (pressEscToGoBack == 27)
        {
            system("cls");
            startProgram();
            break;
        }
    }
}

//beginning of the program
void startProgram()
{
    int counter = 1;
    char key;
    int set[] = { 12, 7, 7, 7, 7, 7 };

    system("cls");

    gotoXY(83, 9);  cout << RESET << "   ___    ___  __    __ " << endl;
    gotoXY(83, 10);  cout << "  / __\\  /___\\/ /   /__\\/\\ /\\  /\\/\\" << endl;
    gotoXY(83, 11);  cout << " /__\\// //  // /   /_\\ / / \\ \\/    \\" << endl;
    gotoXY(83, 12); cout << "/ \\/  \\/ \\_// /___//__ \\ \\_/ / /\\/\\ \\" << endl;
    gotoXY(83, 13); cout << "\\_____/\\___/\\____/\\__/  \\___/\\/    \\/" << endl;

    while (true)
    {
        gotoXY(85, 16);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set[0]);
        cout << "     Play with a computer";

        gotoXY(85, 17);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set[1]);
        cout << "Play with computer with NOT card";

        gotoXY(85, 18);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set[2]);
        cout << "      Play with a friend";

        gotoXY(85, 19);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set[3]);
        cout << "Play with a friend with NOT card";

        gotoXY(85, 20);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set[4]);
        cout << "	      Instructions";

        gotoXY(85, 21);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set[5]);
        cout << "	          Exit";

        key = _getch();

        if (key == 72) // up arrow key
        {
            if (counter == 1)
            {
                counter = 6;
            }
            else
            {
                counter--;
            }
        }

        if (key == 80) // down arrow key
        {
            if (counter == 6)
            {
                counter = 1;
            }
            else
            {
                counter++;
            }
        }

        if (key == '\r')// enter
        {
            if (counter == 1)
            {
                system("cls");
                startTheGameWithComputer();
                break;
            }
            if (counter == 2)
            {
                system("cls");
                startTheGameWithComputerNotCard();
                break;
            }
            if (counter == 3)
            {
                system("cls");
                beginningOfTheGameWithTwoPLayers();
                break;
            }
            if (counter == 4)
            {
                system("cls");
                startTheGameWithTwoPLayersNotCard();
                break;
            }
            if (counter == 5)
            {
                system("cls");
                printInstructions();
                break;
            }
            if (counter == 6)
            {
                system("cls");
                printGoodbye();
                exit(EXIT_FAILURE);
            }
        }

        set[0] = 7;
        set[1] = 7;
        set[2] = 7;
        set[3] = 7;
        set[4] = 7;
        set[5] = 7;

        if (counter == 1)
        {
            set[0] = 12;
        }

        if (counter == 2)
        {
            set[1] = 12;
        }

        if (counter == 3)
        {
            set[2] = 12;
        }

        if (counter == 4)
        {
            set[3] = 12;
        }

        if (counter == 5)
        {
            set[4] = 12;
        }

        if (counter == 6)
        {
            set[5] = 12;
        }
    }

    Sleep(150);
}