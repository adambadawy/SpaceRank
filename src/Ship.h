#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Entity.h"


class Ship : public Entity
{
public:
    Ship
        ( sf::Vector2f pos
        , int thrust
        , int handling
        , int attackPower
        , int attackFrequency
        , int shieldIntegrity
        , int hullIntegrity );

    virtual void update(sf::Time dt);
    virtual void render(Renderer &renderer) const;

private:
    float getRawMoveSpeed();
    float getRawRotateSpeed();
    sf::Time getAttackCooldownTime();
    
    constexpr static float Pi = std::acos(-1);

    // Ship stats (all of these are a value 1 through 10, totaling 15.)
    int thrust;
    int handling;
    int attackPower;
    int attackFrequency;
    int shieldIntegrity;
    int hullIntegrity;

    /** The text displayed over the ship. */
    std::string text;

    /** The rotation of the ship. */
    float rot;

    /** The time left until the ship can fire again. */
    sf::Time attackCooldown;

    mutable sf::ConvexShape sprite;
};
