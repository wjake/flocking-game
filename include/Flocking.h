#ifndef FLOCKING_H_
#define FLOCKING_H_

#include <memory>
#include "Entity.h"

class Flocking
{
public:
    float m_neighbour_radius = 100.0f;
    float m_cohesion_weight = 0.5f;
    float m_alignment_weight = 1.0f;
    float m_separation_weight = 1.5f;
    float m_attraction_weight = 1.0f;
    float m_random_weight = 0.5f;

    /**
     * @brief Calculate the cohesion vector for the entity
     * @param _flock The flock of entities
     * @param _entity The entity to calculate the cohesion vector for
     * @return The cohesion vector
     */
    Vec2<float> cohesion(const std::vector<std::unique_ptr<Entity>>& _flock, const Entity& _entity) const;

    /**
     * @brief Calculate the alignment vector for the entity
     * @param _flock The flock of entities
     * @param _entity The entity to calculate the alignment vector for
     * @return The alignment vector
     */
    Vec2<float> alignment(const std::vector<std::unique_ptr<Entity>>& _flock, const Entity& _entity) const;

    /**
     * @brief Calculate the separation vector for the entity
     * @param _flock The flock of entities
     * @param _entity The entity to calculate the separation vector for
     * @return The separation vector
     */
    Vec2<float> separation(const std::vector<std::unique_ptr<Entity>>& _flock, const Entity& _entity) const;

    /**
     * @brief Calculate the attraction vector for the entity
     * @param _entity The entity to calculate the attraction vector for
     * @param _position The position to attract to
     * @return The attraction vector
     */
    Vec2<float> attraction(const Entity& _entity, const Vec2<float> _position) const;

    Flocking() = default;

    /**
     * @brief Construct a new Flocking object
     * @param _cohesion_weight The weight of the cohesion vector
     * @param _alignment_weight The weight of the alignment vector
     * @param _separation_weight The weight of the separation vector
     * @param _attraction_weight The weight of the attraction vector
     * @return A new Flocking object
     */
    Flocking(const float _cohesion_weight, const float _alignment_weight, const float _separation_weight, const float _attraction_weight) :
        m_cohesion_weight(_cohesion_weight), m_alignment_weight(_alignment_weight),
        m_separation_weight(_separation_weight), m_attraction_weight(_attraction_weight) {};

    /**
     * @brief Update the flock entity positons based on the flocking rules
     * @param _flock The flock of entities
     * @param _entity The entity to update
     * @param _elapsed_time The time since the last update
     */
    void update(std::vector<std::unique_ptr<Entity>>& _flock, const Entity& _entity, const float _elapsed_time);
};

#endif