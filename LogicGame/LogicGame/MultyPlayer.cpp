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
bool boolCardValuesP1[6], boolCardValuesP2[6];

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
            boolCardValuesP1[i] = 1;
            boolCardValuesP2[i] = 0;
        }
        else
        {
            cardOne(pixelsX, pixelsY);
            cardZero(pixelsX + 15, pixelsY);
            boolCardValuesP1[i] = 0;
            boolCardValuesP2[i] = 1;
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


void chooseCard(int* player)
{
    int Set[] = { 12, 7, 7, 7, 7 };
    int counter = 1;
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
    
    gotoXY(30, 3); cout << YELLOW << "Player 2's side" << RESET;

    gotoXY(139, 3); cout << YELLOW << "Player 1's side" << RESET;

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

void firstPlayer()
{
    gotoXY(195, 50); cout << "PLAYER 1";
    int pixelsX = 107;
    int pixelsY;

    displayCards(5, playerOneCards);
    chooseCard(playerOneCards);
    while (true)
    {
        char keyPress;
        keyPress = _getch();
        int asciiValue = keyPress;

        if (asciiValue == 49) // '1' ASCII code
        {
            pixelsY = 4;

            if (chosenCard % 6 == 1 && !(boolCardValuesP1[0] || boolCardValuesP1[1]))
            {
                cardOrZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValuesP1[0] ^ boolCardValuesP1[1]))
            {
                cardXorZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 3 && (boolCardValuesP1[0] && boolCardValuesP1[1]))
            {
                cardAndZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValuesP1[0] || boolCardValuesP1[1]))
            {
                cardOrOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValuesP1[0] ^ boolCardValuesP1[1]))
            {
                cardXorOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValuesP1[0] && boolCardValuesP1[1]))
            {
                cardAndOne(pixelsX, pixelsY);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
            }

        }
        if (asciiValue == 50)  // '2' ASCII code
        {
            pixelsY = 13;

            if (chosenCard % 6 == 1 && !(boolCardValuesP1[1] || boolCardValuesP1[2]))
            {
                cardOrZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValuesP1[1] ^ boolCardValuesP1[2]))
            {
                cardXorZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValuesP1[1] && boolCardValuesP1[2]))
            {
                cardAndZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValuesP1[1] || boolCardValuesP1[2]))
            {
                cardOrOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValuesP1[1] ^ boolCardValuesP1[2]))
            {
                cardXorOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValuesP1[1] && boolCardValuesP1[2]))
            {
                cardAndOne(pixelsX, pixelsY);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
            }
        }
        if (asciiValue == 51) // '3' ASCII code
        {
            pixelsY = 22;

            if (chosenCard % 6 == 1 && !(boolCardValuesP1[2] || boolCardValuesP1[3]))
            {
                cardOrZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValuesP1[2] ^ boolCardValuesP1[3]))
            {
                cardXorZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValuesP1[2] && boolCardValuesP1[3]))
            {
                cardAndZero(pixelsX, pixelsY);
                break;
            }
            else if ((chosenCard % 6 == 4) && (boolCardValuesP1[2] || boolCardValuesP1[3]))
            {
                cardOrOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValuesP1[2] ^ boolCardValuesP1[3]))
            {
                cardXorOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValuesP1[2] && boolCardValuesP1[3]))
            {
                cardAndOne(pixelsX, pixelsY);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
            }
        }
        if (asciiValue == 52) // '4' ASCII code
        {
            pixelsY = 31;

            if (chosenCard % 6 == 1 && !(boolCardValuesP1[3] || boolCardValuesP1[4]))
            {
                cardOrZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValuesP1[3] ^ boolCardValuesP1[4]))
            {
                cardXorZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValuesP1[3] && boolCardValuesP1[4]))
            {
                cardAndZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValuesP1[3] || boolCardValuesP1[4]))
            {
                cardOrOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValuesP1[3] ^ boolCardValuesP1[4]))
            {
                cardXorOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValuesP1[3] && boolCardValuesP1[4]))
            {
                cardAndOne(pixelsX, pixelsY);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
            }
        }
        if (asciiValue == 53) // '5' ASCII code
        {
            pixelsY = 40;

            if (chosenCard % 6 == 1 && !(boolCardValuesP1[4] || boolCardValuesP1[5]))
            {
                cardOrZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValuesP1[4] ^ boolCardValuesP1[5]))
            {
                cardXorZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValuesP1[4] && boolCardValuesP1[5]))
            {
                cardAndZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValuesP1[4] || boolCardValuesP1[5]))
            {
                cardOrOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValuesP1[4] ^ boolCardValuesP1[5]))
            {
                cardXorOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValuesP1[4] && boolCardValuesP1[5]))
            {
                cardAndOne(pixelsX, pixelsY);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
            }
        }
    }

}

