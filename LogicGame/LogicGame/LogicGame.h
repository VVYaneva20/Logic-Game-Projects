#pragma once
#define LOGICGAME_H_INCLUDED

#define RESET   "\033[0m"
#define RED     "\033[31m"

void startProgram();
void cardOrZero(int x, int y);
void cardAndZero(int x, int y);
void cardXorZero(int x, int y);
void cardAndOne(int x, int y);
void cardOrOne(int x, int y);
void cardXorOne(int x, int y);
void cardOne(int x, int y);
void cardZero(int x, int y);