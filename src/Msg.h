#pragma once

#include <string>

#include "State.h"


/** The type or "topic" of a message. */
enum class MsgType
{
    /** A request to quit the game. */
    RequestExit,

    /** A request to change the state of the game. */
    RequestState,

    /** A request to play a sound. */
    PlaySound,

    /** A request to play some music. */
    PlayMusic
};


/** The ideal structure for one-way communication between objects. */
class Msg
{
public:
    Msg(MsgType type);

private:
    struct RequestExitData { int exitCode; };
    struct RequestStateData { State::ID stateID; };
    struct PlaySoundData { const char *path; };
    struct PlayMusicData
    {
        const char *path;
        bool loop;
    };

public:
    MsgType type;
    union
    {
        RequestExitData requestExit;
        RequestStateData requestState;
        PlaySoundData playSound;
        PlayMusicData playMusic;
    };
};
