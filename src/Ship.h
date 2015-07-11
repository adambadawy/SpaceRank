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

    constexpr static float RotateSpeed = 200.0f * Pi / 180.0f;
    constexpr static float MoveSpeed = 100.0f;
    constexpr static float AttackCooldownSpeed = 5;

    float rot;
    sf::Time attackCooldown;

    mutable sf::ConvexShape sprite;
};
