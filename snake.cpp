#include"snake.h"
#include"constants.h"
#include "raylib.h"

Snake::Snake(Vector2 pos, Vector2 spd, Color col) : GameObject(pos, { (float)SQUARE_SIZE, (float)SQUARE_SIZE }, col), speed(spd) {}

void Snake::Update() {
    position.x += speed.x;
    position.y += speed.y;

    if (position.x < 0) position.x = screenWidth - size.x;
    if (position.x >= screenWidth) position.x = 0;
    if (position.y < 0) position.y = screenHeight - size.y;
    if (position.y >= screenHeight) position.y = 0;
}