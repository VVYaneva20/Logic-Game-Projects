#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include "program.h"
#include "twoPlayersMode.h"
#include "twoPlayersWithNotCardMode.h"
#include "computerMode.h"
#include "computerWithNotCardMode.h"

using namespace std;

int main()
{
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    showConsoleCursor(false);
    startProgram();
}