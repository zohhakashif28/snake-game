#include "Food.h"

extern const int screenWidth;
extern const int screenHeight;
#define SQUARE_SIZE 31

Food::Food() {
    size = { (float)SQUARE_SIZE, (float)SQUARE_SIZE };
    color = SKYBLUE;
    active = false;
}

void Food::Spawn(std::vector<Vector2>& occupiedPositions, Vector2 offset) {
    active = true;
    do {
        position = {
            (float)(GetRandomValue(0, screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2),
            (float)(GetRandomValue(0, screenHeight / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.y / 2)
        };
    } while (std::find(occupiedPositions.begin(), occupiedPositions.end(), position) != occupiedPositions.end());
}
