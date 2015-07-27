#pragma once

#include "AbstractSubscriber.h"

class MsgMgr;


/// A default implementation of AbstractSubscriber. Subclasses should override
/// handleMsg.
class Subscriber : AbstractSubscriber
{
public:
    Subscriber(MsgMgr *msgMgr);

    void subscribe(MsgType type) final override;
    void broadcast(const Msg &msg) final override;
    virtual void handleMsg(const Msg &msg);


private:
    MsgMgr *msgMgr;
};
