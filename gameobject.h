#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"

class GameObject {
public:
    Vector2 position;
    Vector2 size;
    Color color;

    GameObject();
    GameObject(Vector2 pos, Vector2 sz, Color col);

    virtual void Draw();
    virtual Rectangle GetRect() const;
};

#endif 
