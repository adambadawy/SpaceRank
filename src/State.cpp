#include "State.h"


State::State(Game &game, MsgMgr *msgMgr) : Subscriber(msgMgr), game(game) {}