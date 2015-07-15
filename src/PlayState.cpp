#include "PlayState.h"

#include <iostream>
#include <memory>

#include "Entity.h"
#include "Game.h"
#include "Ship.h"

using std::shared_ptr;


PlayState::PlayState(Game &game, MsgMgr *msgMgr)
    : State(game, msgMgr)
    , world( b2Vec2(0.0f, -10.0f) )
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    shared_ptr<Ship> ship(
        new Ship(world, sf::Vector2f(100,100), 10, 10, 10, 10, 10, 10 ) );
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
    world.Step(dt.asSeconds(), 8, 3);
    for (auto ent : entities)
        ent->update(dt);
}


void PlayState::render(Renderer &renderer) const
{
    for (auto ent : entities)
        ent->render(renderer);
}
