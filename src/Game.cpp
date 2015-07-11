#include "Game.h"

#include <iostream>

#include <SFML/Window.hpp>

#include "MenuState.h"
#include "Msg.h"
#include "PlayState.h"


Game::Game()
    : exitCode(0)
    , window
        ( sf::VideoMode::getFullscreenModes()[0]
        , "SpaceRank"
        , sf::Style::Fullscreen )
    , resMgr(*this)
    , audioMgr(&msgMgr)
    , renderer(window)
    , menuState(new MenuState(*this, &msgMgr, resMgr))
    , state(menuState)
{
    window.setMouseCursorVisible(false);

    subscribe(MsgType::RequestExit);
    subscribe(MsgType::RequestState);
}


bool Game::handleEvent(const sf::Event &event)
{
    switch (event.type) {
    case sf::Event::Closed:
        window.close();
        return true;

    case sf::Event::Resized:
        window.setSize(sf::Vector2u(event.size.width, event.size.height));
        renderer.refreshSurface();
        return true;

    case sf::Event::KeyPressed:
        if (event.key.alt && event.key.code == sf::Keyboard::F4)
        {
            window.close();
            return true;
        }

    default:
       return false;
    }
}


void Game::handleMsg(const Msg &msg)
{
    switch (msg.type) {
    case MsgType::RequestExit:
        exitCode = msg.requestExit.exitCode;
        window.close();
        break;

    case MsgType::RequestState:
        switch (msg.requestState.stateID) {
        case State::Menu:
            state = menuState;
            break;

        case State::Play:
            state = shared_ptr<State>(new PlayState(*this, &msgMgr));
            break;
        }
        break;

    default:
        std::cerr << "Warning: Unhandled msg type." << std::endl;
        break;
    }
}


void Game::subscribe(MsgType type) { msgMgr.addSubscriber(this, type); }


void Game::broadcast(const Msg &msg) { msgMgr.addMsg(msg); }


int Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (!state->handleEvent(event))
                handleEvent(event);
        }

        msgMgr.broadcast();

        state->update(dt);

        state->render(renderer);
        renderer.flip();
    }
    return exitCode;
}
