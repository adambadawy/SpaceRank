#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Box2D/Box2D.h>

#include "Angle.h"
#include "Entity.h"
#include "Vec2.h"

using std::shared_ptr;


class Ball : public Entity
{
public:
    Ball(b2World &world, sf::Vector2f initPosition);

    Vec2 getPosition() const final override;

    void update(sf::Time dt) final override;
    void render(Renderer &renderer) const final override;

private:
    Angle getRotation() const;

    /// Reposition and rotate the Ball sprite.
    void updateSprite();

    shared_ptr<b2Body> body;

    mutable sf::CircleShape bodySprite;
    mutable sf::RectangleShape markSprite;
};
