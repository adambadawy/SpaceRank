#include "PlayState.h"

#include <iostream>
#include <memory>

#include "Entity.h"
#include "Game.h"
#include "Ship.h"

using std::shared_ptr;


const sf::Time PlayState::PhysicsUpdateDelta = sf::seconds(1.0 / 60.0);


PlayState::PlayState(Game &game, MsgMgr *msgMgr)
    : State(game, msgMgr)
    , physicsUpdateTimer(PhysicsUpdateDelta)
    , world( b2Vec2(0, 0) ) // no gravity
{
    shared_ptr<Ship> ship(
        new Ship(world, sf::Vector2f(50, 108 / 2), 10, 10, 10, 10, 10, 10) );
    entities.push_back(ship);
}


bool PlayState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            Msg msg(MsgType::RequestState);
            msg.requestState.stateID = State::Menu;
            broadcast(msg);
            return true;
        }
    }
    return false;
}


void PlayState::update(sf::Time dt)
{
    physicsUpdateTimer -= dt;
    if (physicsUpdateTimer <= sf::Time::Zero)
    {
        physicsUpdateTimer += PhysicsUpdateDelta;
        world.Step(PhysicsUpdateDelta.asSeconds(), 8, 3);
    }
    for (auto ent : entities)
        ent->update(dt);
}


void PlayState::render(Renderer &renderer) const
{
    for (auto ent : entities)
        ent->render(renderer);
}
