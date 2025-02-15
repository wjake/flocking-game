#include "Game.h"

namespace Game
{
    int drawable_width, drawable_height, drawable_scaler,
        window_height, window_width;

    float interim;

    std::unique_ptr<Arena> arena;
    std::unique_ptr<Flocking> flocking;
    std::unique_ptr<Entity> player;
    std::vector<std::unique_ptr<Entity>> enemies;
    std::vector<std::unique_ptr<Consumable>> consumables;
    std::unordered_map<std::string, std::unique_ptr<Animation>> animations;
    std::unordered_map<std::string, std::unique_ptr<Sprite>> sprites;

    void resize(SDL_Window* _window)
    {
        SDL_GetWindowSize(_window, &window_width, &window_height);
        SDL_GL_GetDrawableSize(_window, &drawable_width, &drawable_height);
        drawable_scaler = ((long) drawable_height / window_height) << 1;
    }

    void init(SDL_Window *_window)
    {
        #ifdef UNIT_TEST
        window_width = 1280;
        window_height = 720;
        drawable_width = 1280;
        drawable_height = 720;
        drawable_scaler = 2;
        return;
        #endif

        resize(_window);

        arena = std::make_unique<Arena>();
        flocking = std::make_unique<Flocking>();
    }

    void clean()
    {
        enemies.clear();
    }

    void update(const float _elapsed_time)
    {
        if (_elapsed_time <= 0) return;

        arena->update(_elapsed_time);
        flocking->update(enemies, *player, _elapsed_time);

        // update animations
        animations.at("player_walk_up")->update();
        animations.at("player_walk_down")->update();
        animations.at("player_walk_left")->update();
        animations.at("player_walk_right")->update();
        animations.at("enemy_idle")->update();
        animations.at("enemy_walk")->update();
        animations.at("comsumable_health")->update();
        animations.at("comsumable_power")->update();
    }

    void render(SDL_Renderer* _renderer, std::array<SDL_Texture*, 4> _textures, const float _interim)
    {
        Game::interim = _interim;
        render_background(_renderer, _textures[0], { 112, 144, 32, 32 });

        // render consumables
        for (const std::unique_ptr<Consumable>& consumable : consumables)
        {
            if (consumable->m_type == ConsumableType::HEALTH)
                render_entity(_renderer, _textures[3], animations.at("comsumable_health"), consumable->m_position);
            else if (consumable->m_type == ConsumableType::POWER)
                render_entity(_renderer, _textures[3], animations.at("comsumable_power"), consumable->m_position);
        }

        if (!player->m_is_attacking)
        {
            if (player->m_velocity.m_x == -1)
            {
                player->m_direction = Direction::LEFT;
                render_entity(_renderer, _textures[1], animations.at("player_walk_left"), player);
            }
            else if (player->m_velocity.m_x == 1)
            {
                player->m_direction = Direction::RIGHT;
                render_entity(_renderer, _textures[1], animations.at("player_walk_right"), player);
            }
            else if (player->m_velocity.m_y == -1)
            {
                player->m_direction = Direction::UP;
                render_entity(_renderer, _textures[1], animations.at("player_walk_up"), player);
            }
            else if (player->m_velocity.m_y == 1)
            {
                player->m_direction = Direction::DOWN;
                render_entity(_renderer, _textures[1], animations.at("player_walk_down"), player);
            }
            else if (player->m_velocity.m_x == 0 && player->m_velocity.m_y == 0)
            {
                switch (player->m_direction)
                {
                    case Direction::UP:
                        render_entity(_renderer, _textures[1],
                            animations.at("player_idle_up"), player);
                        break;
                    case Direction::DOWN:
                        render_entity(_renderer, _textures[1],
                            animations.at("player_idle_down"), player);
                        break;
                    case Direction::LEFT:
                        render_entity(_renderer, _textures[1],
                            animations.at("player_idle_left"), player);
                        break;
                    case Direction::RIGHT:
                        render_entity(_renderer, _textures[1],
                            animations.at("player_idle_right"), player);
                        break;
                    default:
                        render_entity(_renderer, _textures[1],
                            animations.at("player_idle_down"), player);
                        break;
                }
            }
        }
        else if (player->m_is_attacking)
        {
            switch (player->m_direction)
            {
                case Direction::UP:
                    render_entity(_renderer, _textures[1],
                        animations.at("player_attack_up"), player);
                    break;
                case Direction::DOWN:
                    render_entity(_renderer, _textures[1],
                        animations.at("player_attack_down"), player);
                    break;
                case Direction::LEFT:
                    render_entity(_renderer, _textures[1],
                        animations.at("player_attack_left"), player);
                    break;
                case Direction::RIGHT:
                    render_entity(_renderer, _textures[1],
                        animations.at("player_attack_right"), player);
                    break;
                default:
                    render_entity(_renderer, _textures[1],
                        animations.at("player_attack_down"), player);
                    break;
            }
        }

        // render enemies
        for (const std::unique_ptr<Entity>& enemy : enemies)
        {
            if (enemy->m_velocity.magnitude() == 0)
                render_entity(_renderer, _textures[2], animations.at("enemy_idle"), enemy);
            else
                render_entity(_renderer, _textures[2], animations.at("enemy_walk"), enemy);
        }
        
        render_health(player->m_cur_health, _renderer, _textures[3], { 64, 64 });
    }

