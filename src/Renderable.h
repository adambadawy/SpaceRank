#pragma once

class Renderer;


class Renderable
{
    virtual void render(Renderer &renderer) const = 0;
};
