#include "AudioMgr.h"

#include <iostream>

#include <SFML/Audio.hpp>

#include "Msg.h"


AudioMgr::AudioMgr(MsgMgr *msgMgr) : Subscriber(msgMgr)
{
    subscribe(MsgType::PlaySound);
    subscribe(MsgType::PlayMusic);
    subscribe(MsgType::RequestState);
}


void AudioMgr::handleMsg(const Msg &msg)
{
    switch (msg.type) {
    case MsgType::PlayMusic:
        music.stop();
        if (music.openFromFile(msg.playMusic.path))
        {
            music.setLoop(msg.playMusic.loop);
            music.play();
        }
        else
            std::cerr
                << "Error: Failed to load resource \""
                << msg.playMusic.path
                << "\"."
                << std::endl;
        break;

    case MsgType::RequestState:
        music.stop();
        break;

    default:
        std::cerr << "Warning: Unhandled msg type." << std::endl;
        break;
    }
}
