#pragma once
#ifndef TRAP_H
#define TRAP_H

#include "gameobject.h"
#include "raylib.h"
#include"constants.h"

class Trap : public GameObject {
public:
    Trap(Vector2 pos);

    void Draw() override;
    Rectangle GetRect() const override;
};

#endif // TRAP_H
