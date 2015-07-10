#include "ResMgr.h"

#include <iostream>

#include "Game.h"


ResMgr::ResMgr(Game &game)
{
    if (!errorTexture.loadFromFile("res/error.png"))
    {
        std::cout
            << "Fatal: Failed to load \"missing texture\" texture."
            << std::endl;
        // game.requestExit(1);
    }
}


sf::Texture & ResMgr::getTexture(const std::string &path)
{
    return cachedLoad(path, textures);
}


sf::SoundBuffer & ResMgr::getSoundBuffer(const std::string &path)
{
    return cachedLoad(path, soundBuffers);
}


template <typename T>
T & ResMgr::cachedLoad
    ( const std::string &path
    , std::map<std::string, T> &cache )
{
    auto resIter = cache.find(path);
    if (resIter == cache.end())
    {
        cache[path] = T();
        if (!cache[path].loadFromFile(path))
            std::cout
                << "Error: Failed to load resource \""
                << path
                << "\"."
                << std::endl;
        return cache[path];
    }
    return resIter->second;
}
