#include "Util.h"


float toDegrees(float radians) { return (radians * 180) / Pi; }

float toRadians(float degrees) { return (degrees * Pi) / 180; }


sf::Vector2f toSfVector(b2Vec2 v) { return sf::Vector2f(v.x, v.y); }

b2Vec2 toB2Vector(sf::Vector2f v) { return b2Vec2(v.x, v.y); }


b2Vec2 b2VectorFromMagnitude(float magnitude, float direction)
{
    return b2Vec2(magnitude * cos(direction), magnitude * sin(direction));
}
