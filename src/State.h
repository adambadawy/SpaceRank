#pragma once

#include <SFML/Graphics.hpp>

#include "EventHandler.h"
#include "Renderable.h"
#include "Subscriber.h"
#include "Updatable.h"

class Game;
class MsgMgr;


class State
    : public Subscriber
    , public EventHandler
    , public Updatable
    , public Renderable
{
public:
    enum ID { Menu, Play };

    State(Game &game, MsgMgr *msgMgr);

    virtual bool handleEvent(const sf::Event &event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void render(Renderer &renderer) const = 0;


protected:
    Game &game;
};