    void render_background(SDL_Renderer* _renderer, SDL_Texture* _texture, SDL_Rect _src)
    {
        SDL_Rect dest_rect;

        for (int y = 0; y < window_height; y += 32) {
            for (int x = 0; x < window_width; x += 32) {
                dest_rect.x = x * drawable_scaler;
                dest_rect.y = y * drawable_scaler;
                dest_rect.w = 32 * drawable_scaler;
                dest_rect.h = 32 * drawable_scaler;
                SDL_RenderCopy(_renderer, _texture, &_src, &dest_rect);
            }
        }
    }

    void render_entity(SDL_Renderer* _renderer, SDL_Texture* _texture,
        const std::unique_ptr<Animation> &_animation, const Vec2<float> _position)
    {
        const Frame& frame = _animation->m_frames[_animation->m_curr_frame];
        SDL_Rect src_rect = { frame.m_x, frame.m_y, frame.m_w, frame.m_h };

        SDL_Rect dest_rect = {
            static_cast<int>(_position.m_x - (frame.m_w * drawable_scaler) / 2), 
            static_cast<int>(_position.m_y - (frame.m_h * drawable_scaler) / 2),
            frame.m_w * drawable_scaler, frame.m_h * drawable_scaler
        };

        SDL_RenderCopy(_renderer, _texture, &src_rect, &dest_rect);
    }

    void render_entity(SDL_Renderer* _renderer, SDL_Texture* _texture,
        const std::unique_ptr<Animation> &_animation, const std::unique_ptr<Entity>& _entity)
    {
        Vec2<float> extrapolated_pos = _entity->m_position + _entity->m_velocity * _entity->m_speed * Game::interim;
        render_entity(_renderer, _texture, _animation, extrapolated_pos);
    }

    void render_health(int health, SDL_Renderer* _renderer, SDL_Texture* _texture, const Vec2<float> _position)
    {
        const int heart_value = 20;

        int full_hearts = health / heart_value;
        int remainder = health % heart_value;
        int h_width = sprites["heart_0"]->m_src.w * drawable_scaler;
        int total_hearts = Game::player->m_max_health / heart_value;

        for (int i = 0; i < total_hearts; ++i)
        {
            Vec2<float> h_loc(_position.m_x + (i * h_width), _position.m_y);

            if (i < full_hearts)
            {
                sprites["heart_0"]->draw(_renderer, _texture, h_loc);
            }
            else if (i == full_hearts)
            {
                if (remainder >= 15)
                    sprites["heart_1"]->draw(_renderer, _texture, h_loc);
                else if (remainder >= 10)
                    sprites["heart_2"]->draw(_renderer, _texture, h_loc);
                else if (remainder >= 5)
                    sprites["heart_3"]->draw(_renderer, _texture, h_loc);
                else 
                    sprites["heart_4"]->draw(_renderer, _texture, h_loc);
            }
            else
            {
                sprites["heart_4"]->draw(_renderer, _texture, h_loc);
            }
        }
    }

    void reset()
    {
        arena->reset();
        player->m_cur_health = player->m_max_health;
    }


