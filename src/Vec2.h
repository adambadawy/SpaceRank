#pragma once

#include <SFML/System.hpp>

#include <Box2D/Box2D.h>


class Vec2
{
    friend Vec2 worldVec(b2Vec2 v);
    friend Vec2 worldVec(float x, float y);

public:
    /// View this vector in render coordinates
    sf::Vector2f asRenderVec() const;

    /// View this vector in world (Box2D) coordinates
    b2Vec2 asWorldVec() const;

private:
    /// x and y should be world (Box2D) coordinates
    Vec2(float x, float y);

    float x;
    float y;
};


/// Create a Vec2 from world (Box2D) coordinates
Vec2 worldVec(b2Vec2 v);

/// Create a Vec2 from world (Box2D) coordinates
Vec2 worldVec(float x, float y);
