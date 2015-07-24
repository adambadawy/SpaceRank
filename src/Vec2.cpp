#include "Vec2.h"


Vec2::Vec2(float x, float y) : x(x), y(y) {}


sf::Vector2f Vec2::asRenderVec() const { return sf::Vector2f(x * 10, y * 10); }


b2Vec2 Vec2::asWorldVec() const { return b2Vec2(x, y); }


Vec2 worldVec(b2Vec2 v) { return Vec2(v.x, v.y); }


Vec2 worldVec(float x, float y) { return Vec2(x, y); }
