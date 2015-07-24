#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Box2D/Box2D.h>

#include "Angle.h"
#include "Entity.h"
#include "ShipStat.h"
#include "Vec2.h"

using std::shared_ptr;


class Ship : public Entity
{
public:
    Ship
        ( b2World &world
        , Vec2 initPosition
        , ShipStat &&stat );

    virtual Vec2 getPosition() const;

    virtual void update(sf::Time dt);
    virtual void render(Renderer &renderer) const;

private:
    float ThrustCoeff = 10;

    Angle getRotation() const;

    sf::Time getAttackCooldownTime() const;

    /// Update Ship thrusters given the thrust and damper inputs.
    void updateThrust(int thrustInput, float damperCoeff);
    /// Reposition and rotate the Ship sprite.
    void updateSprite();

    shared_ptr<b2Body> body;

    /// The "stats" of the Ship.
    ShipStat stat;

    /// The text displayed over the ship.
    mutable std::string text;

    /// The time left until the ship can fire again.
    sf::Time attackCooldown;

    mutable sf::ConvexShape sprite;
};
