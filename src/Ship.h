#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Entity.h"


class Ship : public Entity
{
public:
    Ship(sf::Vector2f pos);

    virtual void update(sf::Time dt);
    virtual void render(Renderer &renderer) const;

private:
    constexpr static float Pi = std::acos(-1);

    constexpr static float RotateSpeed = 4.0f * Pi / 180.0f;
    constexpr static float MoveSpeed = 2.0f;

    float rot;

    mutable sf::ConvexShape sprite;
};
