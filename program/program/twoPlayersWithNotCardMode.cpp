#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "program.h"
#include "twoPlayersWithNotCardMode.h"
#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m" 
using namespace std;
HANDLE consoleNotCard = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPositionNotCard; // used for goto
int cardsNotCard[56];
int playerOnecardsNotCard[5], playerTwocardsNotCard[5];
int chosencard;
int counterNotCard;
bool initialCardValuesP1[6], initialcardValuesP2[6];
bool valuesP1[15], valuesP2[15];
bool occupiedP1[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool occupiedP2[15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int cardsP1[15];
int cardsP2[15];
int posCoordinatesNotCard[15][3] = { {60, 107, 4}, {60, 107, 13}, {60, 107, 22}, {60, 107, 31}, {60, 107, 40},
                          {47, 122, 8}, {47, 122, 18}, {47, 122, 28}, {47, 122, 38},
                          {32, 137, 12}, {32, 137, 23}, {32, 137, 34},
                          {17, 152, 17}, {17, 152, 29},
                          {2, 167, 23}
};

bool isNotCard = true;
bool scipTurnP1 = 0, scipTurnP2 = 0;
//takes coordinates
void gotoXYNotCard(int x, int y)
{
    CursorPositionNotCard.X = x;
    CursorPositionNotCard.Y = y;
    SetConsoleCursorPosition(consoleNotCard, CursorPositionNotCard);
}
void shuffleBoolcardsNotCard()
{
    bool cardsNotCard[6];
    int pixelsX = 77;
    int pixelsY = 2;
    srand(time(NULL));
    for (int i = 0; i < 6; i++)
    {
        cardsNotCard[i] = rand() % 2;
    }
    for (int i = 0; i < 6; i++)
    {
        if (cardsNotCard[i] == 0)
        {
            cardZero(pixelsX, pixelsY);
            cardOne(pixelsX + 15, pixelsY);
            initialCardValuesP1[i] = 0;
            initialcardValuesP2[i] = 1;
        }
        else
        {
            cardOne(pixelsX, pixelsY);
            cardZero(pixelsX + 15, pixelsY);
            initialCardValuesP1[i] = 1;
            initialcardValuesP2[i] = 0;
        }
        pixelsY += 8;
    }
}
void shufflecardsNotCard()
{
    for (int i = 0; i < 56; i++)
    {
        cardsNotCard[i] = i + 1;
    }
    int temp;
    srand(time(NULL));
    for (int i = 55; i > 0; --i)
    {
        int j = rand() % i;
        temp = cardsNotCard[i];
        cardsNotCard[i] = cardsNotCard[j];
        cardsNotCard[j] = temp;
    }
}
void notCard(int x, int y)
{
    gotoXYNotCard(x, y++); cout << RESET << " _______________" << endl;
    gotoXYNotCard(x, y++); cout << "|               |" << endl;
    gotoXYNotCard(x, y++); cout << "|               |" << endl;
    gotoXYNotCard(x, y++); cout << "|      " << RED << "NOT" << RESET << "      |" << endl;
    gotoXYNotCard(x, y++); cout << "|     " << RED << "CARD" << RESET << "      |" << endl;
    gotoXYNotCard(x, y++); cout << "|               |" << endl;
    gotoXYNotCard(x, y++); cout << "|               |" << endl;
    gotoXYNotCard(x, y++); cout << "|               |" << endl;
    gotoXYNotCard(x, y++); cout << "|_______________|" << endl;
}
//display the empty positions
void printPositionsNotCard(int player, bool* isOccupied, int* values)
{
    int xFirstFive, y, x, xP2;
    if (player == 1)
        xFirstFive = 60;
    else
        xFirstFive = 107;
    for (int i = 0; i < 5; i++)
    {
        y = posCoordinatesNotCard[i][2];
        if (!isOccupied[i] && isNotCard)
        {
            gotoXYNotCard(xFirstFive, y++); cout << " _______________" << endl;
            gotoXYNotCard(xFirstFive, y++); cout << "|    POSITION   |" << endl;
            gotoXYNotCard(xFirstFive, y++); cout << "|               |" << endl;
            gotoXYNotCard(xFirstFive, y++); cout << "|               |" << endl;
            gotoXYNotCard(xFirstFive, y++); cout << "|       " << i + 1 << "       |" << endl;
            gotoXYNotCard(xFirstFive, y++); cout << "|               |" << endl;
            gotoXYNotCard(xFirstFive, y++); cout << "|               |" << endl;
            gotoXYNotCard(xFirstFive, y++); cout << "|               |" << endl;
            gotoXYNotCard(xFirstFive, y++); cout << "|_______________|" << endl;
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
                notCard(xFirstFive, y);
            }
            else if (values[i] % 7 == 0)
            {
                cardAndOne(xFirstFive, y);
            }
        }
    }
    int inColumn = 4;
    int position = 6;
    for (int i = 5; i < 15; i++)
    {
        x = posCoordinatesNotCard[i][player - 1];
        y = posCoordinatesNotCard[i][2];
        if (i == 9)
        {
            position = 1;
        }
        if ((isOccupied[i - inColumn] and isOccupied[i - inColumn - 1] and (!isOccupied[i])))
        {
            gotoXYNotCard(x, y++); cout << " _______________" << endl;
            gotoXYNotCard(x, y++); cout << "|    POSITION   |" << endl;
            gotoXYNotCard(x, y++); cout << "|               |" << endl;
            gotoXYNotCard(x, y++); cout << "|               |" << endl;
            gotoXYNotCard(x, y++); cout << "|       " << position << "       |" << endl;
            gotoXYNotCard(x, y++); cout << "|               |" << endl;
            gotoXYNotCard(x, y++); cout << "|               |" << endl;
            gotoXYNotCard(x, y++); cout << "|               |" << endl;
            gotoXYNotCard(x, y++); cout << "|_______________|" << endl;
        }
        else if (isOccupied[i] && isNotCard)
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
            else if (values[i] % 7 == 6)
            {
                notCard(x, y);
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
void notCardCheck(int* values, bool* isOccupied, bool* initialCardValues, int playerNum)
{
    int pixelsX;
    int pixelsY;

    //notCardCheck(cardsP1, occupiedP1, initialCardValuesP1, 1);
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
            printPositionsNotCard(playerNum, isOccupied, values);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        pixelsX = posCoordinatesNotCard[i + 5][playerNum - 1];
        pixelsY = posCoordinatesNotCard[i + 5][2];

        if (isOccupied[i] == 0 || isOccupied[i + 1] == 0)
        {
            isOccupied[i + 5] = 0;

            for (int i = 0; i < 9; i++)
            {
                gotoXYNotCard(pixelsX, pixelsY++); cout << "                 ";
            }
        }
    }

    for (int i = 5; i < 8; i++)
    {
        pixelsX = posCoordinatesNotCard[i + 4][playerNum - 1];
        pixelsY = posCoordinatesNotCard[i + 4][2];

        if (isOccupied[i] == 0 || isOccupied[i + 1] == 0)
        {
            isOccupied[i + 4] = 0;

            for (int i = 0; i < 9; i++)
            {
                gotoXYNotCard(pixelsX, pixelsY++); cout << "                 ";
            }
        }
    }

    for (int i = 9; i < 11; i++)
    {
        pixelsX = posCoordinatesNotCard[i + 3][playerNum - 1];
        pixelsY = posCoordinatesNotCard[i + 3][2];

        if (isOccupied[i] == 0 || isOccupied[i + 1] == 0)
        {
            isOccupied[i + 3] = 0;

            for (int i = 0; i < 9; i++)
            {
                gotoXYNotCard(pixelsX, pixelsY++); cout << "                 ";
            }
        }
    }

    for (int i = 12; i < 13; i++)
    {
        pixelsX = posCoordinatesNotCard[i + 2][playerNum - 1];
        pixelsY = posCoordinatesNotCard[i + 2][2];

        if (isOccupied[i] == 0 || isOccupied[i + 1] == 0)
        {
            isOccupied[i + 2] = 0;

            for (int i = 0; i < 9; i++)
            {
                gotoXYNotCard(pixelsX, pixelsY++); cout << "                 ";
            }
        }
    }

    printPositionsNotCard(1, occupiedP1, cardsP1);
    printPositionsNotCard(2, occupiedP2, cardsP2);
}
//discard a card
void removeCardNotCard(int card, int* player)
{
    for (int i = card - 1; i < 5; ++i)
    {
        player[i] = player[i + 1];
    }
}

//the player gets cardsNotCard
void takecardsNotCard(int cardsNotCardNeeded, int* player)
{
    if (cardsNotCardNeeded != 1)
    {
        for (int i = 0; i < cardsNotCardNeeded; i++)
        {
            player[i] = cardsNotCard[i];
        }
    }
    else
    {
        player[4] = cardsNotCard[0];
    }
    for (int i = 0; i < cardsNotCardNeeded; i++)
    {
        int temp = cardsNotCard[0];
        for (int j = 0; j < 55; j++)
        {
            cardsNotCard[j] = cardsNotCard[j + 1];
        }
        cardsNotCard[55] = temp;
    }
}

//the player selects a card
void chooseCardNotCard(int* player, bool returned)
{
    int Set[] = { 12, 7, 7, 7, 7 };
    counterNotCard = 1;
    char key;
    while (true)
    {
        gotoXYNotCard(189, 6);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[0]);
        cout << ">";
        gotoXYNotCard(189, 15);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[1]);
        cout << ">";
        gotoXYNotCard(189, 24);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[2]);
        cout << ">";
        gotoXYNotCard(189, 33);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[3]);
        cout << ">";
        gotoXYNotCard(189, 44);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Set[4]);
        cout << ">";
        key = _getch();
        if (key == 72) // up arrow key
        {
            if (counterNotCard == 1)
            {
                counterNotCard = 5;
            }
            else
            {
                counterNotCard--;
            }
        }
        if (key == 80) // down arrow key
        {
            if (counterNotCard == 5)
            {
                counterNotCard = 1;
            }
            else
            {
                counterNotCard++;
            }
        }
        if (key == 's')// select card
        {
            //player[counterNotCard - 1] = chosencard;
            if (counterNotCard == 1)
            {
                chosencard = player[0];
                break;
            }
            if (counterNotCard == 2)
            {
                chosencard = player[1];
                break;
            }
            if (counterNotCard == 3)
            {
                chosencard = player[2];
                break;
            }
            if (counterNotCard == 4)
            {
                chosencard = player[3];
                break;
            }
            if (counterNotCard == 5)
            {
                chosencard = player[4];
                break;
            }
        }
        if (key == 27)// enter
        {
            startProgram();
            break;
        }
        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;
        if (counterNotCard == 1)
        {
            Set[0] = 12;
        }
        if (counterNotCard == 2)
        {
            Set[1] = 12;
        }
        if (counterNotCard == 3)
        {
            Set[2] = 12;
        }
        if (counterNotCard == 4)
        {
            Set[3] = 12;
        }
        if (counterNotCard == 5)
        {
            Set[4] = 12;
        }
    }
    Sleep(150);
}

