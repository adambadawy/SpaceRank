#pragma once

#include <string>

#include "EventHandler.h"
#include "Renderable.h"
#include "Updatable.h"
#include "Vec2.h"

class ResMgr;


/// This class represents a "game object": something in the game world.
class Entity : public EventHandler, public Updatable, public Renderable
{
public:
    /// @see EventHandler
    virtual bool handleEvent(const sf::Event &event);

    /// @see Updatable
    virtual void update(sf::Time dt) = 0;

    /// @see Renderable
    virtual void render(Renderer &renderer) const = 0;

    /// Return the world coordinates of this Entity
    virtual Vec2 getPosition() const = 0;
};
