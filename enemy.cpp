#include "snake.h"
#include "raylib.h"
#include "constants.h"  
#include <vector>
#include"enemy.h"

Enemy::Enemy(Vector2 pos, Vector2 spd) : Snake(pos, spd, RED), active(true) {}

void Enemy:: Update(Vector2 offset) {
    position.x += speed.x;
    position.y += speed.y;

    if (position.x <= offset.x / 2 || position.x + size.x >= screenWidth - offset.x / 2) speed.x *= -1;
    if (position.y <= offset.y / 2 || position.y + size.y >= screenHeight - offset.y / 2) speed.y *= -1;
}

void Enemy:: Draw()  {
    if (active) DrawRectangleV(position, size, color);
}