//display cardsNotCard 
void printcardsNotCard(int cardsNotCardNeeded, int* player)
{
    int counter = 0;
    int pixelsX = 191;
    int pixelsY = 2;
    gotoXYNotCard(30, 3); cout << YELLOW << "Player 1's side" << RESET;
    gotoXYNotCard(139, 3); cout << YELLOW << "Player 2's side" << RESET;
    for (int i = 0; i < 52; i++)
    {
        gotoXYNotCard(187, i); cout << "|";
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
            notCard(pixelsX, pixelsY);
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

void printInitialPositions()
{
    int pixelsX = 77;
    int pixelsY = 2;
    int position = 1;
    for (int i = 0; i < 6; i++)
    {
        gotoXYNotCard(pixelsX, pixelsY++); cout << RESET << " _____________";
        gotoXYNotCard(pixelsX, pixelsY++); cout << "|             |";
        gotoXYNotCard(pixelsX, pixelsY++); cout << "|             |";
        gotoXYNotCard(pixelsX, pixelsY++); cout << "|             |";
        gotoXYNotCard(pixelsX, pixelsY++); cout << "|      " << position << "      |";
        gotoXYNotCard(pixelsX, pixelsY++); cout << "|             |";
        gotoXYNotCard(pixelsX, pixelsY++); cout << "|             |";
        gotoXYNotCard(pixelsX, pixelsY++); cout << "|_____________|";
        pixelsY -= 8;
        gotoXYNotCard(pixelsX + 15, pixelsY++); cout << RESET << " _____________";
        gotoXYNotCard(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXYNotCard(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXYNotCard(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXYNotCard(pixelsX + 15, pixelsY++); cout << "|      " << position << "      |";
        gotoXYNotCard(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXYNotCard(pixelsX + 15, pixelsY++); cout << "|             |";
        gotoXYNotCard(pixelsX + 15, pixelsY++); cout << "|_____________|";
        position++;
    }
}

void printInitialCards(int position, bool reverse, int player)
{
    int pixelsX = 77;
    int pixelsY = 2;

    if (reverse)
    {
        bool flag = 0;
        int temp;
        if (player == 1)
        {
            for (int i = 0; i < 5; i++)
            {
                if (playerTwocardsNotCard[i] % 7 == 6)
                {
                    temp = i;
                    flag = 1;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < 5; i++)
            {
                if (playerOnecardsNotCard[i] % 7 == 6)
                {
                    temp = i;
                    flag = 1;
                    break;
                }
            }
        }

        if (flag)
        {
            if (player == 2)
            {
                gotoXYNotCard(18, 7); cout << "Do you want to use your not card?(y/n)";
            }
            else
            {
                gotoXYNotCard(130, 7); cout << "Do you want to use your not card?(y/n)";
            }



            char keyPress;
            keyPress = _getch();
            int asciiValue = keyPress;


            if (asciiValue == 110)
            {
                if (player == 2)
                {
                    gotoXYNotCard(18, 7); cout << "                                      ";
                }
                else
                {
                    gotoXYNotCard(130, 7); cout << "                                      ";
                }
                initialCardValuesP1[position] = !initialCardValuesP1[position];
                initialcardValuesP2[position] = !initialcardValuesP2[position];
            }
            else if (asciiValue == 121)
            {
                if (player == 2)
                {
                    gotoXYNotCard(18, 7); cout << "                                      ";
                }
                else
                {
                    gotoXYNotCard(130, 7); cout << "                                      ";
                }
                if (player == 1)
                {
                    scipTurnP2 = 1;
                    removeCardNotCard(temp + 1, playerTwocardsNotCard);
                }
                else
                {
                    scipTurnP1 = 1;
                    removeCardNotCard(temp + 1, playerOnecardsNotCard);

                }
            }

        }

    }

    for (int i = 0; i < 6; i++)
    {
        if (initialCardValuesP1[i] == 0)
        {
            cardZero(pixelsX, pixelsY);
            cardOne(pixelsX + 15, pixelsY);
            initialCardValuesP1[i] = 0;
            initialcardValuesP2[i] = 1;
        }
        else
        {
            cardOne(pixelsX, pixelsY);
            cardZero(pixelsX + 15, pixelsY);
            initialCardValuesP1[i] = 1;
            initialcardValuesP2[i] = 0;
        }
        pixelsY += 8;
    }
}

void (*pointToCardNotCard[6])(int x, int y) = { cardOrZero, cardXorZero, cardAndZero, cardOrOne, cardXorOne, cardAndOne };

void placeCardNotCard(bool* occupiedPositions, int index, int pointerIndex, int x, int y, bool* cardValues, int* cards, int cardValue, bool value, int* playersCards)
{
    occupiedPositions[index] = 1;
    pointToCardNotCard[pointerIndex](x, y);
    cardValues[index] = value;
    cards[index] = cardValue;
    removeCardNotCard(counterNotCard, playersCards);
}

//put down a card in a chosen position
void checkCardNotCard(int* playerscardsNotCard, bool* initialvalues, int player, bool* occupiedPositions, bool* values, int* cardValues)
{
    int pixelsX;
    int pixelsY;

    while (true)
    {
        if (chosencard % 7 != 6)
        {
            isNotCard = false;
            char keyPress;
            keyPress = _getch();
            int asciiValue = keyPress - 48;
            if (asciiValue == 1) // '1' ASCII code
            {
                if (occupiedPositions[0] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 60;
                    }
                    else
                    {
                        pixelsX = 107;
                    }
                    pixelsY = 4;
                    if (chosencard % 7 == 1 && !(initialvalues[0] || initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 8;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(initialvalues[0] ^ initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 9;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(initialvalues[0] && initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[0] = 0;
                        cardValues[0] = 10;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (initialvalues[0] || initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 11;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (initialvalues[0] ^ initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 12;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (initialvalues[0] && initialvalues[1]))
                    {
                        occupiedPositions[0] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[0] = 1;
                        cardValues[0] = 7;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else if (occupiedPositions[9] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 32;
                    }
                    else
                    {
                        pixelsX = 137;
                    }
                    pixelsY = 12;
                    if (chosencard % 7 == 1 && !(values[5] || values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 8;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(values[5] ^ values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 9;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(values[5] && values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[9] = 0;
                        cardValues[9] = 10;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (values[5] || values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 11;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (values[5] ^ values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 12;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (values[5] && values[6]) && occupiedPositions[5] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[9] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[9] = 1;
                        cardValues[9] = 0;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                }
            }
            if (asciiValue == 2)  // '2' ASCII code
            {
                if (occupiedPositions[1] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 60;
                    }
                    else
                    {
                        pixelsX = 107;
                    }
                    pixelsY = 13;
                    if (chosencard % 7 == 1 && !(initialvalues[1] || initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[1] = 0;
                        cardValues[1] = 8;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(initialvalues[1] ^ initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[1] = 0;
                        cardValues[1] = 9;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(initialvalues[1] && initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardValues[1] = 10;
                        cardAndZero(pixelsX, pixelsY);
                        values[1] = 0;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (initialvalues[1] || initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 11;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (initialvalues[1] ^ initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 12;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (initialvalues[1] && initialvalues[2]))
                    {
                        occupiedPositions[1] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[1] = 1;
                        cardValues[1] = 7;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else if (occupiedPositions[10] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 32;
                    }
                    else
                    {
                        pixelsX = 137;
                    }
                    pixelsY = 23;
                    if (chosencard % 7 == 1 && !(values[6] || values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 8;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(values[6] ^ values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 9;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(values[6] && values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[10] = 0;
                        cardValues[10] = 10;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (values[6] || values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 11;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (values[6] ^ values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 12;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (values[6] && values[7]) && occupiedPositions[7] == 1 && occupiedPositions[6] == 1)
                    {
                        occupiedPositions[10] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[10] = 1;
                        cardValues[10] = 7;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                }
            }
            if (asciiValue == 3) // '3' ASCII code
            {
                if (occupiedPositions[2] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 60;
                    }
                    else
                    {
                        pixelsX = 107;
                    }
                    pixelsY = 22;
                    if (chosencard % 7 == 1 && !(initialvalues[2] || initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 8;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(initialvalues[2] ^ initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 9;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(initialvalues[2] && initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[2] = 0;
                        cardValues[2] = 10;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (initialvalues[2] || initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 11;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (initialvalues[2] ^ initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 12;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (initialvalues[2] && initialvalues[3]))
                    {
                        occupiedPositions[2] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[2] = 1;
                        cardValues[2] = 7;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else if (occupiedPositions[11] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 32;
                    }
                    else
                    {
                        pixelsX = 137;
                    }
                    pixelsY = 34;
                    if (chosencard % 7 == 1 && !(values[7] || values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 8;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(values[7] ^ values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 9;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(values[7] && values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[11] = 0;
                        cardValues[11] = 10;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (values[7] || values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 11;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (values[7] ^ values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 12;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (values[7] && values[8]) && occupiedPositions[7] == 1 && occupiedPositions[8] == 1)
                    {
                        occupiedPositions[11] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[11] = 1;
                        cardValues[11] = 7;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                }
            }
            if (asciiValue == 4) // '4' ASCII code
            {
                if (occupiedPositions[3] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 60;
                    }
                    else
                    {
                        pixelsX = 107;
                    }
                    pixelsY = 31;
                    if (chosencard % 7 == 1 && !(initialvalues[3] || initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 8;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(initialvalues[3] ^ initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 9;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(initialvalues[3] && initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[3] = 0;
                        cardValues[3] = 10;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (initialvalues[3] || initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 11;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (initialvalues[3] ^ initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 12;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (initialvalues[3] && initialvalues[4]))
                    {
                        occupiedPositions[3] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[3] = 1;
                        cardValues[3] = 7;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else if (occupiedPositions[12] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 17;
                    }
                    else
                    {
                        pixelsX = 152;
                    }
                    pixelsY = 17;
                    if (chosencard % 7 == 1 && !(values[9] || values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 8;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(values[9] ^ values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 9;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(values[9] && values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[12] = 0;
                        cardValues[12] = 10;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (values[9] || values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 11;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (values[9] ^ values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 12;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (values[9] && values[10]) && occupiedPositions[9] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[12] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[12] = 1;
                        cardValues[12] = 7;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                }
            }
            if (asciiValue == 5) // '5' ASCII code
            {
                if (occupiedPositions[4] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 60;
                    }
                    else
                    {
                        pixelsX = 107;
                    }
                    pixelsY = 40;
                    if (chosencard % 7 == 1 && !(initialvalues[4] || initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 8;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(initialvalues[4] ^ initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 9;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(initialvalues[4] && initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[4] = 0;
                        cardValues[4] = 10;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (initialvalues[4] || initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 11;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (initialvalues[4] ^ initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 12;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (initialvalues[4] && initialvalues[5]))
                    {
                        occupiedPositions[4] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[4] = 1;
                        cardValues[4] = 7;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else if (occupiedPositions[13] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 17;
                    }
                    else
                    {
                        pixelsX = 152;
                    }
                    pixelsY = 29;
                    if (chosencard % 7 == 1 && !(values[10] || values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 8;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(values[10] ^ values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 9;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(values[10] && values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[13] = 0;
                        cardValues[13] = 10;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (values[10] || values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 11;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (values[10] ^ values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 12;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (values[10] && values[11]) && occupiedPositions[11] == 1 && occupiedPositions[10] == 1)
                    {
                        occupiedPositions[13] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[13] = 1;
                        cardValues[13] = 7;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                }
            }
            if (asciiValue == 6) // '6' ASCII code
            {
                if (occupiedPositions[5] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 47;
                    }
                    else
                    {
                        pixelsX = 122;
                    }
                    pixelsY = 8;
                    if (chosencard % 7 == 1 && !(values[0] || values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 8;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(values[0] ^ values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 9;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(values[0] && values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        values[5] = 0;
                        cardValues[5] = 10;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (values[0] || values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 11;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (values[0] ^ values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 12;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (values[0] && values[1]) && occupiedPositions[0] == 1 && occupiedPositions[1] == 1)
                    {
                        occupiedPositions[5] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        values[5] = 1;
                        cardValues[5] = 0;
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else if (occupiedPositions[14] == 0)
                {
                    if (player == 1)
                    {
                        pixelsX = 2;
                    }
                    else
                    {
                        pixelsX = 167;
                    }
                    pixelsY = 23;
                    if (chosencard % 7 == 1 && !(values[12] || values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 8;
                        occupiedPositions[14] = 1;
                        cardOrZero(pixelsX, pixelsY);
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 2 && !(values[12] ^ values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 9;
                        occupiedPositions[14] = 1;
                        cardXorZero(pixelsX, pixelsY);
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 3 && !(values[12] && values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 10;
                        occupiedPositions[14] = 1;
                        cardAndZero(pixelsX, pixelsY);
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 4 && (values[12] || values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 11;
                        occupiedPositions[14] = 1;
                        cardOrOne(pixelsX, pixelsY);
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 5 && (values[12] ^ values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 12;
                        occupiedPositions[14] = 1;
                        cardXorOne(pixelsX, pixelsY);
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else if (chosencard % 7 == 0 && (values[12] && values[13]) && occupiedPositions[12] == 1 && occupiedPositions[13] == 1)
                    {
                        cardValues[14] = 7;
                        occupiedPositions[14] = 1;
                        cardAndOne(pixelsX, pixelsY);
                        removeCardNotCard(counterNotCard, playerscardsNotCard);
                        break;
                    }
                    else
                    {
                        gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                        continue;
                    }
                }
                else
                {
                    gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                }
            }
            if (asciiValue == 7 && occupiedPositions[6] == 0) // '7' ASCII code
            {
                if (player == 1)
                {
                    pixelsX = 47;
                }
                else
                {
                    pixelsX = 122;
                }
                pixelsY = 18;
                if (chosencard % 7 == 1 && !(values[1] || values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 8;
                    occupiedPositions[6] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 2 && !(values[1] ^ values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 9;
                    occupiedPositions[6] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 3 && !(values[1] && values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 10;
                    occupiedPositions[6] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    values[6] = 0;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 4 && (values[1] || values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 11;
                    occupiedPositions[6] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 5 && (values[1] ^ values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 12;
                    occupiedPositions[6] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 0 && (values[1] && values[2]) && occupiedPositions[2] == 1 && occupiedPositions[1] == 1)
                {
                    cardValues[6] = 7;
                    occupiedPositions[6] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    values[6] = 1;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else
                {
                    gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
            }
            if (asciiValue == 8 && occupiedPositions[7] == 0) // '8' ASCII code
            {
                if (player == 1)
                {
                    pixelsX = 47;
                }
                else
                {
                    pixelsX = 122;
                }
                pixelsY = 28;
                if (chosencard % 7 == 1 && !(values[2] || values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 8;
                    occupiedPositions[7] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 2 && !(values[2] ^ values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 9;
                    occupiedPositions[7] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 3 && !(values[2] && values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 10;
                    occupiedPositions[7] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    values[7] = 0;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 4 && (values[2] || values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 11;
                    occupiedPositions[7] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 5 && (values[2] ^ values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 12;
                    occupiedPositions[7] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 0 && (values[2] && values[3]) && occupiedPositions[2] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[7] = 7;
                    occupiedPositions[7] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    values[7] = 1;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else
                {
                    gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
            }
            if (asciiValue == 9 && occupiedPositions[8] == 0) // '9' ASCII code
            {
                if (player == 1)
                {
                    pixelsX = 47;
                }
                else
                {
                    pixelsX = 122;
                }
                pixelsY = 38;
                if (chosencard % 7 == 1 && !(values[3] || values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 8;
                    occupiedPositions[8] = 1;
                    cardOrZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 2 && !(values[3] ^ values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 9;
                    occupiedPositions[8] = 1;
                    cardXorZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 3 && !(values[3] && values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 10;
                    occupiedPositions[8] = 1;
                    cardAndZero(pixelsX, pixelsY);
                    values[8] = 0;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 4 && (values[3] || values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 11;
                    occupiedPositions[8] = 1;
                    cardOrOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 5 && (values[3] ^ values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 12;
                    occupiedPositions[8] = 1;
                    cardXorOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else if (chosencard % 7 == 0 && (values[3] && values[4]) && occupiedPositions[4] == 1 && occupiedPositions[3] == 1)
                {
                    cardValues[8] = 7;
                    occupiedPositions[8] = 1;
                    cardAndOne(pixelsX, pixelsY);
                    values[8] = 1;
                    removeCardNotCard(counterNotCard, playerscardsNotCard);
                    break;
                }
                else
                {
                    gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
                    continue;
                }
            }
            else
            {
                gotoXYNotCard(195, 50); cout << RED << "Invalid!" << RESET;
            }
            if (asciiValue == 66)// 'r' ASCII value
            {
                gotoXYNotCard(195, 50); cout << "PLAYER " << player << "  ";
                chooseCardNotCard(playerscardsNotCard, 1);
                if (player == 1)
                {
                    checkCardNotCard(playerscardsNotCard, initialvalues, 1, occupiedPositions, values, cardValues);
                }
                else
                {
                    checkCardNotCard(playerscardsNotCard, initialvalues, 2, occupiedPositions, values, cardValues);
                }
                break;
            }
            if (asciiValue == 52)// 'd' ASCII value
            {
                removeCardNotCard(counterNotCard, playerscardsNotCard);
                break;
            }
            if (asciiValue == 27)// escape ASCII value
            {
                startProgram();
                break;
            }
        }
        else
        {
            isNotCard = true;
            printInitialPositions();
            char press;
            press = _getch();
            int ascii = press - 48;
            int cardPosition = 0;
            if (ascii == 52)// 'd' ASCII value
            {
                removeCardNotCard(counterNotCard, playerscardsNotCard);
                printInitialCards(cardPosition, 0, player);
                break;
            }
            if (ascii == 27)// escape ASCII value
            {
                startProgram();
                break;
            }
            switch (ascii)
            {
            case 1:
            {
                cardPosition = 0;
                break;
            }
            case 2:
            {
                cardPosition = 1;
                break;
            }
            case 3:
            {
                cardPosition = 2;
                break;
            }
            case 4:
            {
                cardPosition = 3;
                break;
            }
            case 5:
            {
                cardPosition = 4;
                break;
            }
            case 6:
            {
                cardPosition = 5;
                break;
            }
            }
            removeCardNotCard(counterNotCard, playerscardsNotCard);
            printInitialCards(cardPosition, 1, player);
            notCardCheck(cardsP1, occupiedP1, initialCardValuesP1, 1);
            notCardCheck(cardsP2, occupiedP2, initialcardValuesP2, 2);
            break;
        }
    }
}


//Player one
void playerOne()
{
    printcardsNotCard(5, playerOnecardsNotCard);
    chooseCardNotCard(playerOnecardsNotCard, 0);
    checkCardNotCard(playerOnecardsNotCard, initialCardValuesP1, 1, occupiedP1, valuesP1, cardsP1);
}
//Player two
void playerTwo()
{
    printcardsNotCard(5, playerTwocardsNotCard);
    chooseCardNotCard(playerTwocardsNotCard, 0);
    checkCardNotCard(playerTwocardsNotCard, initialcardValuesP2, 2, occupiedP2, valuesP2, cardsP2);
}
//start the game
void beginningOfTheGameWithTwoPLayersNotCard()
{
    fill_n(cardsNotCard, 48, 0);
    fill_n(playerOnecardsNotCard, 5, 0);
    fill_n(playerTwocardsNotCard, 5, 0);
    fill_n(initialCardValuesP1, 6, 0);
    fill_n(initialcardValuesP2, 6, 0);
    fill_n(valuesP1, 15, 0);
    fill_n(valuesP2, 15, 0);
    fill_n(occupiedP1, 15, 0);
    fill_n(occupiedP2, 15, 0);
    chosencard = 0;
    shuffleBoolcardsNotCard();
    shufflecardsNotCard();
    takecardsNotCard(5, playerOnecardsNotCard);
    takecardsNotCard(5, playerTwocardsNotCard);

    while (true)
    {
        if (scipTurnP1 == 0)
        {
            scipTurnP2 = 0;

            printPositionsNotCard(1, occupiedP1, cardsP1);
            printPositionsNotCard(2, occupiedP2, cardsP2);
            

            gotoXYNotCard(195, 50); cout << "PLAYER 1";
            takecardsNotCard(1, playerOnecardsNotCard);
            playerOne();
        }

        if (scipTurnP2 == 0)
        {
            scipTurnP1 = 0;

            printPositionsNotCard(1, occupiedP1, cardsP1);
            printPositionsNotCard(2, occupiedP2, cardsP2);

            gotoXYNotCard(195, 50); cout << "PLAYER 2";
            takecardsNotCard(1, playerTwocardsNotCard);
            playerTwo();
        }




        if (occupiedP1[14] == 1 || occupiedP2[14] == 1)
        {
            system("cls");
            break;
        }
    }
    if (occupiedP1[14] == 1 && occupiedP2[14] == 1)
    {
        system("cls");
        gotoXYNotCard(90, 20); cout << "    ___  __    _  __    __ " << endl;
        gotoXYNotCard(90, 21); cout << "   /   \\/__\\  /_\\/ / /\\ \\ \\" << endl;
        gotoXYNotCard(90, 22); cout << "  / /\\ / \\// //_\\\\ \\/  \\/ /" << endl;
        gotoXYNotCard(90, 23); cout << " / /_// _  \\/  _  \\  /\\  / " << endl;
        gotoXYNotCard(90, 24); cout << "/___,'\\/ \\_/\\_/ \\_/\\/  \\/" << endl;
        Sleep(3000);
        startProgram();
    }
    else if (occupiedP1[14] == 1)
    {
        system("cls");
        gotoXYNotCard(73, 20); cout << "   ___  __    _         __  __    _    __    __ _____    __  __" << endl;
        gotoXYNotCard(73, 21); cout << "  / _ \\/ /   /_\\ /\\_/\\ /__\\/__\\  / |  / / /\\ \\ \\\\_   \\/\\ \\ \\/ _\\" << endl;
        gotoXYNotCard(73, 22); cout << " / /_)/ /   //_\\\\\\_ _//_\\ / \\//  | |  \\ \\/  \\/ / / /\\/  \\/ /\\ \\" << endl;
        gotoXYNotCard(73, 23); cout << "/ ___/ /___/  _  \\/ \\//__/ _  \\  | |   \\  /\\  /\\/ /_/ /\\  / _\\ \\" << endl;
        gotoXYNotCard(73, 24); cout << "\\/   \\____/\\_/ \\_/\\_/\\__/\\/ \\_/  |_|    \\/  \\/\\____/\\_\\ \\/  \\__/" << endl;
        Sleep(3000);
        startProgram();
    }
    else if (occupiedP2[14] == 1)
    {
        system("cls");
        gotoXYNotCard(70, 20); cout << "   ___  __    _         __  __    ____     __    __ _____    __  __ " << endl;
        gotoXYNotCard(70, 21); cout << "  / _ \\/ /   /_\\ /\\_/\\ /__\\/__\\  |___ \\   / / /\\ \\ \\\\_   \\/\\ \\ \\/ _\\" << endl;
        gotoXYNotCard(70, 22); cout << " / /_)/ /   //_\\\\\\_ _//_\\ / \\//    __) |  \\ \\/  \\/ / / /\\/  \\/ /\\ \\" << endl;
        gotoXYNotCard(70, 23); cout << "/ ___/ /___/  _  \\/ \\//__/ _  \\   / __/    \\  /\\  /\\/ /_/ /\\  / _\\ \\" << endl;
        gotoXYNotCard(70, 24); cout << "\\/   \\____/\\_/ \\_/\\_/\\__/\\/ \\_/  |_____|    \\/  \\/\\____/\\_\\ \\/  \\__/" << endl;
        Sleep(3000);
        startProgram();
    }
}