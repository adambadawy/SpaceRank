#include "Ship.h"

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Renderer.h"


Ship::Ship
    ( b2World &world
    , sf::Vector2f pos
    , int thrust
    , int handling
    , int attackPower
    , int attackFrequency
    , int shieldIntegrity
    , int hullIntegrity )

    : Entity(pos)
    , body(nullptr)
    , thrust(thrust)
    , handling(handling)
    , attackPower(attackPower)
    , attackFrequency(attackFrequency)
    , text("Marek Jaroki")
    , rot(0)
    , attackCooldown(sf::Time::Zero)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);
    body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
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


void Ship::update(sf::Time dt)
{
    float dtSeconds = dt.asSeconds();

    int thrustInput = 0;
    int rotateInput = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rotateInput -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        rotateInput += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        thrustInput -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        thrustInput += 1;

    float moveSpeed = getRawMoveSpeed();
    float rotateSpeed = getRawRotateSpeed();
    bool damperOn =
        sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
    if (damperOn)
    {
        moveSpeed /= 2;
        rotateSpeed /= 2;
    }

    pos += sf::Vector2f
        ( thrustInput * moveSpeed * dtSeconds * std::cos(rot)
        , thrustInput * moveSpeed * dtSeconds * std::sin(rot) );

    rot = (rot + rotateInput * rotateSpeed * dtSeconds);
    if (rot < -Pi)
        rot += 2 * Pi;
    else if (rot >= Pi)
        rot -= 2 * Pi;
    sprite.setRotation(rot * 180 / Pi);

    attackCooldown -= dt;
    if (attackCooldown < sf::Time::Zero)
        attackCooldown = sf::Time::Zero;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (attackCooldown == sf::Time::Zero)
        {
            if (text == "bang")
                text = "boom";
            else
                text = "bang";
            attackCooldown += getAttackCooldownTime();
        }
    }
}


void Ship::render(Renderer &renderer) const
{
    b2Vec2 bodyPos = body->GetPosition();
    renderer.draw(sprite, sf::Vector2f(bodyPos.x * 10, 1080 - (bodyPos.y * 10)));
    renderer.drawText
        ( text
        , sf::Vector2i(pos.x, pos.y - 55)
        , Renderer::Align::Center );
}


float Ship::getRawMoveSpeed() { return 10 + 40 * thrust; }

float Ship::getRawRotateSpeed() { return (10 + 20 * handling) * Pi / 180; }

sf::Time Ship::getAttackCooldownTime()
{
    return sf::milliseconds(3060 - 300 * attackFrequency);
}
