#pragma once

#include <SFML/Audio.hpp>

#include "Subscriber.h"

class MsgMgr;


/// Manages the audio for the game. No other class streams music or buffers
/// sound effects.
///
/// This class subscribes to PlayMusic and PlaySound messages. Objects can
/// broadcast messages of these types and the AudioMgr will cause the playback.
class AudioMgr : Subscriber
{
public:
    AudioMgr(MsgMgr *msgMgr);

    /// @see AbstractSubscriber
    void handleMsg(const Msg &msg) final override;


private:
    sf::Music music;
};
