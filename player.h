#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "snake.h"
#include "raylib.h"
#include <vector>
#include "constants.h"  

class Player : public Snake {
public:
    int lives;
    int score;
    std::vector<Vector2> body;

    Player(Vector2 pos, Vector2 spd);

    void HandleInput(float speedFactor);
    void Update() override;
    void Grow();
    void Draw() override;
    std::vector<Rectangle> GetBodyRects() const;
};

#endif 
