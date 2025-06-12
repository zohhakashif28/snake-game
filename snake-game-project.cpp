#include "raylib.h"
#include "game.h"

int main() {
    InitWindow(800, 450, "Snake Game - Separated Classes");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.Update();
        game.Draw();
    }

    CloseWindow();
    return 0;
}
