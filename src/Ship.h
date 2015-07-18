#pragma once

#include <functional>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Box2D/Box2D.h>

#include "Entity.h"

using std::function;
using std::shared_ptr;


class Ship : public Entity
{
public:
    Ship
        ( b2World &world
        , sf::Vector2f initPosition
        , int thrusters
        , int handling
        , int attackPower
        , int attackFrequency
        , int shieldIntegrity
        , int hullIntegrity );

    virtual sf::Vector2f getPosition() const;

    virtual void update(sf::Time dt);
    virtual void render(Renderer &renderer) const;

private:
    float ThrustCoeff = 10;

    float getRotation() const;

    float getThrust();
    float getRotateSpeed();
    sf::Time getAttackCooldownTime();

    /// Update Ship thrusters given the thrust and damper inputs.
    void updateThrust(int thrustInput, float damperCoeff);
    /// Reposition and rotate the Ship sprite.
    void updateSprite();

    shared_ptr<b2Body> body;

    // Ship stats (all of these are a value 1 through 10, totaling 15.)
    int thrusters;
    int handling;
    int attackPower;
    int attackFrequency;
    int shieldIntegrity;
    int hullIntegrity;

    /// The text displayed over the ship.
    mutable std::string text;

    /// The time left until the ship can fire again.
    sf::Time attackCooldown;

    mutable sf::ConvexShape sprite;
};
