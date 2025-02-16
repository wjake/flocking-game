[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/RM1pL2Qm)

# Project Idea

Simple game inspired by [Vampire Survivors](https://store.steampowered.com/app/1794680/Vampire_Survivors/) which will make use of a flocking system and will be built using SDL2.  

Enemies will appear on the arena’s edge and head towards the player, who’s goal is to survive for as long as possible. The game progresses in waves, with each wave increasing enemy numbers and health. Players can dodge enemies, wield weapons to damage and kill them, and collect food items that restore health. Enemies will maintain separation to remain visible and avoid overlap, and alignment to steer towards the player. Cohesion could keep certain enemy types in groups.

![Game screenshot](<img/Screenshot 2025-01-30 at 07.26.02.png>)

## Requirements

SDL2 for window context and sdl2-image library used for image handling.  RapidJSON for json file handling.

```
./vcpkg install SDL2
./vcpkg install sdl2-image
./vcpkg install rapidjson
```

## Building

```
mkdir build && cd build
cmake ..
make
```

## Assets Used

- [Zelda-like tilesets and sprites](https://opengameart.org/content/zelda-like-tilesets-and-sprites) under [CC0 1.0 UNIVERSAL](https://creativecommons.org/publicdomain/zero/1.0/)

## Related Material
- Reynolds, C.W., 1987. Flocks, Herds, and Schools: A Distributed Behavioral Model. In: Computer Graphics (SIGGRAPH '87 Conference Proceedings), pp.25-34. Available at: <http://www.red3d.com/cwr/boids/> [Accessed 30 November 2024].

