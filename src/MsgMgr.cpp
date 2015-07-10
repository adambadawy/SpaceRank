#include "MsgMgr.h"

#include <utility>

#include "Subscriber.h"


MsgMgr::MsgMgr() : receivingQueue(queueA), processingQueue(queueB) {}


void MsgMgr::addSubscriber(AbstractSubscriber *sub, MsgType type)
{
    subscriberMap[type].push_back(sub);
}


void MsgMgr::addMsg(Msg msg) { receivingQueue.push_back(msg); }


void MsgMgr::broadcast()
{
    std::swap(processingQueue, receivingQueue);
    for (const Msg &msg : processingQueue)
    {
        for (auto sub : subscriberMap[msg.type])
            sub->handleMsg(msg);
    }
    processingQueue.clear();
}
