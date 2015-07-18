#pragma once

#include <SFML/System.hpp>

#include <Box2D/Box2D.h>


constexpr float Pi = std::acos(-1);

float toDegrees(float theta);
float toRadians(float theta);


sf::Vector2f toSfVector(b2Vec2 v);
b2Vec2 toB2Vector(sf::Vector2f v);


b2Vec2 b2VectorFromMagnitude(float magnitude, float direction);
