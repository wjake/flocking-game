#ifndef PROP_H_
#define PROP_H_

#include "Vec2.h"

class Prop 
{
public:
    Vec2<float> m_position;
    Vec2<float> m_velocity;
    Vec2<float> m_size;

    Prop() : m_position(0, 0), m_velocity(0, 0), m_size(0, 0) {}
    Prop(Vec2<float> _position, Vec2<float> _velocity, Vec2<float> _size) :
        m_position(_position), m_velocity(_velocity), m_size(_size) {}

    /**
     * @brief Check for collision with another entity
     * @param _prop The Prop to check collision with
     * @return True if there is a collision, false otherwise
     */
    bool collision(const Prop& _prop) const;

    /**
     * @brief Check for collision with Entity
     * @param _prop The Prop to check collision with
     * @param _extend The extended size of the prop
     * @return True if there is a collision, false otherwise
     */
    // bool collision(const Prop& _prop, const Vec2<float> _extend) const;
};

#endif