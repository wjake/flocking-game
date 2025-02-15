#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <array>
#include <unordered_map>
#include <iostream>
#include <random>
#include "rapidjson/document.h" 
#include "rapidjson/filereadstream.h" 
#include "Entity.h"
#include "Consumable.h"
#include "Arena.h"
#include "Animation.h"
#include "Flocking.h"
#include "Sprite.h"

namespace Game
{
    extern int drawable_width, drawable_height, drawable_scaler;
    extern float interim;
    extern std::unique_ptr<Arena> arena;
    extern std::unique_ptr<Flocking> flocking;
    extern std::unique_ptr<Entity> player;
    extern std::vector<std::unique_ptr<Entity>> enemies;
    extern std::vector<std::unique_ptr<Consumable>> consumables;
    extern std::unordered_map<std::string, std::unique_ptr<Animation>> animations;
    extern std::unordered_map<std::string, std::unique_ptr<Sprite>> sprites;

    /**
     * @brief Reset the game
     */
    void reset();

    /**
     * @brief Render the background
     * @param _renderer SDL_Renderer to render to
     * @param _texture SDL_Texture to render
     * @param _src Source from texture to render
     */
    void render_background(SDL_Renderer* _renderer, SDL_Texture* _texture, SDL_Rect _src);

    /**
     * @brief Render an entity
     * @param _renderer SDL_Renderer to render to
     * @param _texture SDL_Texture to render
     * @param _animation Animation to render
     * @param _position Position to render at
     */
    void render_entity(SDL_Renderer* _renderer, SDL_Texture* _texture, const std::unique_ptr<Animation> &_animation,
        const Vec2<float> _position);

    /**
     * @brief Render an entity
     * @param _renderer SDL_Renderer to render to
     * @param _texture SDL_Texture to render
     * @param _animation Animation to render
     * @param _entity Entity to render
     */
    void render_entity(SDL_Renderer* _renderer, SDL_Texture* _texture, const std::unique_ptr<Animation> &_animation,
        const std::unique_ptr<Entity>& _entity);

    /**
     * @brief Render health
     * @param health Health to render
     * @param _renderer SDL_Renderer to render to
     * @param _texture SDL_Texture to render
     * @param _position Position to render at
     */
    void render_health(int health, SDL_Renderer* _renderer, SDL_Texture* _texture, Vec2<float> _position);

    /**
     * @brief Load data from data file
     * @param filename File to load data from
     */
    void load_data(const char* filename);

    /**
     * @brief Resize the window
     * @param _window The window to resize
     */
    void resize(SDL_Window* _window);

    /**
     * @brief Construct a new Game object
     * @param _window The window to render to
     */
    void init(SDL_Window *_window);

    /**
     * @brief Clean the game state
     */
    void clean();

    /**
     * @brief Update the game state
     * @param _elapsed_time Time since last update
     */
    void update(const float _elapsed_time);

    /**
     * @brief Render the current game state
     * @param _renderer SDL_Renderer to render to
     * @param _texture_objects SDL_Texture for the objects
     * @param _interim The interim time for interpolating
     */
    void render(SDL_Renderer* _renderer, std::array<SDL_Texture*, 4> _textures, const float _interim);
};

#endif