void secondPlayer()
{

    gotoXY(195, 50); cout << "PLAYER 2";
    int pixelsX = 60;
    int pixelsY;

    takeCards(1, playerTwoCards);
    displayCards(5, playerTwoCards);
    chooseCard(playerTwoCards);
    while (true)
    {
        char keyPress;
        keyPress = _getch();
        int asciiValue = keyPress;

        if (asciiValue == 49) // '1' ASCII code
        {
            pixelsY = 4;

            if (chosenCard % 6 == 1 && !(boolCardValuesP2[0] || boolCardValuesP2[1]))
            {
                cardOrZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValuesP2[0] ^ boolCardValuesP2[1]))
            {
                cardXorZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 3 && boolCardValuesP2[0] && boolCardValuesP2[1])
            {
                cardAndZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValuesP2[0] || boolCardValuesP2[1]))
            {
                cardOrOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValuesP2[0] ^ boolCardValuesP2[1]))
            {
                cardXorOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValuesP2[0] && boolCardValuesP2[1]))
            {
                cardAndOne(pixelsX, pixelsY);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
            }

        }
        if (asciiValue == 50)  // '2' ASCII code
        {
            pixelsY = 13;

            if (chosenCard % 6 == 1 && !(boolCardValuesP2[1] || boolCardValuesP2[2]))
            {
                cardOrZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValuesP2[1] ^ boolCardValuesP2[2]))
            {
                cardXorZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValuesP2[1] && boolCardValuesP2[2]))
            {
                cardAndZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValuesP2[1] || boolCardValuesP2[2]))
            {
                cardOrOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValuesP2[1] ^ boolCardValuesP2[2]))
            {
                cardXorOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValuesP2[1] && boolCardValuesP2[2]))
            {
                cardAndOne(pixelsX, pixelsY);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
            }
        }
        if (asciiValue == 51) // '3' ASCII code
        {
            pixelsY = 22;

            if (chosenCard % 6 == 1 && !(boolCardValuesP2[2] || boolCardValuesP2[3]))
            {
                cardOrZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValuesP2[2] ^ boolCardValuesP2[3]))
            {
                cardXorZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValuesP2[2] && boolCardValuesP2[3]))
            {
                cardAndZero(pixelsX, pixelsY);
                break;
            }
            else if ((chosenCard % 6 == 4) && (boolCardValuesP2[2] || boolCardValuesP2[3]))
            {
                cardOrOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValuesP2[2] ^ boolCardValuesP2[3]))
            {
                cardXorOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValuesP2[2] && boolCardValuesP2[3]))
            {
                cardAndOne(pixelsX, pixelsY);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
            }
        }
        if (asciiValue == 52) // '4' ASCII code
        {
            pixelsY = 31;

            if (chosenCard % 6 == 1 && !(boolCardValuesP2[3] || boolCardValuesP2[4]))
            {
                cardOrZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValuesP2[3] ^ boolCardValuesP2[4]))
            {
                cardXorZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValuesP2[3] && boolCardValuesP2[4]))
            {
                cardAndZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValuesP2[3] || boolCardValuesP2[4]))
            {
                cardOrOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValuesP2[3] ^ boolCardValuesP2[4]))
            {
                cardXorOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValuesP2[3] && boolCardValuesP2[4]))
            {
                cardAndOne(pixelsX, pixelsY);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
            }
        }
        if (asciiValue == 53) // '5' ASCII code
        {
            pixelsY = 40;

            if (chosenCard % 6 == 1 && !(boolCardValuesP2[4] || boolCardValuesP2[5]))
            {
                cardOrZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 2 && !(boolCardValuesP2[4] ^ boolCardValuesP2[5]))
            {
                cardXorZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 3 && !(boolCardValuesP2[4] && boolCardValuesP2[5]))
            {
                cardAndZero(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 4 && (boolCardValuesP2[4] || boolCardValuesP2[5]))
            {
                cardOrOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 5 && (boolCardValuesP2[4] ^ boolCardValuesP2[5]))
            {
                cardXorOne(pixelsX, pixelsY);
                break;
            }
            else if (chosenCard % 6 == 0 && (boolCardValuesP2[4] && boolCardValuesP2[5]))
            {
                cardAndOne(pixelsX, pixelsY);
                break;
            }
            else
            {
                gotoXY(195, 50); cout << "Invalid!";
            }
        }
    }

}

void beginingOfTheGameWithTwoPLayers()
{
    shuffleBoolCards();
    shuffleCards();

    takeCards(5, playerOneCards);
    takeCards(5, playerTwoCards);

    while (true)
    {
        firstPlayer();
        secondPlayer();
    }
}