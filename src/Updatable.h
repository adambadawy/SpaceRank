#pragma once

#include <SFML/System.hpp>


class Updatable
{
    virtual void update(sf::Time dt) = 0;
};
