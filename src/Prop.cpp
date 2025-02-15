#include "Prop.h"
#include "Game.h"

bool Prop::collision(const Prop& _prop) const
{
    // Take half heights (via bit shift) and compare with absolute difference of positions
    long half_w = (static_cast<long>(m_size.m_x * Game::drawable_scaler) >> 1);
    long half_h = (static_cast<long>(m_size.m_y * Game::drawable_scaler) >> 1);
    long p_half_w = (static_cast<long>(_prop.m_size.m_x * Game::drawable_scaler) >> 1);
    long p_half_h = (static_cast<long>(_prop.m_size.m_y * Game::drawable_scaler) >> 1);

    return (abs(m_position.m_x - _prop.m_position.m_x) < (half_w + p_half_w)) &&
           (abs(m_position.m_y - _prop.m_position.m_y) < (half_h + p_half_h));
}

// bool Prop::collision(const Prop& _prop, const Vec2<float> _extend) const
// {
//     Vec2<float> extended_size = m_size + _extend;
//     long half_width1 = (long) (extended_size.m_x * Game::drawable_scaler) >> 1;
//     long half_height1 = (long) (extended_size.m_y * Game::drawable_scaler) >> 1;
//     long half_width2 = (long) (_entity.m_size.m_x * Game::drawable_scaler) >> 1;
//     long half_height2 = (long) (_entity.m_size.m_y * Game::drawable_scaler) >> 1;

//     float abs_x = std::abs(m_position.m_x - _entity.m_position.m_x);
//     float abs_y = std::abs(m_position.m_y - _entity.m_position.m_y);

//     return (abs_x < half_width1 + half_width2) && (abs_y < half_height1 + half_height2);
// }