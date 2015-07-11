#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Entity.h"


class Ship : public Entity
{
public:
    Ship( sf::Vector2f pos
        , int moveSpeed
        , int rotateSpeed
        , int attackCooldownSpeed );

    virtual void update(sf::Time dt);
    virtual void render(Renderer &renderer) const;

private:
    float getMoveSpeed();
    float getRotateSpeed();
    sf::Time getAttackCooldownTime();
    
    constexpr static float Pi = std::acos(-1);

    // Ship stats
    int moveSpeed;
    int rotateSpeed;
    int attackCooldownSpeed;

    /** The rotation of the ship. */
    float rot;

    /** The time left until the ship can fire again. */
    sf::Time attackCooldown;

    mutable sf::ConvexShape sprite;
};
