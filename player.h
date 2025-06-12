#pragma once
#include "snake.h"
#include <vector>

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