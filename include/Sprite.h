#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL_render.h>
#include "Vec2.h"

class Sprite
{
public:
    SDL_Rect m_src;

    /**
     * @brief Construct a new Sprite object
     * @param _src Source rectangle
     * @param _scaler Scaler for the sprite
     * @return Sprite
     */
    Sprite(SDL_Rect _src) : m_src(_src) {}

    /**
     * @brief Draw the sprite
     * @param _renderer SDL_Renderer to render to
     * @param _texture SDL_Texture to render
     * @param _dst Destination to render to
     */
    void draw(SDL_Renderer* _renderer, SDL_Texture* _texture, const Vec2<float>& _dst) const;
};

#endif