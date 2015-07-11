#include "Renderer.h"

#include <iostream>


Renderer::Renderer(sf::RenderWindow &window, float scale)
    : window(window)
{
    if (!font.loadFromFile("res/pixeljosh6.ttf"))
        std::cerr << "Fatal: failed to load font." << std::endl;

    textBuffer.setFont(font);
    textBuffer.setColor(sf::Color::White);
}


sf::Vector2u Renderer::getSurfaceSize() const { return window.getSize(); }


void Renderer::flip()
{
    window.display();
    window.clear();
}


void Renderer::draw(sf::Sprite &sprite, sf::Vector2f pos)
{
    sprite.setPosition(pos);
    window.draw(sprite);
}


void Renderer::draw(sf::Shape &shape, sf::Vector2f pos)
{
    shape.setPosition(pos);
    window.draw(shape);
}


void Renderer::drawText
    ( const std::string &s
    , sf::Vector2i pos
    , Align align
    , sf::Color color
    , unsigned int fontSize )
{
    textBuffer.setString(s);
    textBuffer.setCharacterSize(fontSize * 8);
    if (align == Align::Center || align == Align::Right)
    {
        // We truncate to int here intentionally to avoid fuzzy text.
        int w = (int)textBuffer.getLocalBounds().width;
        if (align == Align::Center)
            pos.x -= w / 2;
        else if (align == Align::Right)
            pos.x -= w;
    }
    textBuffer.setPosition(sf::Vector2f(pos));
    textBuffer.setColor(color);
    window.draw(textBuffer);
}
