#include"player.h"
#include"snake.h"
#include "raylib.h"
#include"constants.h"
Player::Player(Vector2 pos, Vector2 spd) : Snake(pos, spd, DARKBLUE), lives(MAX_LIVES), score(0) {
    body.push_back(position);
}

void Player:: HandleInput(float speedFactor) {
    float baseSpeed = SQUARE_SIZE / 4.0f * speedFactor;

    if (IsKeyPressed(KEY_RIGHT) && speed.x == 0) speed = { baseSpeed, 0 };
    if (IsKeyPressed(KEY_LEFT) && speed.x == 0) speed = { -baseSpeed, 0 };
    if (IsKeyPressed(KEY_UP) && speed.y == 0) speed = { 0, -baseSpeed };
    if (IsKeyPressed(KEY_DOWN) && speed.y == 0) speed = { 0, baseSpeed };
}


void Player:: Update()  {
    Vector2 prevHead = position;
    Snake::Update();

    if (!body.empty()) {
        for (int i = body.size() - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }
        body[0] = prevHead;
    }
}

void Player:: Grow() {
    body.push_back(body.back());
}


void Player:: Draw()  {
    for (Vector2& part : body) {
        DrawRectangleV(part, size, { 255, 224, 189, 255 });  // Body: Skin color
    }
    DrawRectangleV(position, size, BROWN);  // Head: Dark brown
}


std::vector<Rectangle> Player:: GetBodyRects() const {
    std::vector<Rectangle> rects;
    for (const auto& part : body) {
        rects.push_back({ part.x, part.y, size.x, size.y });
    }
    return rects;
}