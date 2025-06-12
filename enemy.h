#pragma once
#include "snake.h"

class Enemy : public Snake {
public:
    bool active;

    Enemy(Vector2 pos, Vector2 spd);
    void Update(Vector2 offset);
    void Draw() override;
};