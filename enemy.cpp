#include "Enemy.h"

extern const int screenWidth;
extern const int screenHeight;
#define SQUARE_SIZE 31

Enemy::Enemy() {
    size = { (float)SQUARE_SIZE, (float)SQUARE_SIZE };
    color = RED;
    active = true;
}

void Enemy::Init(Vector2 offset) {
    position = {
        (float)(GetRandomValue(0, screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2),
        (float)(GetRandomValue(0, screenHeight / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.y / 2)
    };

    int dir = GetRandomValue(0, 3);
    switch (dir) {
    case 0: speed = { SQUARE_SIZE / 40.0f, 0 }; break;
    case 1: speed = { -SQUARE_SIZE / 40.0f, 0 }; break;
    case 2: speed = { 0, SQUARE_SIZE / 40.0f }; break;
    case 3: speed = { 0, -SQUARE_SIZE / 40.0f }; break;
    }
}

void Enemy::Update(Vector2 offset) {
    if (!active) return;
    position.x += speed.x;
    position.y += speed.y;

    if (position.x <= offset.x / 2 || position.x + size.x >= screenWidth - offset.x / 2) speed.x *= -1;
    if (position.y <= offset.y / 2 || position.y + size.y >= screenHeight - offset.y / 2) speed.y *= -1;
}
