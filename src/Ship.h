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


class Ship final : public Entity
{
public:
    Ship
        ( b2World &world
        , Vec2 initPosition
        , ShipStat &&stat );

    Vec2 getPosition() const final override;

    void update(sf::Time dt) final override;
    void render(Renderer &renderer) const final override;

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
    mutable sf::RectangleShape hitboxSprite;
};
