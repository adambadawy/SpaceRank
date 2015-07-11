#include "PlayState.h"

#include <iostream>
#include <memory>

#include "Entity.h"
#include "Game.h"
#include "Ship.h"

using std::shared_ptr;


PlayState::PlayState(Game &game, MsgMgr *msgMgr) : State(game, msgMgr)
{
    shared_ptr<Ship> ship(new Ship(sf::Vector2f(100,100), 1, 1, 1));
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
    for (auto ent : entities)
        ent->update(dt);
}


void PlayState::render(Renderer &renderer) const
{
    for (auto ent : entities)
        ent->render(renderer);
}
