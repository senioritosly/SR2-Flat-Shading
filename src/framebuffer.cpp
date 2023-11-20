#include "framebuffer.h"
#include <glm/glm.hpp>
#include <SDL.h>
#include <array>
#include "color.h"
#include <vector>
#include "fragment.h"

Framebuffer::Framebuffer(float width, float height) : width(width), height(height)
{
    framebuffer.resize(width * height);
    setClearColor(Color{0, 0, 0});
    setMainColor(Color{255, 255, 255});
    setLight(glm::vec3(0.0f, 0.0f, 1.0f));
    blank = {
        clearColor,
        std::numeric_limits<double>::max()};
    clear();
}

Framebuffer::Framebuffer(float width, float height, Color clearColor) : width(width), height(height), clearColor(clearColor)
{
    framebuffer.resize(width * height);
    setMainColor(Color{255, 255, 255});
    setLight(glm::vec3(0.0f, 0.0f, 1.0f));
    blank = {
        clearColor,
        std::numeric_limits<double>::max()};
    clear();
}

Framebuffer::Framebuffer(float width, float height, Color clearColor, glm::vec3 light) : width(width), height(height), clearColor(clearColor), light(light)
{
    framebuffer.resize(width * height);
    setMainColor(Color{255, 255, 255});
    blank = {
        clearColor,
        std::numeric_limits<double>::max()};
    clear();
}

void Framebuffer::clear()
{
    fill(framebuffer.begin(), framebuffer.end(), blank);
}

void Framebuffer::point(const Fragment &f)
{
    if (f.z < framebuffer[f.position.y * width + f.position.x].z)
    {
        framebuffer[f.position.y * width + f.position.x] = FragColor{f.color, f.z};
    }
}

void Framebuffer::renderBuffer(SDL_Renderer *renderer)
{
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    void *texturePixels;
    int pitch;
    SDL_LockTexture(texture, NULL, &texturePixels, &pitch);

    Uint32 format = SDL_PIXELFORMAT_ARGB8888;
    SDL_PixelFormat *mappingFormat = SDL_AllocFormat(format);

    Uint32 *texturePixels32 = static_cast<Uint32 *>(texturePixels);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int framebufferY = height - y - 1;
            int index = y * (pitch / sizeof(Uint32)) + x;
            Color &color = framebuffer[framebufferY * width + x].color;
            texturePixels32[index] = SDL_MapRGBA(mappingFormat, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
        }
    }

    SDL_UnlockTexture(texture);
    SDL_Rect textureRect = {0, 0, static_cast<int>(width), static_cast<int>(height)};
    SDL_RenderCopy(renderer, texture, NULL, &textureRect);
    SDL_DestroyTexture(texture);
}

void Framebuffer::setMainColor(Color color)
{
    mainColor = color;
}

void Framebuffer::setClearColor(Color color)
{
    clearColor = color;
    blank = {clearColor, std::numeric_limits<double>::max()};
}

void Framebuffer::setSize(float w, float h)
{
    framebuffer.resize(w * h);
    clear();
}

void Framebuffer::setLight(glm::vec3 l)
{
    light = l;
}

glm::vec3 Framebuffer::getLight()
{
    return light;
}

float Framebuffer::getWidth()
{
    return width;
}

float Framebuffer::getHeight()
{
    return height;
}

Color Framebuffer::getMainColor()
{
    return mainColor;
}

Color Framebuffer::getClearColor()
{
    return clearColor;
}
