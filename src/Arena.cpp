#include <Arena.h>
#include <random>
#include "Game.h"

static std::mt19937 rng(static_cast<unsigned int>(std::time(0)));

Arena::Arena()
{
    Game::player = std::make_unique<Entity>(
            Vec2<float>(Game::drawable_width >> 1, Game::drawable_height >> 1),
            Vec2<float>(0, 0), Vec2<float>(16.0f, 32.0f), 100, 10, 0.1f);

    for (int i = 0; i < 5 * m_level; ++i)
    {
        spawn_enemy();
        spawn_comsumable();
    }
}

void Arena::update(const float _elapsed_time)
{
    if (!Game::player->alive())
    {
        Game::reset();
        return;
    }

    if (Game::enemies.empty())
        level_up();

    for (const auto& enemy : Game::enemies)
        if (enemy != nullptr && !enemy->alive())
            delete_enemy(enemy);

    // Check if player velcoity diagonal and scale velocity appropriately
    if (Game::player->m_velocity == Vec2<>(-1, -1) || Game::player->m_velocity == Vec2<>(1, 1) ||
        Game::player->m_velocity == Vec2<>(-1, 1) || Game::player->m_velocity == Vec2<>(1, -1))
        Game::player->m_position += (Game::player->m_velocity * 0.5f) * Game::player->m_speed * _elapsed_time * Game::drawable_scaler;
    else
        Game::player->m_position += Game::player->m_velocity * Game::player->m_speed * _elapsed_time * Game::drawable_scaler;
    
    // check for player position going out of bounds
    if (Game::player->m_position.m_x < 0.0f)
        Game::player->m_position.m_x = 0.0f;
    if (Game::player->m_position.m_x > Game::drawable_width - 16.0f)
        Game::player->m_position.m_x = Game::drawable_width - 16.0f;
    if (Game::player->m_position.m_y < 0.0f)
        Game::player->m_position.m_y = 0.0f;
    if (Game::player->m_position.m_y > Game::drawable_height - 16.0f)
        Game::player->m_position.m_y = Game::drawable_height - 16.0f;
    
    if (Game::player->m_is_attacking)
    {
        if (Game::player->m_direction == Direction::UP)
            Game::animations.at("player_attack_up")->update(Game::player->m_is_attacking);
        else if (Game::player->m_direction == Direction::DOWN)
            Game::animations.at("player_attack_down")->update(Game::player->m_is_attacking);
        else if (Game::player->m_direction == Direction::LEFT)
            Game::animations.at("player_attack_left")->update(Game::player->m_is_attacking);
        else if (Game::player->m_direction == Direction::RIGHT)
            Game::animations.at("player_attack_right")->update(Game::player->m_is_attacking);
        else
            Game::animations.at("player_attack_down")->update(Game::player->m_is_attacking);
        // check direction of attack and for enemy collisions
    }

    // check last collision between player and enemy
    if (m_last_collision >= 60)
    {
        m_last_collision = 0;
        for (const auto& enemy : Game::enemies)
            if (enemy != nullptr && Game::player->collision(*enemy))
                Game::player->damage(enemy->m_power);
        
        if (Game::player->m_is_attacking)
        {
            Prop attack_prop(Game::player->m_position, Game::player->m_velocity, Game::player->m_size * 2);
            for (const auto& enemy : Game::enemies)
                if (enemy != nullptr && attack_prop.collision(*enemy))
                    enemy->damage(Game::player->m_power);
        }
    }
    m_last_collision += _elapsed_time;

    // check comsulable collisions
    for (const auto& consumable : Game::consumables)
    {
        if (consumable != nullptr && Game::player->collision(*consumable))
        {
            if (consumable->m_type == ConsumableType::HEALTH) Game::player->heal(16);
            else if (consumable->m_type == ConsumableType::POWER) Game::player->m_power += 5;
            Game::consumables.erase(std::remove(Game::consumables.begin(), Game::consumables.end(), consumable), Game::consumables.end());
        }
    }
}

void Arena::level_up()
{
    if (m_level >= 9)
    {
        reset();
        return;
    }
    ++m_level;
    for (int i = 0; i < 5 * m_level; i++)
        spawn_enemy();
}

void Arena::reset()
{
    m_level = 1;
    Game::enemies.clear();
    Game::consumables.clear();

    // DEBUG
    for (int i = 0; i < 5 * m_level; i++)
        spawn_enemy();
}

void Arena::spawn_enemy()
{
    std::uniform_int_distribution<int> border_dist(0, 3);
    int border = border_dist(rng);
    float x, y;

    std::uniform_real_distribution<float> dist_x_top(0, Game::drawable_width);
    std::uniform_real_distribution<float> dist_x_bottom(0, Game::drawable_width);
    std::uniform_real_distribution<float> dist_y_left(0, Game::drawable_height);
    std::uniform_real_distribution<float> dist_y_right(0, Game::drawable_height);

    switch (border)
    {
        case 0: x = dist_x_top(rng); y = 0; break;
        case 1: x = dist_x_bottom(rng); y = Game::drawable_height; break;
        case 2: x = 0; y = dist_y_left(rng); break;
        case 3: x = Game::drawable_width; y = dist_y_right(rng); break;
    }

    Game::enemies.push_back(
        std::make_unique<Entity>(Vec2<float>(x, y),
            Vec2<float>(1.0f, 0.0f), Vec2<float>(16, 16), 100, 1, 0.05f));
}

void Arena::spawn_comsumable()
{
    std::uniform_int_distribution<int> type_dist(0, 1);
    ConsumableType type = static_cast<ConsumableType>(type_dist(rng));

    std::uniform_real_distribution<float> dist_x(0, Game::drawable_width);
    std::uniform_real_distribution<float> dist_y(0, Game::drawable_height);

    Game::consumables.push_back(std::make_unique<Consumable>(type, Vec2<float>(dist_x(rng), dist_y(rng))));
}

void Arena::delete_enemy(const std::unique_ptr<Entity>& _enemy)
{
    if (_enemy == nullptr) return;
    Game::enemies.erase(std::remove(Game::enemies.begin(), Game::enemies.end(), _enemy), Game::enemies.end());
    spawn_comsumable();
}