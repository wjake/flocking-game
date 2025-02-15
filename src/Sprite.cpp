#include "Sprite.h"
#include "Game.h"

void Sprite::draw(SDL_Renderer* _renderer, SDL_Texture* _texture, const Vec2<float>& _dst) const
{
    SDL_Rect dst = {
        static_cast<int>(_dst.m_x - ((m_src.w * Game::drawable_scaler) >> 1)),
        static_cast<int>(_dst.m_y - ((m_src.h * Game::drawable_scaler) >> 1)),
        static_cast<int>(m_src.w * Game::drawable_scaler),
        static_cast<int>(m_src.h * Game::drawable_scaler)
    };

    SDL_RenderCopy(_renderer, _texture, &m_src, &dst);
}