#include "player.h"
#include "food.h"
#include "enemy.h"
#include "trap.h"
#include "constants.h"
#include "raylib.h"
#include <vector>
#include"game.h"
Game:: Game() : player({ screenWidth / 2.0f, screenHeight / 2.0f }, { 0, 0 }), level(1) {
    Init();
}


void Game:: Init() {
    speedFactor = 1.0f + level * 0.2f;

    offset = { (float)(screenWidth % SQUARE_SIZE), (float)(screenHeight % SQUARE_SIZE) };
    framesCounter = 0;
    gameOver = false;
    traps.clear();
    enemies.clear();

    float speedFactor = 1.0f + level * 0.2f;
    int numEnemies = BASE_ENEMIES + level;

    for (int i = 0; i < numEnemies; i++) {
        Vector2 pos = {
            (float)(GetRandomValue(0, screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2),
            (float)(GetRandomValue(0, screenHeight / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.y / 2)
        };
        Vector2 spd = { SQUARE_SIZE / 40.0f * speedFactor, 0 };
        if (GetRandomValue(0, 1)) std::swap(spd.x, spd.y);
        enemies.push_back(new Enemy(pos, spd));
    }

    for (int i = 0; i < level * MAX_TRAPS; i++) {
        Vector2 trapPos = {
            (float)(GetRandomValue(0, screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2),
            (float)(GetRandomValue(0, screenHeight / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.y / 2)
        };
        traps.emplace_back(trapPos);
    }

    fruit.active = false;
}

void Game:: Update() {



    if (gameOver) {
        if (IsKeyPressed(KEY_ENTER)) *this = Game();
        return;
    }

    player.HandleInput(speedFactor);
    if (framesCounter % 5 == 0)
        player.Update();

    for (Enemy* enemy : enemies) {
        if (!enemy->active) continue;

        enemy->Update(offset);

        // Collision with head
        if (CheckCollisionRecs(player.GetRect(), enemy->GetRect())) {
            player.lives--;
            enemy->active = false;
            if (player.lives <= 0) gameOver = true;
            continue;
        }

        // Collision with body
        for (const Rectangle& bodyRect : player.GetBodyRects()) {
            if (CheckCollisionRecs(bodyRect, enemy->GetRect())) {
                enemy->active = false;
                break;
            }
        }
    }

    for (Trap& trap : traps) {
        if (CheckCollisionRecs(trap.GetRect(), player.GetRect()))
        {
            player.lives--;
            if (player.lives <= 0) gameOver = true;
        }
    }

    if (!fruit.active)
        fruit.Spawn(offset);

    if (CheckCollisionRecs(player.GetRect(), fruit.GetRect())) {
        player.score++;
        player.Grow();
        fruit.active = false;

        if (player.score % 3 == 0 && level < 5) {
            level++;
            Init();
        }
    }

    framesCounter++;
}

void Game:: Draw() {
    BeginDrawing();
    ClearBackground(GetBackgroundColor());

    if (!gameOver) {
        fruit.Draw();
        for (Trap& trap : traps) trap.Draw();
        for (Enemy* enemy : enemies) enemy->Draw();
        player.Draw();
        DrawLifeBar();  // Draw the vertical life bar on the left

        DrawText(TextFormat("Lives:"), 10, 10, 20, BLACK);
        DrawText(TextFormat("Score: %d", player.score), 10, 30, 20, BLACK);
        DrawText(TextFormat("Level: %d", level), 10, 50, 20, BLACK);
    }
    else {
        DrawText("GAME OVER", screenWidth / 2 - 80, screenHeight / 2 - 20, 40, RED);
        DrawText("Press ENTER to Restart", screenWidth / 2 - 100, screenHeight / 2 + 30, 20, GRAY);
    }


    EndDrawing();
}
void Game:: DrawLifeBar() {
    float barX = 85;                // Right next to "Lives:"
    float barY = 12;
    float totalWidth = 90;          // Full width when lives = MAX_LIVES
    float height = 12;

    // Draw the background (gray)
    DrawRectangle(barX, barY, totalWidth, height, GRAY);

    // Calculate how much of the bar to fill
    float filledWidth = totalWidth * ((float)player.lives / MAX_LIVES);

    // Draw the filled portion in black
    DrawRectangle(barX, barY, filledWidth, height, BLACK);
}


Color Game:: GetBackgroundColor() {
    switch (level) {
    case 1: return PINK;
    case 2: return BEIGE;
    case 3: return SKYBLUE;
    case 4: return YELLOW;
    case 5: return GREEN;
    default: return PINK;
    }
}