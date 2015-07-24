#include "Ball.h"

#include <functional>

#include "Renderer.h"
#include "Util.h"

using std::function;


Ball::Ball(b2World &world, sf::Vector2f initPosition)
    : body(nullptr)
    , bodySprite(10.0f)
    , markSprite(sf::Vector2f(10.0f, 2.0f))
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(initPosition.x, initPosition.y);

    // This lambda captures `world` as a reference (hence [&])
    // equivalent: [&](byBody *b) mutable { world.DestroyBody(b); };
    // It also modifies `world`, so we need `mutable` after the parameters.
    function<void(b2Body*)> deleter =
        [&world](b2Body *b) mutable { world.DestroyBody(b); };

    body = shared_ptr<b2Body>(world.CreateBody(&bodyDef), deleter);

    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 1.0f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    bodySprite.setOrigin
        ( sf::Vector2f(bodySprite.getRadius(), bodySprite.getRadius()) );
    bodySprite.setFillColor(sf::Color::White);

    markSprite.setOrigin(sf::Vector2f(0.0f, 1.0f));
    markSprite.setFillColor(sf::Color::Blue);
}


Vec2 Ball::getPosition() const
{
    return worldVec(body->GetPosition());
}


Angle Ball::getRotation() const { return radians(body->GetAngle()); }


void Ball::update(sf::Time dt) { updateSprite(); }


void Ball::updateSprite()
{
    bodySprite.setPosition( getPosition().asRenderVec() );
    markSprite.setPosition( getPosition().asRenderVec() );
    markSprite.setRotation( getRotation().asDegrees() );
}


void Ball::render(Renderer &renderer) const
{
    renderer.draw(bodySprite);
    renderer.draw(markSprite);
}
