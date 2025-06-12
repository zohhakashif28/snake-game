#pragma once
#include "gameobject.h"

class Snake : public GameObject {
public:
    Vector2 speed;

    Snake(Vector2 pos, Vector2 spd, Color col);
    virtual void Update();
};