#pragma once

#include <SFML/Graphics.hpp>


class Renderer
{
public:
    enum class Align { Left, Center, Right };

    Renderer(sf::RenderWindow &window, float scale=1);

    sf::Vector2u getSurfaceSize() const;
    
    void flip();

    void draw(sf::Sprite &sprite);
    void draw(sf::Shape &shape);
    void drawText
        ( const std::string &s
        , sf::Vector2i pos
        , Align align=Align::Left
        , sf::Color color=sf::Color::White
        , unsigned int fontSize=2 );


private:
    sf::RenderWindow &window;
    sf::Font font;
    sf::Text textBuffer;
};
