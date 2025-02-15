#include "Flocking.h"
#include <iostream>
#include "Game.h"

Vec2<float> Flocking::cohesion(const std::vector<std::unique_ptr<Entity>>& _flock, const Entity& _entity) const
{
    Vec2<float> center_mass(0, 0);
    int count = 0;
    for (auto& entity_ptr : _flock)
    {
        Entity& entity = *entity_ptr;
        if (&entity != &_entity)
        {
            float distance = (_entity.m_position - entity.m_position).magnitude();
            if (distance < m_neighbour_radius)
            {
                center_mass += entity.m_position;
                count++;
            }
        }
    }
    if (count > 0)
    {
        center_mass /= count;
        return (center_mass - _entity.m_position).normalise();
    }
    return Vec2<float>(0, 0);
}

Vec2<float> Flocking::alignment(const std::vector<std::unique_ptr<Entity>>& _flock, const Entity& _entity) const
{
    Vec2<float> avg_velocity(0, 0);
    int count = 0;
    for (auto& entity_ptr : _flock)
    {
        Entity& entity = *entity_ptr;
        if (&entity != &_entity)
        {
            float distance = (_entity.m_position - entity.m_position).magnitude();
            if (distance < m_neighbour_radius)
            {
                avg_velocity += entity.m_velocity;
                count++;
            }
        }
    }
    if (count > 0)
    {
        avg_velocity /= count;
        return avg_velocity.normalise();
    }
    return Vec2<float>(0, 0);
}

Vec2<float> Flocking::separation(const std::vector<std::unique_ptr<Entity>>& _flock, const Entity& _entity) const
{
    Vec2<float> avoid_vec(0, 0);
    int count = 0;
    for (auto& entity_ptr : _flock)
    {
        Entity& entity = *entity_ptr;
        if (&entity != &_entity)
        {
            const long distance = (_entity.m_position - entity.m_position).magnitude();
            if (distance < m_neighbour_radius)
            {
                avoid_vec += (_entity.m_position - entity.m_position) / (distance << 1);
                count++;
            }
        }
    }
    if (count > 0)
    {
        avoid_vec /= count;
        return avoid_vec.normalise();
    }
    return Vec2<float>(0, 0);
}

Vec2<float> Flocking::attraction(const Entity& _entity, const Vec2<float> _position) const
{
    float distance = (_position - _entity.m_position).magnitude();
    if (distance < 1000.0f)
        return (_position - _entity.m_position).normalise();
    return Vec2<float>(0, 0);
    // return (_position - _entity.m_position).normalise();
}

void Flocking::update(std::vector<std::unique_ptr<Entity>>& _flock, const Entity& _entity, const float _elapsed_time)
{
    #pragma omp parallel for
    for (auto& entity_ptr : _flock)
    {
        Entity& entity = *entity_ptr;
        Vec2<float> cohesion_vec = cohesion(_flock, entity) * m_cohesion_weight;
        Vec2<float> alignment_vec = alignment(_flock, entity) * m_alignment_weight;
        Vec2<float> separation_vec = separation(_flock, entity) * m_separation_weight;
        Vec2<float> attraction_vec = attraction(entity, _entity.m_position) * m_attraction_weight;
        Vec2<float> flock_force = cohesion_vec + alignment_vec + separation_vec + attraction_vec;

        if (flock_force.magnitude() == 0)
        {
            // entity has no neigbours whtin radius
            // TODO: add idle random movement?
            // entity sleep for ease?
            entity.m_velocity = Vec2<float>(0, 0);
            continue;
        }

        entity.m_velocity = (entity.m_velocity + flock_force * _elapsed_time).normalise();
        entity.m_position += entity.m_velocity * entity.m_speed * _elapsed_time * Game::drawable_scaler;

        // when entity is on edge of window, move to other side
        // if (entity.m_position.m_x < -entity.m_size.m_x)
        //     entity.m_position.m_x = Game::drawable_width + entity.m_size.m_x;
        // else if (entity.m_position.m_x > Game::drawable_width + entity.m_size.m_x)
        //     entity.m_position.m_x = -entity.m_size.m_x;
        // if (entity.m_position.m_y < -entity.m_size.m_y)
        //     entity.m_position.m_y = Game::drawable_height + entity.m_size.m_y;
        // else if (entity.m_position.m_y > Game::drawable_height + entity.m_size.m_y)
        //     entity.m_position.m_y = -entity.m_size.m_y;
    }
}