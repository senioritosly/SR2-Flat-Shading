#pragma once
#include "color.h"
#include <glm/glm.hpp>
#include <vector>
#include <SDL.h>
#include <glm/glm.hpp>
#include "fragment.h"

class Framebuffer
{
private:
    float width;
    float height;
    std::vector<FragColor> framebuffer;
    Color clearColor;
    Color mainColor;
    glm::vec3 light;
    FragColor blank;

public:
    Framebuffer(float width, float height);
    Framebuffer(float width, float height, Color clearColor);
    Framebuffer(float width, float height, Color clearColor, glm::vec3 light);
    void clear();
    void point(const Fragment &);
    void renderBuffer(SDL_Renderer *);

    void setMainColor(Color color);
    void setClearColor(Color color);
    void setSize(float width, float height);
    void setLight(glm::vec3 lignt);

    glm::vec3 getLight();
    float getWidth();
    float getHeight();
    Color getMainColor();
    Color getClearColor();
};
