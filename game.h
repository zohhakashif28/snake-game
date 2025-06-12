#pragma once
#include "player.h"
#include "enemy.h"
#include "food.h"
#include "trap.h"

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