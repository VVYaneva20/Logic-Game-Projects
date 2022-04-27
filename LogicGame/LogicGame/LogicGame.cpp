#include <iostream>
#include "MultyPlayer.h"
#include "MultyPlayerWithNoCard.h"
#include "WithComputer.h"
#include "WithComputerWithNoCard.h"

using namespace std;

void cardOrZero()
{
    cout << " ___________________" << endl;
    cout << "|   |            |  |" << endl;
    cout << "|   |     " << RED << "OR   " << RESET << "  |  |" << endl;
    cout << "|                   |" << endl;
    cout << "|        " << RED << "___" << RESET << "        |" << endl;
    cout << "|       " << RED << "/ _ \\ " << RESET << "      |" << endl;
    cout << "|      " << RED << "| | | | " << RESET << "     |" << endl;
    cout << "|      " << RED << "| | | |  " << RESET << "    |" << endl;
    cout << "|      " << RED << "| |_| |   " << RESET << "   |" << endl;
    cout << "|       " << RED << "\\___/  " << RESET << "     |" << endl;
    cout << "|                   |" << endl;
    cout << "|                   |" << endl;
    cout << "|         |         |" << endl;
    cout << "|_________|_________|" << endl;
}

void cardAndZero()
{
    cout << " ___________________" << endl;
    cout << "|   |            |  |" << endl;
    cout << "|   |     " << RED << "AND  " << RESET << "  |  |" << endl;
    cout << "|                   |" << endl;
    cout << "|        " << RED << "___" << RESET << "        |" << endl;
    cout << "|       " << RED << "/ _ \\ " << RESET << "      |" << endl;
    cout << "|      " << RED << "| | | | " << RESET << "     |" << endl;
    cout << "|      " << RED << "| | | |  " << RESET << "    |" << endl;
    cout << "|      " << RED << "| |_| |   " << RESET << "   |" << endl;
    cout << "|       " << RED << "\\___/  " << RESET << "     |" << endl;
    cout << "|                   |" << endl;
    cout << "|                   |" << endl;
    cout << "|         |         |" << endl;
    cout << "|_________|_________|" << endl;
}

void cardXorZero()
{
    cout << " ___________________" << endl;
    cout << "|   |            |  |" << endl;
    cout << "|   |     " << RED << "XOR   " << RESET << " |  |" << endl;
    cout << "|                   |" << endl;
    cout << "|        " << RED << "___" << RESET << "        |" << endl;
    cout << "|       " << RED << "/ _ \\ " << RESET << "      |" << endl;
    cout << "|      " << RED << "| | | | " << RESET << "     |" << endl;
    cout << "|      " << RED << "| | | |  " << RESET << "    |" << endl;
    cout << "|      " << RED << "| |_| |   " << RESET << "   |" << endl;
    cout << "|       " << RED << "\\___/  " << RESET << "     |" << endl;
    cout << "|                   |" << endl;
    cout << "|                   |" << endl;
    cout << "|         |         |" << endl;
    cout << "|_________|_________|" << endl;
}

void cardAndOne()
{
    cout << " ___________________" << endl;
    cout << "|   |            |  |" << endl;
    cout << "|   |    " << RED << "AND    " << RESET << " |  |" << endl;
    cout << "|                   |" << endl;
    cout << "|                   |" << endl;
    cout << "|        " << RED << "__" << RESET << "         |" << endl;
    cout << "|       " << RED << "/_ | " << RESET << "       |" << endl;
    cout << "|      " << RED << "  | |  " << RESET << "      |" << endl;
    cout << "|      " << RED << "  | |   " << RESET << "     |" << endl;
    cout << "|      " << RED << "  | |    " << RESET << "    |" << endl;
    cout << "|       " << RED << " |_|  " << RESET << "      |" << endl;
    cout << "|                   |" << endl;
    cout << "|                   |" << endl;
    cout << "|         |         |" << endl;
    cout << "|_________|_________|" << endl;
}

void cardOrOne()
{
    cout << " ___________________" << endl;
    cout << "|   |            |  |" << endl;
    cout << "|   |    " << RED << " OR    " << RESET << " |  |" << endl;
    cout << "|                   |" << endl;
    cout << "|                   |" << endl;
    cout << "|        " << RED << "__" << RESET << "         |" << endl;
    cout << "|       " << RED << "/_ | " << RESET << "       |" << endl;
    cout << "|      " << RED << "  | |  " << RESET << "      |" << endl;
    cout << "|      " << RED << "  | |   " << RESET << "     |" << endl;
    cout << "|      " << RED << "  | |    " << RESET << "    |" << endl;
    cout << "|       " << RED << " |_|  " << RESET << "      |" << endl;
    cout << "|                   |" << endl;
    cout << "|                   |" << endl;
    cout << "|         |         |" << endl;
    cout << "|_________|_________|" << endl;
}

void cardXorOne()
{
    cout << " ___________________" << endl;
    cout << "|   |            |  |" << endl;
    cout << "|   |    " << RED << "XOR    " << RESET << " |  |" << endl;
    cout << "|                   |" << endl;
    cout << "|                   |" << endl;
    cout << "|        " << RED << "__" << RESET << "         |" << endl;
    cout << "|       " << RED << "/_ | " << RESET << "       |" << endl;
    cout << "|      " << RED << "  | |  " << RESET << "      |" << endl;
    cout << "|      " << RED << "  | |   " << RESET << "     |" << endl;
    cout << "|      " << RED << "  | |    " << RESET << "    |" << endl;
    cout << "|       " << RED << " |_|  " << RESET << "      |" << endl;
    cout << "|                   |" << endl;
    cout << "|                   |" << endl;
    cout << "|         |         |" << endl;
    cout << "|_________|_________|" << endl;
}

int main()
{

}