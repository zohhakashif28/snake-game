#ifndef FOOD_H
#define FOOD_H

#include "GameObject.h"
#include <vector>

class Food : public GameObject {
public:
    bool active;

    Food();
    void Spawn(std::vector<Vector2>& occupiedPositions, Vector2 offset);
};

#endif
