#include "Entity.h"
#include "Game.h"

void Entity::damage(const short _damage)
{
    m_cur_health -= _damage;
    if (m_cur_health <= 0) m_cur_health = 0;
}

void Entity::heal(const short _heal)
{
    m_cur_health += _heal;
    if (m_cur_health > m_max_health) m_cur_health = m_max_health;
}

bool Entity::alive() const
{
    return m_cur_health > 0;
}