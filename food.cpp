#include "gameobject.h"
#include "raylib.h"
#include "constants.h"
#include"food.h"
Food::Food() {
    size = { (float)SQUARE_SIZE, (float)SQUARE_SIZE };
    color = GREEN;
    active = false;
}

void Food:: Spawn(Vector2 offset) {
    active = true;
    position = {
        (float)(GetRandomValue(0, screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2),
        (float)(GetRandomValue(0, screenHeight / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.y / 2)
    };
}
void Food:: Draw()  {
    float radius = size.x / 2.0f;
    DrawCircleV({ position.x + radius, position.y + radius }, radius, color);
}