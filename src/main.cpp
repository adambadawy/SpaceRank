#include "Game.h"

#include <iostream>


int main()
{
    std::cout
        << "SFML version: "
        << SFML_VERSION_MAJOR
        << '.'
        << SFML_VERSION_MINOR
        << std::endl;
    Game game;
    return game.run();
}
