#pragma once

class Msg;
enum class MsgType;


/**
 * A pure interface for subscribers.
 *
 * @see Subscriber
 */
class AbstractSubscriber
{
public:
    /** This function does handling for Msg objects. */
    virtual void handleMsg(const Msg &msg) = 0;

    /** Subscribes to certain MsgTypes. */
    virtual void subscribe(MsgType type) = 0;

    /**
     * Broadcasts a Msg.
     *
     * All subscribers will have handleMsg called with an equivalent Msg
     * object as an argument.
     */
    virtual void broadcast(const Msg &msg) = 0;
};
