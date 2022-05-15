#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "program.h"
#include "twoPlayersMode.h"

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m"

using namespace std;

void (*pointToCard[6])(int x, int y) = { cardOrZero, cardXorZero, cardAndZero, cardOrOne, cardXorOne, cardAndOne };



//display the empty positions
void printPositions(int player, bool* isOccupied)
{
    int posCoordinates[15][3] = { {60, 107, 4}, {60, 107, 13}, {60, 107, 22}, {60, 107, 31}, {60, 107, 40},
                                 {47, 122, 8}, {47, 122, 18}, {47, 122, 28}, {47, 122, 38},
                                 {32, 137, 12}, {32, 137, 23}, {32, 137, 34},
                                 {17, 152, 17}, {17, 152, 29},
                                 {2, 167, 23} };
    int xFirstFive, y, x, xP2;
    if (player == 1)
        xFirstFive = 60;
    else
        xFirstFive = 107;


    for (int i = 0; i < 5; i++)
    {
        y = posCoordinates[i][2];
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
    }
    int inColumn = 4;
    int position = 6;

    for (int i = 5; i < 15; i++)
    {
        x = posCoordinates[i][player - 1];
        y = posCoordinates[i][2];
        if (i == 9)
        {
            position = 1;
        }
        if (isOccupied[i - inColumn] and isOccupied[i - inColumn - 1] and (!isOccupied[i]))
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
        position++;
        if (i == 8 or i == 11 or i == 13)
        {
            inColumn--;
        }
    }
}

//put down a card in a chosen position
void placeCard(bool* occupiedPositions, int index, int pointerIndex, int x, int y, bool* cardValues, bool value, int* playersCards)
{
    occupiedPositions[index] = 1;
    pointToCard[pointerIndex](x, y);
    cardValues[index] = value;
    removeCard(counter, playersCards);
}

