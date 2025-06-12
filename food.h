#pragma once
#include "gameobject.h"

class Food : public GameObject {
public:
    bool active;

    Food();
    void Spawn(Vector2 offset);
    void Draw() override;
};
