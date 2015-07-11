#include <iostream>

#include "Config.h"
#include "Game.h"


int main()
{
    std::cout
        << "SFML version:      "
        << SFML_VERSION_MAJOR
        << '.'
        << SFML_VERSION_MINOR
        << std::endl;
    std::cout
        << "SpaceRank version: "
        << SpaceRank_VERSION_MAJOR
        << '.'
        << SpaceRank_VERSION_MINOR
        << std::endl;
    Game game;
    return game.run();
}
