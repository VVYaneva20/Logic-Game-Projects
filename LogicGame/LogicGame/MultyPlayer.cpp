#include "MultyPlayer.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

#define RESET   "\033[0m"
#define RED     "\033[31m"

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition; // used for goto

int cards[48];
int player1Cards[5];

void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}
void cardOrZero(int x, int y)
{
    gotoXY(x, y++); cout << " ___________________" << endl;
    gotoXY(x, y++); cout << "|        " << RED << "OR    " << RESET << "     |" << endl;
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
    gotoXY(x, y++); cout << "|        " << RED << "AND   " << RESET << "     |" << endl;
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
    gotoXY(x, y++); cout << "|        " << RED << "XOR    " << RESET << "    |" << endl;
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
    gotoXY(x, y++); cout << "|        " << RED << "OR     " << RESET << "    |" << endl;
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
    int cardCounter = 0;
    int pixelsX = 190;
    int pixelsY = 2;
    int selectedCards = 0;

    for (int i = 0; i < 63; i++)
    {

        gotoXY(185, i); cout << "|";
    }

    srand(time(NULL));

    while (selectedCards < 5)
    {
        int selectedCard = rand() % 6;

        if (selectedCard == 0)
        {
            cardOrZero(pixelsX, pixelsY);
            player1Cards[selectedCards] = 0;
        }
        else if (selectedCard == 1)
        {
            cardXorZero(pixelsX, pixelsY);
            player1Cards[selectedCards] = 1;
        }
        else if (selectedCard == 2)
        {
            cardAndZero(pixelsX, pixelsY);
            player1Cards[selectedCards] = 2;
        }
        else if (selectedCard == 3)
        {
            cardOrOne(pixelsX, pixelsY);
            player1Cards[selectedCards] = 3;
        }
        else if (selectedCard == 4)
        {
            cardXorOne(pixelsX, pixelsY);
            player1Cards[selectedCards] = 4;
        }
        else if (selectedCard == 5)
        {
            cardAndOne(pixelsX, pixelsY);
            player1Cards[selectedCards] = 5;
        }

        selectedCards++;
        cardCounter++;
        pixelsX += 22;

        if (cardCounter % 2 == 0 && cardCounter >= 2)
        {
            pixelsY += 10;
            pixelsX = 190;
        }
        if (cardCounter == 4)
        {
            pixelsX = 200;
        }


    }

}
void cardOne(int x, int y)
{
    gotoXY(x, y++); cout << " _____________" << endl;
    gotoXY(x, y++); cout << "|             |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << " __  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "/_ |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << " | |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << " | |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << " | |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << " |_|" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|_____________|" << endl;
}
void cardZero(int x, int y)
{
    gotoXY(x, y++); cout << " _____________" << endl;
    gotoXY(x, y++); cout << "|             |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << " ___ " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "/ _ \\" << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|   " << RED << "| | | |" << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|   " << RED << "| | | |" << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|   " << RED << "| |_| |" << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "\\___/" << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|_____________|" << endl;
}
void shuffleBoolCards()
{
    bool cards[6];
    int pixelsX = 70;
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
        }
        else
        {
            cardOne(pixelsX, pixelsY);
            cardZero(pixelsX + 15, pixelsY);
        }
        pixelsY += 10;
    }

}


void firstPlayer()
{

    int pixelsX;
    int pixelsY;

    displayCards(4);
    while (true)
    {
        char keyPress;
        keyPress = _getch();
        int asciiValue = keyPress;

        if (asciiValue == 49) // '1' ASCII code
        {
            pixelsX = 100;
            pixelsY = 7;

            if (player1Cards[0] == 0)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (player1Cards[0] == 1)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (player1Cards[0] == 2)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (player1Cards[0] == 3)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (player1Cards[0] == 4)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (player1Cards[0] == 5)
            {
                cardAndOne(pixelsX, pixelsY);
            }
        }
        if (asciiValue == 50)  // '2' ASCII code
        {
            pixelsY = 17;

            if (player1Cards[1] == 0)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (player1Cards[1] == 1)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (player1Cards[1] == 2)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (player1Cards[1] == 3)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (player1Cards[1] == 4)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (player1Cards[1] == 5)
            {
                cardAndOne(pixelsX, pixelsY);
            }
        }
        if (asciiValue == 51) // '3' ASCII code
        {
            pixelsY = 27;

            if (player1Cards[2] == 0)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (player1Cards[2] == 1)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (player1Cards[2] == 2)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (player1Cards[2] == 3)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (player1Cards[2] == 4)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (player1Cards[2] == 5)
            {
                cardAndOne(pixelsX, pixelsY);
            }
        }
        if (asciiValue == 52) // '4' ASCII code
        {
            pixelsY = 37;

            if (player1Cards[3] == 0)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (player1Cards[3] == 1)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (player1Cards[3] == 2)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (player1Cards[3] == 3)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (player1Cards[3] == 4)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (player1Cards[3] == 5)
            {
                cardAndOne(pixelsX, pixelsY);
            }
        }
        if (asciiValue == 53) // '5' ASCII code
        {
            pixelsY = 47;

            if (player1Cards[4] == 0)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (player1Cards[4] == 1)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (player1Cards[4] == 2)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (player1Cards[4] == 3)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (player1Cards[4] == 4)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (player1Cards[4] == 5)
            {
                cardAndOne(pixelsX, pixelsY);
            }
        }
    }
}

void secondPlayer()
{
    displayCards(4);
}

void beginingOfTheGameWithTwoPLayers()
{
    shuffleBoolCards();
    firstPlayer();
}