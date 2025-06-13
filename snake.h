#pragma once
#ifndef SNAKE_H
#define SNAKE_H

#include "gameobject.h"
#include "raylib.h"
#include "constants.h"  

class Snake : public GameObject {
public:
    Vector2 speed;

    Snake(Vector2 pos, Vector2 spd, Color col);

    virtual void Update();  // Or 'override' if Update() is virtual in GameObject
};

#endif 