//put down a card in a chosen position
void checkCard(int* playersCards, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues)
{
    int posCoordinates[15][3] = { {60, 107, 4}, {60, 107, 13}, {60, 107, 22}, {60, 107, 31}, {60, 107, 40},
                                 {47, 122, 8}, {47, 122, 18}, {47, 122, 28}, {47, 122, 38},
                                 {32, 137, 12}, {32, 137, 23}, {32, 137, 34},
                                 {17, 152, 17}, {17, 152, 29},
                                 {2, 167, 23} };
    int pixelsX;
    int pixelsY;
    int inColumn[15] = { 5, 5, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 2, 2, 1 };
    int x = 2;

    //bool isNum = 0; 

    while (true)
    {
        char keyPress = _getch();
        int choice = keyPress - 49;

        bool flag = true;

        for (int i = 0; i < 9; i++)
        {
            if (choice != i)
                flag = false;
            else
            {
                //isNum = true;
                flag = true;
                break;
            }
        }

        //gotoXY(2, x++); cout << flag;

        for (int i = 0; i < 9; i++)
        {
            if (i == choice)
            {
                if (occupiedPositions[i] == 0 or i >= 6)
                {
                    pixelsX = posCoordinates[i][player - 1];
                    pixelsY = posCoordinates[i][2];
                }
                else
                {
                    pixelsX = posCoordinates[i + 9][player - 1];
                    pixelsY = posCoordinates[i + 9][2];
                }

                if (occupiedPositions[i] == 0 && i <= 4)
                {
                    if (chosenCard % 6 == 1 && !(boolCardValues[i + 1] || boolCardValues[i]))
                    {
                        placeCard(occupiedPositions, i, 0, pixelsX, pixelsY, cardValues, 0, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 2 && !(boolCardValues[i + 1] ^ boolCardValues[i]))
                    {
                        placeCard(occupiedPositions, i, 1, pixelsX, pixelsY, cardValues, 0, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 3 && !(boolCardValues[i + 1] && boolCardValues[i]))
                    {
                        placeCard(occupiedPositions, i, 2, pixelsX, pixelsY, cardValues, 0, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 4 && (boolCardValues[i + 1] || boolCardValues[i]))
                    {
                        placeCard(occupiedPositions, i, 3, pixelsX, pixelsY, cardValues, 1, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 5 && (boolCardValues[i + 1] ^ boolCardValues[i]))
                    {
                        placeCard(occupiedPositions, i, 4, pixelsX, pixelsY, cardValues, 1, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 0 && (boolCardValues[i + 1] && boolCardValues[i]))
                    {
                        placeCard(occupiedPositions, i, 5, pixelsX, pixelsY, cardValues, 1, playersCards);
                        break;
                    }
                    else
                    {
                        gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                        flag = false;
                    }
                }
                else if (i >= 5 && occupiedPositions[i] == 0)
                {
                    if (chosenCard % 6 == 1 && !(cardValues[i - inColumn[i]] || cardValues[i - inColumn[i] - 1]) && occupiedPositions[i - inColumn[i]] == 1 && occupiedPositions[i - inColumn[i] - 1] == 1)
                    {
                        placeCard(occupiedPositions, i, 0, pixelsX, pixelsY, cardValues, 0, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 2 && !(cardValues[i - inColumn[i]] ^ cardValues[i - inColumn[i] - 1]) && occupiedPositions[i - inColumn[i]] == 1 && occupiedPositions[i - inColumn[i] - 1] == 1)
                    {
                        placeCard(occupiedPositions, i, 1, pixelsX, pixelsY, cardValues, 0, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 3 && !(cardValues[i - inColumn[i]] && cardValues[i - inColumn[i] - 1]) && occupiedPositions[i - inColumn[i]] == 1 && occupiedPositions[i - inColumn[i] - 1] == 1)
                    {
                        placeCard(occupiedPositions, i, 2, pixelsX, pixelsY, cardValues, 0, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 4 && (cardValues[i - inColumn[i]] || cardValues[i - inColumn[i] - 1]) && occupiedPositions[i - inColumn[i]] == 1 && occupiedPositions[i - inColumn[i] - 1] == 1)
                    {
                        placeCard(occupiedPositions, i, 3, pixelsX, pixelsY, cardValues, 1, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 5 && (cardValues[i - inColumn[i]] ^ cardValues[i - inColumn[i] - 1]) && occupiedPositions[i - inColumn[i]] == 1 && occupiedPositions[i - inColumn[i] - 1] == 1)
                    {
                        placeCard(occupiedPositions, i, 4, pixelsX, pixelsY, cardValues, 1, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 0 && (cardValues[i - inColumn[i]] && cardValues[i - inColumn[i] - 1]) && occupiedPositions[i - inColumn[i]] == 1 && occupiedPositions[i - inColumn[i] - 1] == 1)
                    {
                        placeCard(occupiedPositions, i, 5, pixelsX, pixelsY, cardValues, 1, playersCards);
                        break;
                    }
                    else
                    {
                        gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                        flag = false;
                    }
                }
                else if (occupiedPositions[i + 9] == 0 && i <= 5)
                {
                    if (chosenCard % 6 == 1 && !(cardValues[i + 8 - inColumn[i + 9]] || cardValues[i + 9 - inColumn[i + 9]]) && occupiedPositions[i + 8 - inColumn[i + 9]] == 1 && occupiedPositions[i + 9 - inColumn[i + 9]] == 1)
                    {
                        placeCard(occupiedPositions, i + 9, 0, pixelsX, pixelsY, cardValues, 0, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 2 && !(cardValues[i + 8 - inColumn[i + 9]] ^ cardValues[i + 9 - inColumn[i + 9]]) && occupiedPositions[i + 8 - inColumn[i + 9]] == 1 && occupiedPositions[i + 9 - inColumn[i + 9]] == 1)
                    {
                        placeCard(occupiedPositions, i + 9, 1, pixelsX, pixelsY, cardValues, 0, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 3 && !(cardValues[i + 8 - inColumn[i + 9]] && cardValues[i + 9 - inColumn[i + 9]]) && occupiedPositions[i + 8 - inColumn[i + 9]] == 1 && occupiedPositions[i + 9 - inColumn[i + 9]] == 1)
                    {
                        placeCard(occupiedPositions, i + 9, 2, pixelsX, pixelsY, cardValues, 0, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 4 && (cardValues[i + 8 - inColumn[i + 9]] || cardValues[i + 9 - inColumn[i + 9]]) && occupiedPositions[i + 8 - inColumn[i + 9]] == 1 && occupiedPositions[i + 9 - inColumn[i + 9]] == 1)
                    {
                        placeCard(occupiedPositions, i + 9, 3, pixelsX, pixelsY, cardValues, 1, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 5 && (cardValues[i + 8 - inColumn[i + 9]] ^ cardValues[i + 9 - inColumn[i + 9]]) && occupiedPositions[i + 8 - inColumn[i + 9]] == 1 && occupiedPositions[i + 9 - inColumn[i + 9]] == 1)
                    {
                        placeCard(occupiedPositions, i + 9, 4, pixelsX, pixelsY, cardValues, 1, playersCards);
                        break;
                    }
                    else if (chosenCard % 6 == 0 && (cardValues[i + 8 - inColumn[i + 9]] && cardValues[i + 9 - inColumn[i + 9]]) && occupiedPositions[i + 8 - inColumn[i + 9]] == 1 && occupiedPositions[i + 9 - inColumn[i + 9]] == 1)
                    {
                        placeCard(occupiedPositions, i + 9, 5, pixelsX, pixelsY, cardValues, 1, playersCards);
                        break;
                    }
                    else
                    {
                        gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                        flag = false;
                    }
                }
                else
                {
                    gotoXY(195, 50); cout << RED << "Invalid!" << RESET;
                    flag = false;
                }
            }
        }

        if (choice == 65 or choice == 33 or choice == -81 or choice == -161)
        {
            gotoXY(195, 50); cout << "PLAYER " << player << "  ";
            chooseCard(playersCards, 1, 0);
            checkCard(playersCards, boolCardValues, player, occupiedPositions, cardValues);
            break;
        }
        if (choice == 51 or choice == 19 or choice == -141 or choice == -173)
        {
            removeCard(counter, playersCards);
            break;
        }
        if (GetAsyncKeyState(VK_ESCAPE))// escape ASCII value
        {
            startProgram();
            break;
        }

        if (flag) break;
    }
}

// implements the players' turns
void executeTurn(int* playerCards, bool* boolCardValues, int player, bool* isOccupied, bool* cardValues)
{
    int yCoords[5] = { 6, 15, 24, 33, 44 };

    printPositions(1, isOccupiedP1);   // printPositions(player, isOccupied);
    printPositions(2, isOccupiedP2);
    gotoXY(195, 50); cout << "PLAYER " << player;

    takeCards(1, playerCards, 48);
    printCards(playerCards);

    chooseCard(playerCards, 0, 0);
    checkCard(playerCards, boolCardValues, player, isOccupied, cardValues);
    gotoXY(189, yCoords[counter]); cout << " ";
}

//start the game
void beginningOfTheGameWithTwoPLayers()
{
    fill_n(cards, 48, 0);

    fill_n(playerOneCards, 5, 0);
    fill_n(playerTwoCards, 5, 0);

    fill_n(boolCardValuesP1, 6, 0);
    fill_n(boolCardValuesP2, 6, 0);

    fill_n(cardValuesP1, 15, 0);
    fill_n(cardValuesP2, 15, 0);

    fill_n(isOccupiedP1, 15, 0);
    fill_n(isOccupiedP2, 15, 0);

    chosenCard = 0;

    shuffleBoolCards();
    shuffleCards(48);
    takeCards(5, playerOneCards, 48);
    takeCards(5, playerTwoCards, 48);

    gotoXY(30, 3); cout << YELLOW << "Player 1's side" << RESET;
    gotoXY(139, 3); cout << YELLOW << "Player 2's side" << RESET;

    while (true)
    {
        executeTurn(playerOneCards, boolCardValuesP1, 1, isOccupiedP1, cardValuesP1);
        executeTurn(playerTwoCards, boolCardValuesP2, 2, isOccupiedP2, cardValuesP2);

        if (isOccupiedP1[14] == 1 || isOccupiedP2[14] == 1)
        {
            system("cls");
            break;
        }
    }
    if (isOccupiedP1[14] == 1 && isOccupiedP2[14] == 1)
    {
        system("cls");
        gotoXY(90, 20); cout << "    ___  __    _  __    __ " << endl;
        gotoXY(90, 21); cout << "   /   \\/__\\  /_\\/ / /\\ \\ \\" << endl;
        gotoXY(90, 22); cout << "  / /\\ / \\// //_\\\\ \\/  \\/ /" << endl;
        gotoXY(90, 23); cout << " / /_// _  \\/  _  \\  /\\  / " << endl;
        gotoXY(90, 24); cout << "/___,'\\/ \\_/\\_/ \\_/\\/  \\/" << endl;
        Sleep(3000);
        startProgram();
    }
    else if (isOccupiedP1[14] == 1)
    {
        system("cls");
        gotoXY(73, 20); cout << "   ___  __    _         __  __    _    __    __ _____    __  __" << endl;
        gotoXY(73, 21); cout << "  / _ \\/ /   /_\\ /\\_/\\ /__\\/__\\  / |  / / /\\ \\ \\\\_   \\/\\ \\ \\/ _\\" << endl;
        gotoXY(73, 22); cout << " / /_)/ /   //_\\\\\\_ _//_\\ / \\//  | |  \\ \\/  \\/ / / /\\/  \\/ /\\ \\" << endl;
        gotoXY(73, 23); cout << "/ ___/ /___/  _  \\/ \\//__/ _  \\  | |   \\  /\\  /\\/ /_/ /\\  / _\\ \\" << endl;
        gotoXY(73, 24); cout << "\\/   \\____/\\_/ \\_/\\_/\\__/\\/ \\_/  |_|    \\/  \\/\\____/\\_\\ \\/  \\__/" << endl;
        Sleep(3000);
        startProgram();
    }
    else if (isOccupiedP2[14] == 1)
    {
        system("cls");
        gotoXY(70, 20); cout << "   ___  __    _         __  __    ____     __    __ _____    __  __ " << endl;
        gotoXY(70, 21); cout << "  / _ \\/ /   /_\\ /\\_/\\ /__\\/__\\  |___ \\   / / /\\ \\ \\\\_   \\/\\ \\ \\/ _\\" << endl;
        gotoXY(70, 22); cout << " / /_)/ /   //_\\\\\\_ _//_\\ / \\//    __) |  \\ \\/  \\/ / / /\\/  \\/ /\\ \\" << endl;
        gotoXY(70, 23); cout << "/ ___/ /___/  _  \\/ \\//__/ _  \\   / __/    \\  /\\  /\\/ /_/ /\\  / _\\ \\" << endl;
        gotoXY(70, 24); cout << "\\/   \\____/\\_/ \\_/\\_/\\__/\\/ \\_/  |_____|    \\/  \\/\\____/\\_\\ \\/  \\__/" << endl;
        Sleep(3000);
        startProgram();
    }
}