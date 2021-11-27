#include <iostream>
#include "game.hpp"

using namespace std;

int main()
{
    // different results everytime
    srand(time(0));

    // create a game
    Game game = Game("input1.txt");

    // start game
    game.start();
}