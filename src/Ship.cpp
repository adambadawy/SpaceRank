#include "Ship.h"

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Renderer.h"


Ship::Ship
    ( sf::Vector2f pos
    , int moveSpeed
    , int rotateSpeed
    , int attackCooldownSpeed )

    : Entity(pos)
    , moveSpeed(moveSpeed)
    , rotateSpeed(rotateSpeed)
    , attackCooldownSpeed(attackCooldownSpeed)
    , rot(0)
    , attackCooldown(sf::Time::Zero)
{
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
    sf::Vector2i moveAxis(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        moveAxis.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        moveAxis.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        moveAxis.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        moveAxis.y += 1;

    pos += sf::Vector2f
        ( moveAxis.y * getMoveSpeed() * dt.asSeconds() * std::cos(rot)
        , moveAxis.y * getMoveSpeed() * dt.asSeconds() * std::sin(rot) );
    
    rot = (rot + moveAxis.x * getRotateSpeed() * dt.asSeconds());
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
            // FIRE!
            attackCooldown += getAttackCooldownTime();
        }
    }
}


void Ship::render(Renderer &renderer) const
{
    renderer.draw(sprite, pos);
    renderer.drawText
        ( "debug text"
        , sf::Vector2i(pos.x, pos.y - 55)
        , Renderer::Align::Center );
}


float Ship::getMoveSpeed() { return 80 + 10 * moveSpeed; }

float Ship::getRotateSpeed() { return (100 + 20 * rotateSpeed) * Pi / 180; }

sf::Time Ship::getAttackCooldownTime()
{
    return sf::milliseconds(1200 - 100 * attackCooldownSpeed);
}
