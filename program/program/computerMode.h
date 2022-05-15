#pragma once
#define COMPUTERMODE_H_INCLUDED

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[1m\033[33m" 

void chooseCardComputer(int* player);
void printPositionsComputerMode();
void placeCardComputerMode(int* playerscardsComputerMode, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues);
void placeCardComputer(int* playerscardsComputerMode, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues);
void player();
void computer();
void beginningOfTheGameWithComputer();