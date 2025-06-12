#include "Game.h"
#include "raylib.h"

#define screenWidth 800
#define screenHeight 450
#define BASE_ENEMIES 2
#define MAX_TRAPS 5
#define SQUARE_SIZE 31
#define MAX_LIVES 3

//Game::Game() {
//    Init();
//}
Game::Game() : player({ 100, 100 }, { 0, 0 }) {
    Init();
}


void Game::Init() {
    offset = { 60, 60 };
    framesCounter = 0;
    gameOver = false;
    //level = 1;
    //speedFactor = 1.0f;
    speedFactor = 1.0f + level * 0.2f;

    player = Player({ 100, 100 }, { 0, 0 });
    fruit = Food();

    traps.clear();
    for (int i = 0; i < level && i < MAX_TRAPS; i++) {
        Vector2 trapPos = {
            (float)(GetRandomValue(0, screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2),
            (float)(GetRandomValue(0, screenHeight / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.y / 2)
        };
        traps.push_back(Trap(trapPos));
    }

    for (auto enemy : enemies) delete enemy;
    enemies.clear();
    for (int i = 0; i < BASE_ENEMIES + level; i++) {
        Vector2 enemyPos = {
            (float)(GetRandomValue(0, screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2),
            (float)(GetRandomValue(0, screenHeight / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.y / 2)
        };
        Vector2 enemySpd = { (float)((GetRandomValue(0, 1) * 2 - 1) * 2), (float)((GetRandomValue(0, 1) * 2 - 1) * 2) };
        enemies.push_back(new Enemy(enemyPos, enemySpd));
    }

    fruit.Spawn(offset);
}

void Game::Update() {
    if (gameOver) {
        if (IsKeyPressed(KEY_ENTER)) {
            gameOver = false;
            Init();
        }
        return;
    }

    framesCounter++;
    player.HandleInput(speedFactor);

    if ((framesCounter % 10) == 0) {
        player.Update();
        for (auto& enemy : enemies) {
            enemy->Update(offset);
        }

        for (auto& trap : traps) {
            if (CheckCollisionRecs(player.GetRect(), trap.GetRect())) {
                player.lives--;
                if (player.lives <= 0) gameOver = true;
            }
        }

        for (auto& enemy : enemies) {
            if (enemy->active && CheckCollisionRecs(player.GetRect(), enemy->GetRect())) {
                player.lives--;
                enemy->active = false;
                if (player.lives <= 0) gameOver = true;
            }
        }

        if (fruit.active && CheckCollisionRecs(player.GetRect(), fruit.GetRect())) {
            player.Grow();
            fruit.active = false;
            player.score += 10;

            if (player.score % 50 == 0) {
                level++;
                speedFactor += 0.2f;
                Init();
            }
            else {
                fruit.Spawn(offset);
            }
        }

        auto bodyRects = player.GetBodyRects();
        for (auto& part : bodyRects) {
            if (CheckCollisionRecs(player.GetRect(), part)) {
                player.lives--;
                if (player.lives <= 0) gameOver = true;
                break;
            }
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(GetBackgroundColor());

    if (!gameOver) {
        for (auto& trap : traps) trap.Draw();
        for (auto& enemy : enemies) enemy->Draw();
        player.Draw();
        if (fruit.active) fruit.Draw();
        DrawLifeBar();

        DrawText(TextFormat("Score: %i", player.score), 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Level: %i", level), screenWidth - 100, 10, 20, DARKGRAY);
    }
    else {
        DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 30, 40, RED);
        DrawText("PRESS [ENTER] TO RESTART", screenWidth / 2 - 150, screenHeight / 2 + 10, 20, LIGHTGRAY);
    }

    EndDrawing();
}

void Game::DrawLifeBar() {
    for (int i = 0; i < MAX_LIVES; i++) {
        DrawRectangle(10 + i * 35, 40, 30, 30, LIGHTGRAY);
    }
    for (int i = 0; i < player.lives; i++) {
        DrawRectangle(10 + i * 35, 40, 30, 30, RED);
    }
}

Color Game::GetBackgroundColor() {
    if (level < 3) return RAYWHITE;
    if (level < 6) return LIGHTGRAY;
    if (level < 9) return GRAY;
    return DARKGRAY;
}
