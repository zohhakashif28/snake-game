#pragma once
#include "gameobject.h"

class Trap : public GameObject {
public:
    Trap(Vector2 pos);
    void Draw() override;
    Rectangle GetRect() const override;
};