#include <iostream>
#include <string>
#include <windows.h>
#include "MultyPlayer.h"
#include "MultyPlayerWithNoCard.h"
#include "WithComputer.h"
#include "WithComputerWithNoCard.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"

using namespace std;


void twoPlayers()
{
    system("cls");
    cout << "This is two players game";
}
void onePlayer()
{
    system("cls");
    cout << "This is one player game";
}
void menu()
{
    string Menu[5] = { "     Play with a computer", "Play with computer with NO card", "      Play with a friend", "Play with a friend with NO card", "	         Exit" };
    int pointer = 0;

    while (true)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        for (int i = 0; i < 5; ++i)
        {
            if (i == pointer)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                gotoXY(85, 16 + i);  cout << Menu[i] << endl;
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                gotoXY(85, 16 + i); cout << Menu[i] << endl;
            }
        }

        while (true)
        {
            if (GetAsyncKeyState(VK_UP) != 0)
            {
                pointer -= 1;
                if (pointer == -1)
                {
                    pointer = 4;
                }
                break;
            }
            else if (GetAsyncKeyState(VK_DOWN) != 0)
            {
                pointer += 1;
                if (pointer == 5)
                {
                    pointer = 0;
                }
                break;
            }
            else if (GetAsyncKeyState(VK_RETURN) != 0)
            {
                switch (pointer)
                {
                case 0:
                {
                    onePlayer();
                    break;
                }
                case 1:
                {
                    twoPlayers();
                    break;
                }
                case 2:
                {
                    system("cls");
                    beginingOfTheGameWithTwoPLayers();
                }
                case 4:
                {
                    break;
                }
                }
            }
        }

        Sleep(150);
    }
}

void startProgram()
{
    gotoXY(79, 9);  cout << " _      ________   _________  __  _________" << endl;
    gotoXY(79, 10);  cout << "| | /| / / __/ /  / ___/ __ \\/  |/  / __/ /" << endl;
    gotoXY(79, 11);  cout << "| |/ |/ / _// /__/ /__/ /_/ / /|_/ / _//_/ " << endl;
    gotoXY(79, 12); cout << "|__/|__/___/____/\\___/\\____/_/  /_/___(_)" << endl;

    menu();
}

int main()
{
    startProgram();
}