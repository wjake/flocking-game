#ifndef ARENA_H_
#define ARENA_H_

#include <vector>
#include <ctime>
#include <algorithm>
#include "Entity.h"
#include "Consumable.h"

class Arena
{
    unsigned char m_level = 1;
    Uint32 m_last_collision = 0;
public:
    Arena();
    ~Arena() = default;

    /**
     * @brief Update the arena
     * @param _elapsed_time The time since the last update
     */
    void update(const float _elapsed_time);

    /**
     * @brief Level up the arena level
     */
    void level_up();

    /**
     * @brief Reset the arena
     */
    void reset();

    /**
     * @brief Spawn an enemy
     */
    void spawn_enemy();

    /**
     * @brief Spawn a consumable
     */
    void spawn_comsumable();

    /**
     * @brief Delete an enemy
     * @param _enemy The enemy to delete
     */
    void delete_enemy(const std::unique_ptr<Entity>& _enemy);
};

#endif