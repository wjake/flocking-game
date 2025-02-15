#ifndef ENTITY_H_
#define ENTITY_H_

#include <cstdint>
#include "Prop.h"
#include "Vec2.h"
#include "Animation.h"

enum class Direction { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3};

class Entity : public Prop
{
public:
    Direction m_direction = Direction::DOWN;

    short m_cur_health;
    short m_max_health;
    short m_power;
    float m_speed;

    // Character states
    bool m_is_attacking = false;

    /**
     * @brief Construct a new Entity object
     */
    Entity() = default;

    /**
     * @brief Construct a new Entity object
     * @param _position The position of the entity
     * @param _velocity The velocity of the entity
     * @param _max_health The maximum health of the entity
     * @param _power The power of the entity
     * @param _speed The speed of the entity
     * @return A new Entity object
     */
    Entity(const Vec2<float> _position, const Vec2<float> _velocity, const Vec2<float>
        _size, const short _max_health = 10, const short _power = 10, const float _speed = 10) :
        m_cur_health(_max_health), m_max_health(_max_health), m_power(_power), m_speed(_speed) {
            m_position = _position;
            m_velocity = _velocity;
            m_size = _size;
        };

    /**
     * @brief Deconstruct the Entity object
     */
    ~Entity() = default;

    /**
     * @brief Damage the entity
     * @param _power The power to damage by
     */
    void damage(const short _power);

    /**
     * @brief Heal the entity
     * @param _heal The amount to heal by
     */
    void heal(const short _heal);

    /**
     * @brief Check if the entity is alive
     * @return True if the entity is alive, false otherwise
     */
    bool alive() const;
};

#endif