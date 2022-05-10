#pragma once
#define PROGRAM_H_INCLUDED

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

//display cards
void cardOrZero(int x, int y);
void cardAndZero(int x, int y);
void cardXorZero(int x, int y);
void cardAndOne(int x, int y);
void cardOrOne(int x, int y);
void cardXorOne(int x, int y);
void cardOne(int x, int y);
void cardZero(int x, int y);
void ShowConsoleCursor(bool showFlag);
void instructions();
void startProgram();