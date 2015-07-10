#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "State.h"

using std::shared_ptr;

class Entity;
class Game;


class PlayState : public State
{
public:
    PlayState(Game &game, MsgMgr *msgMgr);

    virtual bool handleEvent(const sf::Event &event);
    virtual void update(sf::Time dt);
    virtual void render(Renderer &renderer) const;


private:
    std::vector<shared_ptr<Entity>> entities;
};
