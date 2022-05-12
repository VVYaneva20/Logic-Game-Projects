#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "program.h"
#include "twoPlayersMode.h"
#include "twoPlayersWithNotCardMode.h"
#include "computerMode.h"
#include "computerWithNotCardMode.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

//display cards
void cardOrZero(int x, int y)
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
void cardAndZero(int x, int y)
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
void cardXorZero(int x, int y)
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
void cardAndOne(int x, int y)
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
void cardOrOne(int x, int y)
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
void cardXorOne(int x, int y)
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
void cardOne(int x, int y)
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
void cardZero(int x, int y)
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

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void instructions()
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
      |                                                         |
      |_________________________________________________________|

)" << endl;

    cout << R"(


       _________________________________________________________
      |                                                         |
      |                       HOW TO PLAY                       |
      |                                                         |
      |       with arrow up and arrow down - choose card        |
      |            with the key 'S' - select card               |
      |  with keys from '1' to '9' - choose a place for a card  |
      |        with the key 'D' - discard selected card         |
      |       with the key 'R'- return after wrong choce        |
      |     with the key 'Esc' - stop the game and go back      |
      |                                                         |
      |_________________________________________________________|

)" << endl;

    cardAndZero(191, 2);
    cardXorOne(191, 11);
    cardOrOne(191, 20);
    cardOrZero(191, 29);
    cardXorOne(191, 40);

    gotoXY(188, 2); cout << "/" << endl;
    gotoXY(187, 3); cout << "/" << endl;
    for (int i = 4; i <= 35; i++)
    {
        switch (i)
        {
        case 17:
            gotoXY(186, i); cout << "/" << endl;
            break;
        case 18:
            gotoXY(174, i); cout << "Cards that /" << endl;
            break;
        case 19:
            gotoXY(175, i); cout << "you have  \\" << endl;
            break;
        case 20:
            gotoXY(186, i); cout << "\\" << endl;
            break;
        default:
            gotoXY(186, i); cout << "|" << endl;
        }
    }
    gotoXY(187, 36); cout << "\\" << endl;
    gotoXY(188, 37); cout << "\\" << endl;

    gotoXY(166, 44); cout << "Random card that     ->" << endl;
    gotoXY(162, 45); cout << "is different every time" << endl;

    gotoXY(85, 3); cout << " _________________________________________________________" << endl;
    gotoXY(85, 4); cout << "|                                                         |" << endl;
    gotoXY(85, 5); cout << "|                         RULES:                          | " << endl;
    gotoXY(85, 6); cout << "|                                                         | " << endl;
    gotoXY(85, 7); cout << "|                                                         | " << endl;
    gotoXY(85, 8); cout << "|                       Game setup:                       | " << endl;
    gotoXY(85, 9); cout << "|                                                         | " << endl;
    gotoXY(85, 10); cout << "|   At the beginning of the game, all cards are shuffled  | " << endl;
    gotoXY(85, 11); cout << "|  and the six initial cards are placed so that the ‘1’   | " << endl;
    gotoXY(85, 12); cout << "|    side is facing the first player and the ‘0’ side     | " << endl;
    gotoXY(85, 13); cout << "|                is facing the other.                     | " << endl;
    gotoXY(85, 14); cout << "|                                                         | " << endl;
    gotoXY(85, 15); cout << "|                                                         | " << endl;
    gotoXY(85, 16); cout << "|                      Game play:                         | " << endl;
    gotoXY(85, 17); cout << "|                                                         | " << endl;
    gotoXY(85, 18); cout << "|   During each turn, the player is given a random card.  | " << endl;
    gotoXY(85, 19); cout << "| Then they can choose one of their cards and what to do  | " << endl;
    gotoXY(85, 20); cout << "| with it – play it or discard it. When the card is being | " << endl;
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
    gotoXY(85, 36); cout << "|      Wins the player who first finishes his pyramid.    | " << endl;
    gotoXY(85, 37); cout << "|                                                         | " << endl;
    gotoXY(85, 38); cout << "|                                                         | " << endl;
    gotoXY(85, 37); cout << "|                                                         | " << endl;
    gotoXY(85, 38); cout << "|                                                         | " << endl;
    gotoXY(85, 39); cout << "|_________________________________________________________|" << endl;

    char pressEscToGoBack;
    pressEscToGoBack = _getch();
    if (pressEscToGoBack == 27)
    {
        system("cls");
        startProgram();
    }
}

void startProgram()
{
    system("cls");

    gotoXY(83, 9);  cout << "   ___    ___  __    __ " << endl;
    gotoXY(83, 10);  cout << "  / __\\  /___\\/ /   /__\\/\\ /\\  /\\/\\" << endl;
    gotoXY(83, 11);  cout << " /__\\// //  // /   /_\\ / / \\ \\/    \\" << endl;
    gotoXY(83, 12); cout << "/ \\/  \\/ \\_// /___//__ \\ \\_/ / /\\/\\ \\" << endl;
    gotoXY(83, 13); cout << "\\_____/\\___/\\____/\\__/  \\___/\\/    \\/" << endl;
    int Set[] = { 12, 7, 7, 7, 7, 7 };
    int counter = 1;
    char key;
    while (true)
    {
        gotoXY(85, 16);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[0]);
        cout << "     Play with a computer";

        gotoXY(85, 17);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[1]);
        cout << "Play with computer with NOT card";

        gotoXY(85, 18);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[2]);
        cout << "      Play with a friend";

        gotoXY(85, 19);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[3]);
        cout << "Play with a friend with NOT card";

        gotoXY(85, 20);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[4]);
        cout << "	      Instructions";

        gotoXY(85, 21);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[5]);
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
                beginningOfTheGameWithComputer();
                break;
            }
            if (counter == 2)
            {
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
                beginningOfTheGameWithTwoPLayersNotCard();
                break;
            }
            if (counter == 5)
            {
                system("cls");
                instructions();
                break;
            }
            if (counter == 6)
            {
                break;
            }
        }

        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;
        Set[5] = 7;

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
        if (counter == 5)
        {
            Set[4] = 12;
        }
    }

    Sleep(150);
}


int main()
{
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    ShowConsoleCursor(false);
    startProgram();
}