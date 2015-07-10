#pragma once

#include <SFML/Graphics.hpp>


class Renderer
{
public:
    enum class Align { Left, Center, Right };

    Renderer(sf::RenderWindow &window, float scale=4);

    sf::Vector2u getSurfaceSize() const;

    void refreshSurface();
    
    void flip();

    void draw(sf::Sprite &sprite, sf::Vector2f pos);
    void draw(sf::Shape &shape, sf::Vector2f pos);
    void draw
        ( const std::string &s
        , sf::Vector2i pos
        , Align align=Align::Left
        , sf::Color color=sf::Color::White
        , unsigned int fontSize=1 );


private:
    sf::RenderWindow &window;
    sf::RenderTexture surface;
    sf::Sprite surfaceBuffer;
    sf::Font font;
    sf::Text textBuffer;
};
