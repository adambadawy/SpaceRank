#pragma once

#include "AbstractSubscriber.h"

class MsgMgr;


/// A default implementation of AbstractSubscriber. Subclasses should override
/// handleMsg.
class Subscriber : AbstractSubscriber
{
public:
    Subscriber(MsgMgr *msgMgr);

    virtual void subscribe(MsgType type);
    virtual void broadcast(const Msg &msg);
    virtual void handleMsg(const Msg &msg);


private:
    MsgMgr *msgMgr;
};
