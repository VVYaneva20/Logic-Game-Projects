#pragma once
#define COMPUTERMODE_H_INCLUDED

using namespace std;

void chooseCardComputer(int* player);
void printPositionsComputerMode();
void placeCardPlayer(int* playerscardsComputerMode, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues);
void placeCardComputer(int* playerscardsComputerMode, bool* boolCardValues, int player, bool* occupiedPositions, bool* cardValues);
void player();
void computer();
void startTheGameWithComputer();