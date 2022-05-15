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
    //runs the programe in full screen
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

    //makes the cursor invisible
    showConsoleCursor(false);

    startProgram();
}