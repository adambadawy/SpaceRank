#include "MenuState.h"

#include <iostream>

#include "Game.h"
#include "PlayState.h"
#include "ResMgr.h"


MenuState::MenuState(Game &game, MsgMgr *msgMgr, ResMgr &resMgr)
    : State(game, msgMgr)
    , selection(0)
{
    choices.push_back("New Game");
    choices.push_back("Load Game");
    choices.push_back("Options");
    choices.push_back("Quit");

    Msg msg(MsgType::PlayMusic);
    msg.playMusic.loop = false;
    msg.playMusic.path = "res/theme.ogg";
    broadcast(msg);
}


bool MenuState::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Return:
            if (choices[selection] == "New Game")
            {
                Msg msg(MsgType::RequestState);
                msg.requestState.stateID = State::Play;
                broadcast(msg);
                return true;
            }
            else if (choices[selection] == "Quit")
            {
                Msg msg(MsgType::RequestExit);
                msg.requestExit.exitCode = 0;
                broadcast(msg);
                return true;
            }
            else
            {
                std::cout
                    << "\""
                    << choices[selection]
                    << "\" not yet implemented."
                    << std::endl;
                return true;
            }

        case sf::Keyboard::Escape:
        { // braces are needed here so `msg` is scoped to this case.
            Msg msg(MsgType::RequestExit);
            msg.requestExit.exitCode = 0;
            broadcast(msg);
            return true;
        }

        case sf::Keyboard::Up:
            selection -= 1;
            if (selection < 0)
                selection += choices.size();
            return true;

        case sf::Keyboard::Down:
            selection = (selection + 1) % choices.size();
            return true;

        default:
            return false;
        }
    }
    return false;
}


void MenuState::update(sf::Time dt) {}


void MenuState::render(Renderer &renderer) const
{
    auto size = renderer.getSurfaceSize();
    renderer.drawText
        ( "SPACERANK"
        , sf::Vector2i(size.x / 2, (size.y * 3) / 16)
        , Renderer::Align::Center
        , sf::Color::White
        , 8 );

    auto selectedColor = sf::Color(0, 150, 255);
    for (unsigned int i = 0; i < choices.size(); ++i)
    {
        renderer.drawText
            ( choices[i]
            , sf::Vector2i(size.x / 2, (size.y * (9 + i)) / 16)
            , Renderer::Align::Center
            , (int)i == selection ? selectedColor : sf::Color::White
            , 3 );
    }
}
