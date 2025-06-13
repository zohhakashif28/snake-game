#pragma once
#ifndef FOOD_H
#define FOOD_H

#include "gameobject.h"
#include "raylib.h"
#include "constants.h" 

class Food : public GameObject {
public:
    bool active;

    Food();

    void Spawn(Vector2 offset);
    void Draw() override;
};

#endif 
