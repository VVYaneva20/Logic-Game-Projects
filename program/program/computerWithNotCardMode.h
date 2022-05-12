#pragma once
#define COMPUTERWITHNOTCARD_H_INCLUDED

#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m" 
#define YELLOW  "\033[1m\033[33m" 

using namespace std;

void gotoXYNotCardWithComputer(int x, int y);
void shuffleBooleanCards();
void shuffleAllCards();
void notCardWithComputer(int x, int y);