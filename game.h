#pragma once
#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "food.h"
#include "enemy.h"
#include "trap.h"
#include "constants.h"
#include "raylib.h"
#include <vector>

class Game {
public:
    Player player;
    Food fruit;
    std::vector<Enemy*> enemies;
    std::vector<Trap> traps;
    Vector2 offset;
    int framesCounter;
    bool gameOver;
    int level;
    float speedFactor;

    Game();

    void Init();
    void Update();
    void Draw();
    void DrawLifeBar();
    Color GetBackgroundColor();
};

#endif // GAME_H
