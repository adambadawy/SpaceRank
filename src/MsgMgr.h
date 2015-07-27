#pragma once

#include <map>
#include <vector>

#include "Msg.h"

class AbstractSubscriber;


class MsgMgr final
{
    friend class Game;

public:
    MsgMgr();

    void addSubscriber(AbstractSubscriber *sub, MsgType type);
    void addMsg(Msg m);


private:
    void broadcast();

    std::vector<Msg> queueA;
    std::vector<Msg> queueB;
    std::vector<Msg> &receivingQueue;
    std::vector<Msg> &processingQueue;
    std::map< MsgType, std::vector<AbstractSubscriber*> > subscriberMap;
};
