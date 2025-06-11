#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject {
public:
    Vector2 speed;
    bool active;

    Enemy();
    void Init(Vector2 offset);
    void Update(Vector2 offset);
};

#endif
