#include "Subscriber.h"

#include "MsgMgr.h"

enum class MsgType;


Subscriber::Subscriber(MsgMgr *msgMgr) : msgMgr(msgMgr) {}


void Subscriber::subscribe(MsgType type) { msgMgr->addSubscriber(this, type); }


void Subscriber::broadcast(const Msg &msg) { msgMgr->addMsg(msg); }


void Subscriber::handleMsg(const Msg &msg) {}
