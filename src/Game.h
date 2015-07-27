#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "AudioMgr.h"
#include "EventHandler.h"
#include "MsgMgr.h"
#include "Renderer.h"
#include "ResMgr.h"
#include "Subscriber.h"

using std::shared_ptr;

class State;
class MenuState;


/// This is class represents the control flow and global state of the game.
class Game final : public AbstractSubscriber, public EventHandler
{
public:
    Game();

    /// @see EventHandler
    bool handleEvent(const sf::Event &event) final override;
    
    /// @see AbstractSubscriber
    void handleMsg(const Msg &msg) final override;

    /// @see AbstractSubscriber
    void subscribe(MsgType type) final override;

    /// @see AbstractSubscriber
    void broadcast(const Msg &msg) final override;

    /// The "game loop".
    int run();


private:
    int exitCode;

    MsgMgr msgMgr;
    sf::RenderWindow window;
    ResMgr resMgr;
    AudioMgr audioMgr;
    Renderer renderer;

    shared_ptr<MenuState> menuState;
    shared_ptr<State> state;
};
