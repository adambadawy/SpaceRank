#include "Entity.h"

#include "ResMgr.h"


Entity::Entity(sf::Vector2f pos) : pos(pos) {}


bool Entity::handleEvent(const sf::Event &event) { return false; }
