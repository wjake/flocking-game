#ifndef CONSUMABLE_H_
#define CONSUMABLE_H_

#include "Vec2.h"
#include "Prop.h"

enum ConsumableType { HEALTH, POWER };

class Consumable : public Prop
{
public:
    ConsumableType m_type;
    short m_power;

    /**
     * @brief Construct a new Consumable object
     */
    Consumable() = default;

    /**
     * @brief Construct a new Consumable object
     * @param _position The position of the consumable
     * @param _type The type of the consumable
     * @return A new Consumable object
     */
    Consumable(const ConsumableType _type, Vec2<float> _position) : m_type(_type)
    {
        m_position = _position;
        m_size = Vec2<float>(8, 8);
    };
};

#endif