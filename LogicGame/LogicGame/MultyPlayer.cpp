#include "MultyPlayer.h"
#include <iostream>
#include <windows.h>
#include <string>

#define RESET   "\033[0m"
#define RED     "\033[31m"

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition; // used for goto

int cards[48];

void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}
void cardOrZero(int x, int y)
{
    gotoXY(x, y++); cout << " ___________________" << endl;
    gotoXY(x, y++); cout << "|         " << RED << "OR   " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|        " << RED << "___" << RESET << "        |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << "/ _ \\ " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "| | | | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "| | | |  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "| |_| |   " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << "\\___/  " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|___________________|" << endl;
}
void cardAndZero(int x, int y)
{
    gotoXY(x, y++); cout << " ___________________" << endl;
    gotoXY(x, y++); cout << "|         " << RED << "AND  " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|        " << RED << "___" << RESET << "        |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << "/ _ \\ " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "| | | | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "| | | |  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "| |_| |   " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << "\\___/  " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|___________________|" << endl;
}
void cardXorZero(int x, int y)
{
    gotoXY(x, y++); cout << " ___________________" << endl;
    gotoXY(x, y++); cout << "|         " << RED << "XOR   " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|        " << RED << "___" << RESET << "        |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << "/ _ \\ " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "| | | | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "| | | |  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "| |_| |   " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << "\\___/  " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|___________________|" << endl;
}
void cardAndOne(int x, int y)
{
    gotoXY(x, y++); cout << " ___________________" << endl;
    gotoXY(x, y++); cout << "|        " << RED << "AND    " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|        " << RED << "__" << RESET << "         |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << "/_ | " << RESET << "       |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | |  " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | |   " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | |    " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << " |_|  " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|___________________|" << endl;
}
void cardOrOne(int x, int y)
{
    gotoXY(x, y++); cout << " ___________________" << endl;
    gotoXY(x, y++); cout << "|        " << RED << " OR    " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|        " << RED << "__" << RESET << "         |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << "/_ | " << RESET << "       |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | |  " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | |   " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | |    " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << " |_|  " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|___________________|" << endl;
}
void cardXorOne(int x, int y)
{
    gotoXY(x, y++); cout << " ___________________" << endl;
    gotoXY(x, y++); cout << "|        " << RED << "XOR    " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|        " << RED << "__" << RESET << "         |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << "/_ | " << RESET << "       |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | |  " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | |   " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | |    " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|       " << RED << " |_|  " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|___________________|" << endl;
}
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
void displayCards(int cardsNeeded)
{

    int pixelsX = 2;
    int pixelsY = 2;

    for (int i = 0; i < cardsNeeded; i++)
    {
        if (cards[i] % 6 == 1)
        {
            cardOrZero(pixelsX, pixelsY);
        }
        else if (cards[i] % 6 == 2)
        {
            cardXorZero(pixelsX, pixelsY);
        }
        else if (cards[i] % 6 == 3)
        {
            cardAndZero(pixelsX, pixelsY);
        }
        else if (cards[i] % 6 == 4)
        {
            cardOrOne(pixelsX, pixelsY);
        }
        else if (cards[i] % 6 == 5)
        {
            cardXorOne(pixelsX, pixelsY);
        }
        else if (cards[i] % 6 == 0)
        {
            cardAndOne(pixelsX, pixelsY);
        }

        pixelsX += 22;

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
void cardOne(int x, int y)
{
    gotoXY(x, y++); cout << " __________________" << endl;
    gotoXY(x, y++); cout << "|                  |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  __   " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << " /_ | " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | | " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | | " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  | | " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "  |_| " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|                  |" << endl;
    gotoXY(x, y++); cout << "|__________________|" << endl;
}
void cardZero(int x, int y)
{
    gotoXY(x, y++); cout << " __________________" << endl;
    gotoXY(x, y++); cout << "|                  |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << " ___  " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "/ _ \\ " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "| | | | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "| | | | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "| |_| | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "\\___/ " << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|                  |" << endl;
    gotoXY(x, y++); cout << "|__________________|" << endl;
}
void shuffleBoolCards()
{
    bool cards[6];
    int pixelsX = 2;
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
            cardOne(pixelsX + 20, pixelsY);
        }
        else
        {
            cardOne(pixelsX, pixelsY);
            cardZero(pixelsX + 20, pixelsY);
        }
        pixelsY += 9;
    }
}


void firstPlayer()
{
    displayCards(4);
}

void secondPlayer()
{
    displayCards(4);
}

void beginingOfTheGameWithTwoPLayers()
{
    shuffleBoolCards();
}