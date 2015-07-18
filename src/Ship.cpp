#include "Ship.h"

#include <cmath>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "PlayState.h"
#include "Renderer.h"
#include "Util.h"


Ship::Ship
    ( b2World &world
    , sf::Vector2f initPosition
    , ShipStat &&stat )

    : body(nullptr)
    , stat(stat)
    , text("debug text")
    , attackCooldown(sf::Time::Zero)
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

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1, 1);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    sprite.setPointCount(3);

    float shipLength = 26;
    float shipWidth = 20;

    sprite.setPoint(0, sf::Vector2f(0, 0));
    sprite.setPoint(1, sf::Vector2f(0, shipWidth));
    sprite.setPoint(2, sf::Vector2f(shipLength, shipWidth / 2));
    sprite.setFillColor(sf::Color::White);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}


sf::Vector2f Ship::getPosition() const
{
    return toSfVector(body->GetPosition());
}


float Ship::getRotation() const { return toDegrees(body->GetAngle()); }


void Ship::update(sf::Time dt)
{
    float damperCoeff =
        sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) ? 0.5 : 1;

    int thrustInput = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        thrustInput += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        thrustInput -= 1;
    updateThrust(thrustInput, damperCoeff);

    int rotateInput = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        rotateInput += 1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rotateInput -= 1;
    body->SetAngularVelocity(rotateInput * stat.getHandling() * damperCoeff);

    if (attackCooldown != sf::Time::Zero)
    {
        attackCooldown -= dt;
        if (attackCooldown < sf::Time::Zero)
            attackCooldown = sf::Time::Zero;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (text == "bang")
            text = "boom";
        else
            text = "bang";
        attackCooldown += getAttackCooldownTime();
    }

    updateSprite();
}


void Ship::updateThrust(int thrustInput, float damperCoeff)
{
    float thrustMagnitude = stat.getThrust() * ThrustCoeff * damperCoeff;
    if (thrustInput == 1)
    {
        b2Vec2 thrustForce =
            b2VectorFromMagnitude(thrustMagnitude, body->GetAngle());
        body->ApplyForceToCenter( thrustForce, true );
    }
    else if (thrustInput == -1)
    {
        b2Vec2 brakeVel = body->GetLinearVelocity();
        float magnitude = brakeVel.Normalize();
        if (abs(magnitude) <
                (ThrustCoeff * PlayState::PhysicsUpdateDelta.asSeconds()) / 2)
        {
            body->SetLinearVelocity( b2Vec2(0, 0) );
        }
        else
        {
            brakeVel *= (thrustMagnitude * -1 * stat.getHandling()) / 10;
            body->ApplyForceToCenter( brakeVel, true );
        }
    }
}


void Ship::updateSprite()
{
    sprite.setPosition( this->getPosition() * 10.0f );
    sprite.setRotation( this->getRotation() );
}


void Ship::render(Renderer &renderer) const
{
    renderer.draw(sprite);
    // text = "%f", body->GetAngularVelocity();
    std::stringstream ss;
    ss << (int)(abs(body->GetLinearVelocity().x));
    text = ss.str();
    renderer.drawText
        ( text
        , sf::Vector2i(sprite.getPosition()) - sf::Vector2i(0, 55)
        , Renderer::Align::Center );
}


sf::Time Ship::getAttackCooldownTime()
{
    return sf::milliseconds(3060 - 300 * stat.getAttackFreq());
}
