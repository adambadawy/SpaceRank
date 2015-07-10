#pragma once

#include <string>
#include <vector>

#include "State.h"

class Game;
class MsgMgr;
class ResMgr;


/** The "main menu" state of the game. */
class MenuState : public State
{
public:
    MenuState(Game &game, MsgMgr *msgMgr, ResMgr &resMgr);

    /** @see EventHandler */
    virtual bool handleEvent(const sf::Event &event);

    /** @see Updatable */
    virtual void update(sf::Time dt);

    /** @see Renderable */
    virtual void render(Renderer &renderer) const;


private:
    std::vector<std::string> choices;
    int selection;
};
