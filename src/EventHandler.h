#pragma once

#include <memory>

#include <SFML/Window.hpp>

using std::weak_ptr;


/** A base class for classes which listen for input events. */
class EventHandler
{
public:
    /**
     * The handler function for input events.
     *
     * Returning true will cause the the traversal of the handler tree to end.
     * Because of that, this function is not guaranteed to be called for every
     * event, and won't be called if another EventHandler "consumes" an event
     * this EventHandler is reached.
     *
     * @return true if the event was handled, false otherwise.
     */
    virtual bool handleEvent(const sf::Event &event) = 0;
};
