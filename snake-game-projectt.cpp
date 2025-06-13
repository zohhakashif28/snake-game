#include<iostream>
#include "raylib.h"
#include <vector>
#include"constants.h"
#include"game.h"
using namespace std;



bool operator==(const Vector2& lhs, const Vector2& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

int main() {
    InitWindow(screenWidth, screenHeight, "Snake Game - Levels, Traps (Circle), Lives, Wrapping, BG Color");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.Update();
        game.Draw();
    }

    CloseWindow();
    return 0;
}