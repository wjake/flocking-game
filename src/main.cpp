#ifdef WIN32
    #define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <array>
#include "Game.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FRAME_DELAY 16.67

void SDLErrorExit(const std::string &_msg);
SDL_Texture* load_texture(SDL_Renderer* renderer, const char* filename);

#ifndef UNIT_TEST
int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) SDLErrorExit("Unable to initialize SDL");

    SDL_Window *window = SDL_CreateWindow(
        "SDL2 Flocking Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (!window) SDLErrorExit("Unable to create window");

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) SDLErrorExit("Unable to create renderer");
    
    IMG_Init(IMG_INIT_PNG);
    std::array<SDL_Texture*, 4> textures = {
        load_texture(renderer, "assets/overworld.png"),
        load_texture(renderer, "assets/character.png"),
        load_texture(renderer, "assets/log.png"),
        load_texture(renderer, "assets/objects.png")
    };
    IMG_Quit();

    Game::init(window);
    Game::load_data("assets/data.json");
    
    SDL_Event event;
    Uint32 last_ticks = SDL_GetTicks64();
    Uint32 frame_delay = 0;
    bool quit = false;
    while (!quit)
    {
        Uint32 curr_ticks = SDL_GetTicks64();
        Uint32 elapsed_ticks = curr_ticks - last_ticks;
        last_ticks = curr_ticks;
        frame_delay += elapsed_ticks;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT : quit = true; break;
                case SDL_WINDOWEVENT : Game::resize(window); break;
                case SDL_KEYUP :
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_w : case SDLK_UP: case SDLK_s : case SDLK_DOWN :
                            Game::player->m_velocity.m_y = 0;
                            break;
                        case SDLK_a : case SDLK_LEFT : case SDLK_d : case SDLK_RIGHT :
                            Game::player->m_velocity.m_x = 0;
                            break;
                        default : break;
                    }
                } break;
                case SDL_KEYDOWN :
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE : quit = true; break;
                        case SDLK_w : case SDLK_UP : Game::player->m_velocity.m_y = -1; break;
                        case SDLK_s : case SDLK_DOWN : Game::player->m_velocity.m_y = 1; break;
                        case SDLK_a : case SDLK_LEFT : Game::player->m_velocity.m_x = -1; break;
                        case SDLK_d : case SDLK_RIGHT : Game::player->m_velocity.m_x = 1; break;
                        case SDLK_SPACE : Game::player->m_is_attacking = true; break;
                        case SDLK_g : SDL_SetWindowFullscreen(window, SDL_TRUE); break;
                        case SDLK_h : SDL_SetWindowFullscreen(window, SDL_FALSE); break;
                        default : break;
                    }
                } break;
                default : break;
            }
        }

        while (frame_delay >= FRAME_DELAY)
        {
            Game::update(FRAME_DELAY);
            frame_delay -= FRAME_DELAY;
        }

        SDL_RenderClear(renderer);
        Game::render(renderer, textures, frame_delay / FRAME_DELAY);
        SDL_RenderPresent(renderer);
    }

    Game::clean();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
#endif

SDL_Texture* load_texture(SDL_Renderer* _renderer, const char* _filename)
{
    std::cout << "Loading texture: " << _filename << '\n';
    SDL_Surface* image = IMG_Load(_filename);
    if (image == nullptr) SDLErrorExit("Unable to load texture image.");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, image);
    SDL_FreeSurface(image);
    return texture;
}

void SDLErrorExit(const std::string &_msg)
{
    std::cerr << _msg << '\n';
    std::cerr << SDL_GetError() << '\n';
    SDL_Quit();
    exit(EXIT_FAILURE);
}
