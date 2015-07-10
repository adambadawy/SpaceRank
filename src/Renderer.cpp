#include "Renderer.h"

#include <iostream>


Renderer::Renderer(sf::RenderWindow &window, float scale)
    : window(window)
{
    surfaceBuffer.setScale(sf::Vector2f(scale, scale));
    refreshSurface();

    if (!font.loadFromFile("res/pixeljosh6.ttf"))
        std::cerr << "Fatal: failed to load font." << std::endl;

    textBuffer.setFont(font);
    textBuffer.setColor(sf::Color::White);
}


sf::Vector2u Renderer::getSurfaceSize() const { return surface.getSize(); }


void Renderer::refreshSurface()
{
    auto windowSize = window.getSize();
    float scale = surfaceBuffer.getScale().x;
    surface.create
        ( (unsigned int)(windowSize.x / scale)
        , (unsigned int)(windowSize.y / scale) );
    surface.clear();
}


void Renderer::flip()
{
    surface.display();
    surfaceBuffer.setTexture(surface.getTexture());

    window.clear();
    window.draw(surfaceBuffer);
    window.display();

    surface.clear();
}


void Renderer::draw(sf::Sprite &sprite, sf::Vector2f pos)
{
    sprite.setPosition(pos);
    surface.draw(sprite);
}


void Renderer::draw(sf::Shape &shape, sf::Vector2f pos)
{
    shape.setPosition(pos);
    surface.draw(shape);
}


void Renderer::draw
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
    surface.draw(textBuffer);
}
