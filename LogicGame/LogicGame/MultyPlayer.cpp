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
int playerOneCards[5], playerTwoCards[5], playerOneCardValues[5], playerTwoCardValues[5];
int chosenCard;
int counter;
bool  boolCardValuesP1[6], boolCardValuesP2[6];

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

void removeCard(int card, int *player)
{
    for (int i = card - 1; i < 5; ++i)
    {
        player[i] = player[i + 1];
    }
}

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
        if (key == 's')// enter key
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
void displayCards(int cardsNeeded, int* player)
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
void displayPositions()
{
    gotoXY(107, 4); cout << " _______________" << endl;
    gotoXY(107, 5); cout << "|    POSITION   |" << endl;
    gotoXY(107, 6); cout << "|               |" << endl;
    gotoXY(107, 7); cout << "|               |" << endl;
    gotoXY(107, 8); cout << "|       1       |" << endl;
    gotoXY(107, 9); cout << "|               |" << endl;
    gotoXY(107, 10); cout << "|               |" << endl;
    gotoXY(107, 11); cout << "|               |" << endl;
    gotoXY(107, 12); cout << "|_______________|" << endl;

    gotoXY(60, 4); cout << " _______________" << endl;
    gotoXY(60, 5); cout << "|    POSITION   |" << endl;
    gotoXY(60, 6); cout << "|               |" << endl;
    gotoXY(60, 7); cout << "|               |" << endl;
    gotoXY(60, 8); cout << "|       1       |" << endl;
    gotoXY(60, 9); cout << "|               |" << endl;
    gotoXY(60, 10); cout << "|               |" << endl;
    gotoXY(60, 11); cout << "|               |" << endl;
    gotoXY(60, 12); cout << "|_______________|" << endl;

    gotoXY(107, 13); cout << " _______________" << endl;
    gotoXY(107, 14); cout << "|    POSITION   |" << endl;
    gotoXY(107, 15); cout << "|               |" << endl;
    gotoXY(107, 16); cout << "|               |" << endl;
    gotoXY(107, 17); cout << "|       2       |" << endl;
    gotoXY(107, 18); cout << "|               |" << endl;
    gotoXY(107, 19); cout << "|               |" << endl;
    gotoXY(107, 20); cout << "|               |" << endl;
    gotoXY(107, 21); cout << "|_______________|" << endl;

    gotoXY(60, 13); cout << " _______________" << endl;
    gotoXY(60, 14); cout << "|    POSITION   |" << endl;
    gotoXY(60, 15); cout << "|               |" << endl;
    gotoXY(60, 16); cout << "|               |" << endl;
    gotoXY(60, 17); cout << "|       2       |" << endl;
    gotoXY(60, 18); cout << "|               |" << endl;
    gotoXY(60, 19); cout << "|               |" << endl;
    gotoXY(60, 20); cout << "|               |" << endl;
    gotoXY(60, 21); cout << "|_______________|" << endl;

    gotoXY(107, 22); cout << " _______________" << endl;
    gotoXY(107, 23); cout << "|    POSITION   |" << endl;
    gotoXY(107, 24); cout << "|               |" << endl;
    gotoXY(107, 25); cout << "|               |" << endl;
    gotoXY(107, 26); cout << "|       3       |" << endl;
    gotoXY(107, 27); cout << "|               |" << endl;
    gotoXY(107, 28); cout << "|               |" << endl;
    gotoXY(107, 29); cout << "|               |" << endl;
    gotoXY(107, 30); cout << "|_______________|" << endl;

    gotoXY(60, 22); cout << " _______________" << endl;
    gotoXY(60, 23); cout << "|    POSITION   |" << endl;
    gotoXY(60, 24); cout << "|               |" << endl;
    gotoXY(60, 25); cout << "|               |" << endl;
    gotoXY(60, 26); cout << "|       3       |" << endl;
    gotoXY(60, 27); cout << "|               |" << endl;
    gotoXY(60, 28); cout << "|               |" << endl;
    gotoXY(60, 29); cout << "|               |" << endl;
    gotoXY(60, 30); cout << "|_______________|" << endl;

    gotoXY(107, 31); cout << " _______________" << endl;
    gotoXY(107, 32); cout << "|    POSITION   |" << endl;
    gotoXY(107, 33); cout << "|               |" << endl;
    gotoXY(107, 34); cout << "|               |" << endl;
    gotoXY(107, 35); cout << "|       4       |" << endl;
    gotoXY(107, 36); cout << "|               |" << endl;
    gotoXY(107, 37); cout << "|               |" << endl;
    gotoXY(107, 38); cout << "|               |" << endl;
    gotoXY(107, 39); cout << "|_______________|" << endl;

    gotoXY(60, 31); cout << " _______________" << endl;
    gotoXY(60, 32); cout << "|    POSITION   |" << endl;
    gotoXY(60, 33); cout << "|               |" << endl;
    gotoXY(60, 34); cout << "|               |" << endl;
    gotoXY(60, 35); cout << "|       4       |" << endl;
    gotoXY(60, 36); cout << "|               |" << endl;
    gotoXY(60, 37); cout << "|               |" << endl;
    gotoXY(60, 38); cout << "|               |" << endl;
    gotoXY(60, 39); cout << "|_______________|" << endl;

    gotoXY(107, 40); cout << " _______________" << endl;
    gotoXY(107, 41); cout << "|    POSITION   |" << endl;
    gotoXY(107, 42); cout << "|               |" << endl;
    gotoXY(107, 43); cout << "|               |" << endl;
    gotoXY(107, 44); cout << "|       5       |" << endl;
    gotoXY(107, 45); cout << "|               |" << endl;
    gotoXY(107, 46); cout << "|               |" << endl;
    gotoXY(107, 47); cout << "|               |" << endl;
    gotoXY(107, 48); cout << "|_______________|" << endl;

    gotoXY(60, 40); cout << " _______________" << endl;
    gotoXY(60, 41); cout << "|    POSITION   |" << endl;
    gotoXY(60, 42); cout << "|               |" << endl;
    gotoXY(60, 43); cout << "|               |" << endl;
    gotoXY(60, 44); cout << "|       5       |" << endl;
    gotoXY(60, 45); cout << "|               |" << endl;
    gotoXY(60, 46); cout << "|               |" << endl;
    gotoXY(60, 47); cout << "|               |" << endl;
    gotoXY(60, 48); cout << "|_______________|" << endl;

    gotoXY(122, 8); cout << " _______________" << endl;
    gotoXY(122, 9); cout << "|    POSITION   |" << endl;
    gotoXY(122, 10); cout << "|               |" << endl;
    gotoXY(122, 11); cout << "|               |" << endl;
    gotoXY(122, 12); cout << "|       6       |" << endl;
    gotoXY(122, 13); cout << "|               |" << endl;
    gotoXY(122, 14); cout << "|               |" << endl;
    gotoXY(122, 15); cout << "|               |" << endl;
    gotoXY(122, 16); cout << "|_______________|" << endl;

    gotoXY(47, 8); cout << " _______________" << endl;
    gotoXY(47, 9); cout << "|    POSITION   |" << endl;
    gotoXY(47, 10); cout << "|               |" << endl;
    gotoXY(47, 11); cout << "|               |" << endl;
    gotoXY(47, 12); cout << "|       6       |" << endl;
    gotoXY(47, 13); cout << "|               |" << endl;
    gotoXY(47, 14); cout << "|               |" << endl;
    gotoXY(47, 15); cout << "|               |" << endl;
    gotoXY(47, 16); cout << "|_______________|" << endl;

    gotoXY(122, 18); cout << " _______________" << endl;
    gotoXY(122, 19); cout << "|    POSITION   |" << endl;
    gotoXY(122, 20); cout << "|               |" << endl;
    gotoXY(122, 21); cout << "|               |" << endl;
    gotoXY(122, 22); cout << "|       7       |" << endl;
    gotoXY(122, 23); cout << "|               |" << endl;
    gotoXY(122, 24); cout << "|               |" << endl;
    gotoXY(122, 25); cout << "|               |" << endl;
    gotoXY(122, 26); cout << "|_______________|" << endl;

    gotoXY(47, 18); cout << " _______________" << endl;
    gotoXY(47, 19); cout << "|    POSITION   |" << endl;
    gotoXY(47, 20); cout << "|               |" << endl;
    gotoXY(47, 21); cout << "|               |" << endl;
    gotoXY(47, 22); cout << "|       7       |" << endl;
    gotoXY(47, 23); cout << "|               |" << endl;
    gotoXY(47, 24); cout << "|               |" << endl;
    gotoXY(47, 25); cout << "|               |" << endl;
    gotoXY(47, 26); cout << "|_______________|" << endl;

    gotoXY(122, 28); cout << " _______________" << endl;
    gotoXY(122, 29); cout << "|    POSITION   |" << endl;
    gotoXY(122, 30); cout << "|               |" << endl;
    gotoXY(122, 31); cout << "|               |" << endl;
    gotoXY(122, 32); cout << "|       8       |" << endl;
    gotoXY(122, 33); cout << "|               |" << endl;
    gotoXY(122, 34); cout << "|               |" << endl;
    gotoXY(122, 35); cout << "|               |" << endl;
    gotoXY(122, 36); cout << "|_______________|" << endl;

    gotoXY(47, 28); cout << " _______________" << endl;
    gotoXY(47, 29); cout << "|    POSITION   |" << endl;
    gotoXY(47, 30); cout << "|               |" << endl;
    gotoXY(47, 31); cout << "|               |" << endl;
    gotoXY(47, 32); cout << "|       8       |" << endl;
    gotoXY(47, 33); cout << "|               |" << endl;
    gotoXY(47, 34); cout << "|               |" << endl;
    gotoXY(47, 35); cout << "|               |" << endl;
    gotoXY(47, 36); cout << "|_______________|" << endl;

    gotoXY(122, 38); cout << " _______________" << endl;
    gotoXY(122, 39); cout << "|    POSITION   |" << endl;
    gotoXY(122, 40); cout << "|               |" << endl;
    gotoXY(122, 41); cout << "|               |" << endl;
    gotoXY(122, 42); cout << "|       9       |" << endl;
    gotoXY(122, 43); cout << "|               |" << endl;
    gotoXY(122, 44); cout << "|               |" << endl;
    gotoXY(122, 45); cout << "|               |" << endl;
    gotoXY(122, 46); cout << "|_______________|" << endl;

    gotoXY(47, 38); cout << " _______________" << endl;
    gotoXY(47, 39); cout << "|    POSITION   |" << endl;
    gotoXY(47, 40); cout << "|               |" << endl;
    gotoXY(47, 41); cout << "|               |" << endl;
    gotoXY(47, 42); cout << "|       9       |" << endl;
    gotoXY(47, 43); cout << "|               |" << endl;
    gotoXY(47, 44); cout << "|               |" << endl;
    gotoXY(47, 45); cout << "|               |" << endl;
    gotoXY(47, 46); cout << "|_______________|" << endl;

    gotoXY(137, 12); cout << " _______________" << endl;
    gotoXY(137, 13); cout << "|    POSITION   |" << endl;
    gotoXY(137, 14); cout << "|               |" << endl;
    gotoXY(137, 15); cout << "|               |" << endl;
    gotoXY(137, 16); cout << "|      10       |" << endl;
    gotoXY(137, 17); cout << "|               |" << endl;
    gotoXY(137, 18); cout << "|               |" << endl;
    gotoXY(137, 19); cout << "|               |" << endl;
    gotoXY(137, 20); cout << "|_______________|" << endl;

    gotoXY(32, 12); cout << " _______________" << endl;
    gotoXY(32, 13); cout << "|    POSITION   |" << endl;
    gotoXY(32, 14); cout << "|               |" << endl;
    gotoXY(32, 15); cout << "|               |" << endl;
    gotoXY(32, 16); cout << "|       10      |" << endl;
    gotoXY(32, 17); cout << "|               |" << endl;
    gotoXY(32, 18); cout << "|               |" << endl;
    gotoXY(32, 19); cout << "|               |" << endl;
    gotoXY(32, 20); cout << "|_______________|" << endl;

    gotoXY(137, 23); cout << " _______________" << endl;
    gotoXY(137, 24); cout << "|    POSITION   |" << endl;
    gotoXY(137, 25); cout << "|               |" << endl;
    gotoXY(137, 26); cout << "|               |" << endl;
    gotoXY(137, 27); cout << "|      11       |" << endl;
    gotoXY(137, 28); cout << "|               |" << endl;
    gotoXY(137, 29); cout << "|               |" << endl;
    gotoXY(137, 30); cout << "|               |" << endl;
    gotoXY(137, 31); cout << "|_______________|" << endl;

    gotoXY(32, 23); cout << " _______________" << endl;
    gotoXY(32, 24); cout << "|    POSITION   |" << endl;
    gotoXY(32, 25); cout << "|               |" << endl;
    gotoXY(32, 26); cout << "|               |" << endl;
    gotoXY(32, 27); cout << "|       11      |" << endl;
    gotoXY(32, 28); cout << "|               |" << endl;
    gotoXY(32, 29); cout << "|               |" << endl;
    gotoXY(32, 30); cout << "|               |" << endl;
    gotoXY(32, 31); cout << "|_______________|" << endl;

    gotoXY(137, 34); cout << " _______________" << endl;
    gotoXY(137, 35); cout << "|    POSITION   |" << endl;
    gotoXY(137, 36); cout << "|               |" << endl;
    gotoXY(137, 37); cout << "|               |" << endl;
    gotoXY(137, 38); cout << "|      12       |" << endl;
    gotoXY(137, 39); cout << "|               |" << endl;
    gotoXY(137, 40); cout << "|               |" << endl;
    gotoXY(137, 41); cout << "|               |" << endl;
    gotoXY(137, 42); cout << "|_______________|" << endl;

    gotoXY(32, 34); cout << " _______________" << endl;
    gotoXY(32, 35); cout << "|    POSITION   |" << endl;
    gotoXY(32, 36); cout << "|               |" << endl;
    gotoXY(32, 37); cout << "|               |" << endl;
    gotoXY(32, 38); cout << "|       12      |" << endl;
    gotoXY(32, 39); cout << "|               |" << endl;
    gotoXY(32, 40); cout << "|               |" << endl;
    gotoXY(32, 41); cout << "|               |" << endl;
    gotoXY(32, 42); cout << "|_______________|" << endl;

    gotoXY(152, 17); cout << " _______________" << endl;
    gotoXY(152, 18); cout << "|    POSITION   |" << endl;
    gotoXY(152, 19); cout << "|               |" << endl;
    gotoXY(152, 20); cout << "|               |" << endl;
    gotoXY(152, 21); cout << "|      13       |" << endl;
    gotoXY(152, 22); cout << "|               |" << endl;
    gotoXY(152, 23); cout << "|               |" << endl;
    gotoXY(152, 24); cout << "|               |" << endl;
    gotoXY(152, 25); cout << "|_______________|" << endl;

    gotoXY(17, 17); cout << " _______________" << endl;
    gotoXY(17, 18); cout << "|    POSITION   |" << endl;
    gotoXY(17, 19); cout << "|               |" << endl;
    gotoXY(17, 20); cout << "|               |" << endl;
    gotoXY(17, 21); cout << "|       13      |" << endl;
    gotoXY(17, 22); cout << "|               |" << endl;
    gotoXY(17, 23); cout << "|               |" << endl;
    gotoXY(17, 24); cout << "|               |" << endl;
    gotoXY(17, 25); cout << "|_______________|" << endl;

    gotoXY(152, 29); cout << " _______________" << endl;
    gotoXY(152, 30); cout << "|    POSITION   |" << endl;
    gotoXY(152, 31); cout << "|               |" << endl;
    gotoXY(152, 32); cout << "|               |" << endl;
    gotoXY(152, 33); cout << "|      14       |" << endl;
    gotoXY(152, 34); cout << "|               |" << endl;
    gotoXY(152, 35); cout << "|               |" << endl;
    gotoXY(152, 36); cout << "|               |" << endl;
    gotoXY(152, 37); cout << "|_______________|" << endl;

    gotoXY(17, 29); cout << " _______________" << endl;
    gotoXY(17, 30); cout << "|    POSITION   |" << endl;
    gotoXY(17, 31); cout << "|               |" << endl;
    gotoXY(17, 32); cout << "|               |" << endl;
    gotoXY(17, 33); cout << "|       14      |" << endl;
    gotoXY(17, 34); cout << "|               |" << endl;
    gotoXY(17, 35); cout << "|               |" << endl;
    gotoXY(17, 36); cout << "|               |" << endl;
    gotoXY(17, 37); cout << "|_______________|" << endl;

    gotoXY(167, 23); cout << " _______________" << endl;
    gotoXY(167, 24); cout << "|    POSITION   |" << endl;
    gotoXY(167, 25); cout << "|               |" << endl;
    gotoXY(167, 26); cout << "|               |" << endl;
    gotoXY(167, 27); cout << "|      15       |" << endl;
    gotoXY(167, 28); cout << "|               |" << endl;
    gotoXY(167, 29); cout << "|               |" << endl;
    gotoXY(167, 30); cout << "|               |" << endl;
    gotoXY(167, 31); cout << "|_______________|" << endl;

    gotoXY(2, 23); cout << " _______________" << endl;
    gotoXY(2, 24); cout << "|    POSITION   |" << endl;
    gotoXY(2, 25); cout << "|               |" << endl;
    gotoXY(2, 26); cout << "|               |" << endl;
    gotoXY(2, 27); cout << "|       15      |" << endl;
    gotoXY(2, 28); cout << "|               |" << endl;
    gotoXY(2, 29); cout << "|               |" << endl;
    gotoXY(2, 30); cout << "|               |" << endl;
    gotoXY(2, 31); cout << "|_______________|" << endl;
}
void placeCard(int* player, bool* boolCardValues, int x)
{
    int pixelsX = x;
    int pixelsY;

    while (true)
    {
        char keyPress;
        keyPress = _getch();
        int asciiValue = keyPress;

        if (asciiValue == 49) // '1' ASCII code
        {
            pixelsY = 4;

            if (chosenCard % 6 == 1 && !(boolCardValues[0] || boolCardValues[1]))
            {
                cardOrZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValues[0] ^ boolCardValues[1]))
            {
                cardXorZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValues[0] && boolCardValues[1]))
            {
                cardAndZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValues[0] || boolCardValues[1]))
            {
                cardOrOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValues[0] ^ boolCardValues[1]))
            {
                cardXorOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValues[0] && boolCardValues[1]))
            {
                cardAndOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
                continue;
            }

        }
        if (asciiValue == 50)  // '2' ASCII code
        {
            pixelsY = 13;

            if (chosenCard % 6 == 1 && !(boolCardValues[1] || boolCardValues[2]))
            {
                cardOrZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValues[1] ^ boolCardValues[2]))
            {
                cardXorZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValues[1] && boolCardValues[2]))
            {
                cardAndZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValues[1] || boolCardValues[2]))
            {
                cardOrOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValues[1] ^ boolCardValues[2]))
            {
                cardXorOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValues[1] && boolCardValues[2]))
            {
                cardAndOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
                continue;
            }
        }
        if (asciiValue == 51) // '3' ASCII code
        {
            pixelsY = 22;

            if (chosenCard % 6 == 1 && !(boolCardValues[2] || boolCardValues[3]))
            {
                cardOrZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValues[2] ^ boolCardValues[3]))
            {
                cardXorZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValues[2] && boolCardValues[3]))
            {
                cardAndZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if ((chosenCard % 6 == 4) && (boolCardValues[2] || boolCardValues[3]))
            {
                cardOrOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValues[2] ^ boolCardValues[3]))
            {
                cardXorOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValues[2] && boolCardValues[3]))
            {
                cardAndOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
                continue;
            }
        }
        if (asciiValue == 52) // '4' ASCII code
        {
            pixelsY = 31;

            if (chosenCard % 6 == 1 && !(boolCardValues[3] || boolCardValues[4]))
            {
                cardOrZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValues[3] ^ boolCardValues[4]))
            {
                cardXorZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValues[3] && boolCardValues[4]))
            {
                cardAndZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValues[3] || boolCardValues[4]))
            {
                cardOrOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValues[3] ^ boolCardValues[4]))
            {
                cardXorOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValues[3] && boolCardValues[4]))
            {
                cardAndOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
                continue;
            }
        }
        if (asciiValue == 53) // '5' ASCII code
        {
            pixelsY = 40;

            if (chosenCard % 6 == 1 && !(boolCardValues[4] || boolCardValues[5]))
            {
                cardOrZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValues[4] ^ boolCardValues[5]))
            {
                cardXorZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValues[4] && boolCardValues[5]))
            {
                cardAndZero(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValues[4] || boolCardValues[5]))
            {
                cardOrOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValues[4] ^ boolCardValues[5]))
            {
                cardXorOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValues[4] && boolCardValues[5]))
            {
                cardAndOne(pixelsX, pixelsY);
                removeCard(counter, player);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
                continue;
            }
            
        }
        if (asciiValue == 114)// 'r' ASCII value
        {
            chooseCard(player);
            placeCard(player, boolCardValues, pixelsX);
            break;
        }
    }
}
void firstPlayer()
{
    displayCards(5, playerOneCards);
    chooseCard(playerOneCards);
    placeCard(playerOneCards, boolCardValuesP1 ,60);

}
void secondPlayer()
{
    displayCards(5, playerTwoCards);
    chooseCard(playerTwoCards);
    placeCard(playerTwoCards, boolCardValuesP2, 107);
    
}


void beginingOfTheGameWithTwoPLayers()
{
    shuffleBoolCards();
    shuffleCards();

    takeCards(5, playerTwoCards);
    takeCards(5, playerOneCards);

    displayPositions();

    while (true)
    {

        gotoXY(195, 50); cout << "PLAYER 1";
        takeCards(1, playerOneCards);
        firstPlayer();

        gotoXY(195, 50); cout << "PLAYER 2";
        takeCards(1, playerTwoCards);
        secondPlayer();
    }
}