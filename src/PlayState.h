#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <Box2D/Box2D.h>

#include "State.h"

using std::shared_ptr;

class Entity;
class Game;


class PlayState final : public State
{
public:
    static const sf::Time PhysicsUpdateDelta;

    PlayState(Game &game, MsgMgr *msgMgr);

    bool handleEvent(const sf::Event &event) final override;
    void update(sf::Time dt) final override;
    void render(Renderer &renderer) const final override;

private:
    sf::Time physicsUpdateTimer;

    b2World world;
    std::vector<shared_ptr<Entity>> entities;
};
