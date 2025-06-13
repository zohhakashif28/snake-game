#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "snake.h"
#include "raylib.h"
#include "constants.h"  
#include <vector>

class Enemy : public Snake {
public:
    bool active;

    Enemy(Vector2 pos, Vector2 spd);

    void Update(Vector2 offset);
    void Draw() override;
};

#endif 
