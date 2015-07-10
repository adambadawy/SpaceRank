#pragma once

#include <map>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Game;


class ResMgr
{
public:
    ResMgr(Game &game);

    sf::Texture & getTexture(const std::string &path);
    sf::SoundBuffer & getSoundBuffer(const std::string &path);


private:
    template <typename T>
    T & cachedLoad(const std::string &path, std::map<std::string, T> &cache);

    sf::Texture errorTexture;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::SoundBuffer> soundBuffers;
};
