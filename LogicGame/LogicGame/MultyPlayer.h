#pragma once
#define MULTYPLAYER_H_INCLUDED

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"

void gotoXY(int x, int y);
void cardOrZero(int x, int y); 
void cardAndZero(int x, int y);
void cardXorZero(int x, int y);
void cardAndOne(int x, int y);
void cardOrOne(int x, int y);
void cardXorOne(int x, int y);
void shuffleCards();
void beginingOfTheGameWithTwoPLayers();