    void load_data(const char* filename)
    {
        FILE* fp = fopen(filename, "r");
        if (fp == nullptr)
        {
            std::cerr << "Could not open file " << filename << '\n';
            return;
        }

        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        rapidjson::Document d;
        d.ParseStream(is);
        fclose(fp);

        if (d.HasParseError())
        {
            std::cerr << "Parse error!" << '\n';
            return;
        }

        if (!d.HasMember("animations") || !d["animations"].IsObject())
        {
            std::cerr << "Invalid or missing animations data" << '\n';
            return;
        }

        if (!d.HasMember("sprites") || !d["sprites"].IsObject())
        {
            std::cerr << "Invalid or missing sprites data" << '\n';
            return;
        }

        const rapidjson::Value& animation_data = d["animations"];
        for (rapidjson::Value::ConstMemberIterator entity_itr = animation_data.MemberBegin(); entity_itr != animation_data.MemberEnd(); ++entity_itr)
        {
            const std::string& entity_name = entity_itr->name.GetString();
            const rapidjson::Value& entity_animations = entity_itr->value;

            for (rapidjson::Value::ConstMemberIterator anim_itr = entity_animations.MemberBegin(); anim_itr != entity_animations.MemberEnd(); ++anim_itr)
            {
                const std::string& animation_name = anim_itr->name.GetString();
                std::cout << "Loading animation: " << entity_name << "_" << animation_name << '\n';

                if (!anim_itr->value.HasMember("frames") || !anim_itr->value["frames"].IsArray())
                {
                    std::cerr << "Invalid frames data for animation: " << entity_name << "_" << animation_name << '\n';
                    continue;
                }

                const rapidjson::Value& animation_frames = anim_itr->value["frames"];
                std::vector<Frame> frames;

                for (rapidjson::SizeType i = 0; i < animation_frames.Size(); ++i)
                {
                    const rapidjson::Value& frame_data = animation_frames[i];

                    if (!frame_data.HasMember("x") || !frame_data["x"].IsInt() ||
                        !frame_data.HasMember("y") || !frame_data["y"].IsInt() ||
                        !frame_data.HasMember("w") || !frame_data["w"].IsInt() ||
                        !frame_data.HasMember("h") || !frame_data["h"].IsInt())
                    {
                        std::cerr << "Invalid frame data at index " << i << " for animation: " << entity_name << "_" << animation_name << '\n';
                        continue;
                    }

                    Frame frame = {
                        frame_data["x"].GetInt(),
                        frame_data["y"].GetInt(),
                        frame_data["w"].GetInt(),
                        frame_data["h"].GetInt()
                    };

                    frames.push_back(frame);
                }

                int curr_frame = anim_itr->value["curr_frame"].GetInt();
                int frame_dur = anim_itr->value["frame_dur"].GetInt();

                Animation animation(curr_frame, frame_dur, frames);
                animations.insert(std::make_pair(entity_name + "_" + animation_name, std::make_unique<Animation>(animation)));
            }
        }

        const rapidjson::Value& sprite_data = d["sprites"];

        for (rapidjson::Value::ConstMemberIterator sprites_itr = sprite_data.MemberBegin(); sprites_itr != sprite_data.MemberEnd(); ++sprites_itr)
        {
            const std::string& obj_name = sprites_itr->name.GetString();
            const rapidjson::Value& obj_sprites = sprites_itr->value;

            if (obj_sprites.HasMember("x"))
            {
                std::cout << "Loading sprite: " << obj_name << '\n';

                SDL_Rect src = {
                    obj_sprites["x"].GetInt(),
                    obj_sprites["y"].GetInt(),
                    obj_sprites["w"].GetInt(),
                    obj_sprites["h"].GetInt()
                };

                sprites.insert(std::make_pair(obj_name, new Sprite(src)));
                continue;
            }

            for (rapidjson::Value::ConstMemberIterator sprite_itr = obj_sprites.MemberBegin(); sprite_itr != obj_sprites.MemberEnd(); ++sprite_itr)
            {
                const std::string& obj_sprite_name = sprite_itr->name.GetString();
                const rapidjson::Value& obj_sprite = sprite_itr->value;

                std::cout << "Loading sprite: " << obj_name << "_" << obj_sprite_name << '\n';

                if (!obj_sprite.HasMember("x") || !obj_sprite["x"].IsInt() ||
                    !obj_sprite.HasMember("y") || !obj_sprite["y"].IsInt() ||
                    !obj_sprite.HasMember("w") || !obj_sprite["w"].IsInt() ||
                    !obj_sprite.HasMember("h") || !obj_sprite["h"].IsInt())
                {
                    std::cerr << "Invalid sprite data for object: " << obj_name << "_" << obj_sprite_name << '\n';
                    continue;
                }

                SDL_Rect src = {
                    obj_sprite["x"].GetInt(),
                    obj_sprite["y"].GetInt(),
                    obj_sprite["w"].GetInt(),
                    obj_sprite["h"].GetInt()
                };

                sprites.insert(std::make_pair(obj_name + "_" + obj_sprite_name, new Sprite(src)));
            }

        }
    }
}