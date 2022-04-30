#include "MultyPlayer.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition; // used for goto

int cards[48];
int playerOneCards[5], playerTwoCards[5];

void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}
void cardOrZero(int x, int y)
{
    gotoXY(x, y++); cout << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "OR    " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "___" << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/ _ \\ " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | | " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | |  " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| |_| |   " << RESET << " |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "\\___/  " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void cardAndZero(int x, int y)
{
    gotoXY(x, y++); cout << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "AND   " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "___" << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/ _ \\ " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | | " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | |  " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| |_| |   " << RESET << " |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "\\___/  " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void cardXorZero(int x, int y)
{
    gotoXY(x, y++); cout << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "XOR    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "___" << RESET << "      |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/ _ \\ " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | | " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| | | |  " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "| |_| |   " << RESET << " |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "\\___/  " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void cardAndOne(int x, int y)
{
    gotoXY(x, y++); cout << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "AND    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "__" << RESET << "       |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/_ | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |   " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << " |_|  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void cardOrOne(int x, int y)
{
    gotoXY(x, y++); cout << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "OR     " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "__" << RESET << "       |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/_ | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |   " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << " |_|  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void cardXorOne(int x, int y)
{
    gotoXY(x, y++); cout << " _______________" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "XOR    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|      " << RED << "__" << RESET << "       |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << "/_ | " << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |   " << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << RED << "  | |    " << RESET << "  |" << endl;
    gotoXY(x, y++); cout << "|     " << RED << " |_|  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|_______________|" << endl;
}
void cardOne(int x, int y)
{
    gotoXY(x, y++); cout << " _____________" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " __  " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << "/_ |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " | |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " | |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " | |" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " |_|" << RESET << "     |" << endl;
    gotoXY(x, y++); cout << "|_____________|" << endl;
}
void cardZero(int x, int y)
{
    gotoXY(x, y++); cout << " _____________" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << " ___ " << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << "/ _ \\" << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|   " << YELLOW << "| | | |" << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|   " << YELLOW << "| | | |" << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|   " << YELLOW << "| |_| |" << RESET << "   |" << endl;
    gotoXY(x, y++); cout << "|    " << YELLOW << "\\___/" << RESET << "    |" << endl;
    gotoXY(x, y++); cout << "|_____________|" << endl;
}
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
        }
        else
        {
            cardOne(pixelsX, pixelsY);
            cardZero(pixelsX + 15, pixelsY);
        }
        pixelsY += 8;
    }

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

void displayCards(int cardsNeeded, int player)
{
    int cardCounter = 0;
    int pixelsX = 191;
    int pixelsY = 2;

    for (int i = 0; i < 63; i++)
    {
        gotoXY(187, i); cout << "|";
    }

    srand(time(NULL));

    if (player == 1)
    {
        for (int i = 0; i < 5; i++)
        {
            if (playerOneCards[i] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[i] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[i] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[i] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[i] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[i] % 6 == 0)
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
    else
    {
        for (int i = 0; i < 5; i++)
        {
            if (playerTwoCards[i] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[i] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[i] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[i] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[i] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[i] % 6 == 0)
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
    

    gotoXY(195, 50); 
    
    if (player == 1)
    {
        cout << "PLAYER 1";
    }
    else
    {
        cout << "PLAYER 2";
    }
}
void takeCards(int cardsNeeded, int player)
{
    if (cardsNeeded != 1)
    {
        for (int i = 0; i < cardsNeeded; i++)
        {
            if (player == 1)
            {
                playerOneCards[i] = cards[i];
            }
            else
            {
                playerTwoCards[i] = cards[i];
            }
        }
    }
    else
    {
        if (player == 1)
        {
            playerOneCards[4] = cards[0];
        }
        else
        {
            playerTwoCards[4] = cards[0];
        }
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



void firstPlayer()
{
    int pixelsX = 107;
    int pixelsY;

    takeCards(1, 1);
    displayCards(5, 1);

    while (true)
    {
        char keyPress;
        keyPress = _getch();
        int asciiValue = keyPress;

        if (asciiValue == 49) // '1' ASCII code
        {
            pixelsY = 4;

            if (playerOneCards[1] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 0)
            {
                cardAndOne(pixelsX, pixelsY);
            }

            break;
        }
        if (asciiValue == 50)  // '2' ASCII code
        {
            pixelsY = 13;

            if (playerOneCards[1] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 0)
            {
                cardAndOne(pixelsX, pixelsY);
            }

            break;
        }
        if (asciiValue == 51) // '3' ASCII code
        {
            pixelsY = 22;

            if (playerOneCards[1] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 0)
            {
                cardAndOne(pixelsX, pixelsY);
            }

            break;
        }
        if (asciiValue == 52) // '4' ASCII code
        {
            pixelsY = 31;

            if (playerOneCards[1] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 0)
            {
                cardAndOne(pixelsX, pixelsY);
            }

            break;
        }
        if (asciiValue == 53) // '5' ASCII code
        {
            pixelsY = 40;

            if (playerOneCards[1] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerOneCards[1] % 6 == 0)
            {
                cardAndOne(pixelsX, pixelsY);
            }

            break;
        }
    }
   
}

void secondPlayer()
{

    int pixelsX = 60;
    int pixelsY;

    takeCards(1, 2);
    displayCards(5, 2);



    while (true)
    {
        char keyPress;
        keyPress = _getch();
        int asciiValue = keyPress;

        if (asciiValue == 49) // '1' ASCII code
        {
            pixelsY = 4;

            if (playerTwoCards[1] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 0)
            {
                cardAndOne(pixelsX, pixelsY);
            }

            break;
        }
        if (asciiValue == 50)  // '2' ASCII code
        {
            pixelsY = 13;

            if (playerTwoCards[1] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 0)
            {
                cardAndOne(pixelsX, pixelsY);
            }

            break;
        }
        if (asciiValue == 51) // '3' ASCII code
        {
            pixelsY = 22;

            if (playerTwoCards[1] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 0)
            {
                cardAndOne(pixelsX, pixelsY);
            }

            break;
        }
        if (asciiValue == 52) // '4' ASCII code
        {
            pixelsY = 31;

            if (playerTwoCards[1] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 0)
            {
                cardAndOne(pixelsX, pixelsY);
            }

            break;
        }
        if (asciiValue == 53) // '5' ASCII code
        {
            pixelsY = 40;

            if (playerTwoCards[1] % 6 == 1)
            {
                cardOrZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 2)
            {
                cardXorZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 3)
            {
                cardAndZero(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 4)
            {
                cardOrOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 5)
            {
                cardXorOne(pixelsX, pixelsY);
            }
            else if (playerTwoCards[1] % 6 == 0)
            {
                cardAndOne(pixelsX, pixelsY);
            }

            break;
        }
    }
}

void beginingOfTheGameWithTwoPLayers()
{
    shuffleBoolCards();
    shuffleCards();

    takeCards(5, 1);
    takeCards(5, 2);
    
    while (true)
    {
        firstPlayer();
        secondPlayer();
    }
    
}