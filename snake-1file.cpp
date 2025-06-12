#include<iostream>
#include "raylib.h"
#include <vector>

using namespace std;

#define SQUARE_SIZE 31
#define BASE_ENEMIES 2
#define MAX_TRAPS 5
#define MAX_LIVES 3
const int screenWidth = 800;
const int screenHeight = 450;

bool operator==(const Vector2& lhs, const Vector2& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

class GameObject {
public:
    Vector2 position;
    Vector2 size;
    Color color;

    GameObject() {}
    GameObject(Vector2 pos, Vector2 sz, Color col) : position(pos), size(sz), color(col) {}

    virtual void Draw() {
        DrawRectangleV(position, size, color);
    }

    virtual Rectangle GetRect() const {
        return { position.x, position.y, size.x, size.y };
    }
};

//class Trap : public GameObject {
//public:
//    float radius;
//
//    Trap(Vector2 pos) {
//        radius = SQUARE_SIZE / 2.0f;
//        position = pos;
//        size = { radius * 2, radius * 2 };
//        color = DARKGRAY;
//    }
//
//    void Draw() override {
//        DrawCircleV({ position.x + radius, position.y + radius }, radius, color);
//    }
//
//    Rectangle GetRect() const override {
//        return { position.x, position.y, size.x, size.y };
//    }
//
//    Vector2 GetCenter() const {
//        return { position.x + radius, position.y + radius };
//    }
//};

class Trap : public GameObject {
public:
    Trap(Vector2 pos) {
        position = pos;
        size = { (float)SQUARE_SIZE, 4 };  // Thin horizontal line
        color = BLACK;
    }

    void Draw() override {
        DrawRectangleV(position, size, color);
    }

    Rectangle GetRect() const override {
        return { position.x, position.y, size.x, size.y };
    }
};


class Snake : public GameObject {
public:
    Vector2 speed;

    Snake(Vector2 pos, Vector2 spd, Color col) : GameObject(pos, { (float)SQUARE_SIZE, (float)SQUARE_SIZE }, col), speed(spd) {}

    virtual void Update() {
        position.x += speed.x;
        position.y += speed.y;

        if (position.x < 0) position.x = screenWidth - size.x;
        if (position.x >= screenWidth) position.x = 0;
        if (position.y < 0) position.y = screenHeight - size.y;
        if (position.y >= screenHeight) position.y = 0;
    }
};

class Player : public Snake {
public:
    int lives;
    int score;
    std::vector<Vector2> body;

    Player(Vector2 pos, Vector2 spd) : Snake(pos, spd, DARKBLUE), lives(MAX_LIVES), score(0) {
        body.push_back(position);
    }

    /*void HandleInput() {
        if (IsKeyPressed(KEY_RIGHT) && speed.x == 0) speed = { SQUARE_SIZE / 4.0f, 0 };
        if (IsKeyPressed(KEY_LEFT) && speed.x == 0) speed = { -SQUARE_SIZE / 4.0f, 0 };
        if (IsKeyPressed(KEY_UP) && speed.y == 0) speed = { 0, -SQUARE_SIZE / 4.0f };
        if (IsKeyPressed(KEY_DOWN) && speed.y == 0) speed = { 0, SQUARE_SIZE / 4.0f };
    }*/

    void HandleInput(float speedFactor) {
        float baseSpeed = SQUARE_SIZE / 4.0f * speedFactor;

        if (IsKeyPressed(KEY_RIGHT) && speed.x == 0) speed = { baseSpeed, 0 };
        if (IsKeyPressed(KEY_LEFT) && speed.x == 0) speed = { -baseSpeed, 0 };
        if (IsKeyPressed(KEY_UP) && speed.y == 0) speed = { 0, -baseSpeed };
        if (IsKeyPressed(KEY_DOWN) && speed.y == 0) speed = { 0, baseSpeed };
    }


    void Update() override {
        Vector2 prevHead = position;
        Snake::Update();

        if (!body.empty()) {
            for (int i = body.size() - 1; i > 0; i--) {
                body[i] = body[i - 1];
            }
            body[0] = prevHead;
        }
    }

    void Grow() {
        body.push_back(body.back());
    }

    /* void Draw() override {
         for (Vector2& part : body) {
             DrawRectangleV(part, size, DARKBLUE);
         }
         DrawRectangleV(position, size, color);
     }*/

    void Draw() override {
        for (Vector2& part : body) {
            DrawRectangleV(part, size, { 255, 224, 189, 255 });  // Body: Skin color
        }
        DrawRectangleV(position, size, BROWN);  // Head: Dark brown
    }


    std::vector<Rectangle> GetBodyRects() const {
        std::vector<Rectangle> rects;
        for (const auto& part : body) {
            rects.push_back({ part.x, part.y, size.x, size.y });
        }
        return rects;
    }
};

class Enemy : public Snake {
public:
    bool active;

    Enemy(Vector2 pos, Vector2 spd) : Snake(pos, spd, RED), active(true) {}

    void Update(Vector2 offset) {
        position.x += speed.x;
        position.y += speed.y;

        if (position.x <= offset.x / 2 || position.x + size.x >= screenWidth - offset.x / 2) speed.x *= -1;
        if (position.y <= offset.y / 2 || position.y + size.y >= screenHeight - offset.y / 2) speed.y *= -1;
    }

    void Draw() override {
        if (active) DrawRectangleV(position, size, color);
    }
   
};

class Food : public GameObject {
public:
    bool active;

    Food() {
        size = { (float)SQUARE_SIZE, (float)SQUARE_SIZE };
        color = GREEN;
        active = false;
    }

    void Spawn(Vector2 offset) {
        active = true;
        position = {
            (float)(GetRandomValue(0, screenWidth / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.x / 2),
            (float)(GetRandomValue(0, screenHeight / SQUARE_SIZE - 1) * SQUARE_SIZE + offset.y / 2)
        };
    }
    void Draw() override {
        float radius = size.x / 2.0f;
        DrawCircleV({ position.x + radius, position.y + radius }, radius, color);
    }

};

class Game {
public:
    Player player;
    Food fruit;
    std::vector<Enemy*> enemies;
    std::vector<Trap> traps;
    Vector2 offset;
    int framesCounter;
    bool gameOver;
    int level;
    float speedFactor;

    /*Game() : player({ screenWidth / 2.0f, screenHeight / 2.0f }, { 0, 0 }), level(1) {
        Init();
    }*/
    Game() : player({ screenWidth / 2.0f, screenHeight / 2.0f }, { 0, 0 }), level(1) {
        Init();
    }


    void Init() {
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
            if (GetRandomValue(0, 1)) swap(spd.x, spd.y);
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

    void Update() {



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

    void Draw() {
        BeginDrawing();
        ClearBackground(GetBackgroundColor());

        if (!gameOver) {
            fruit.Draw();
            for (Trap& trap : traps) trap.Draw();
            for (Enemy* enemy : enemies) enemy->Draw();
            player.Draw();
            DrawLifeBar();  // Draw the vertical life bar on the left

            DrawText(TextFormat("Lives: %d", player.lives), 10, 10, 20, BLACK);
            DrawText(TextFormat("Score: %d", player.score), 10, 30, 20, DARKGREEN);
            DrawText(TextFormat("Level: %d", level), 10, 50, 20, BLUE);
        }
        else {
            DrawText("GAME OVER", screenWidth / 2 - 80, screenHeight / 2 - 20, 40, RED);
            DrawText("Press ENTER to Restart", screenWidth / 2 - 100, screenHeight / 2 + 30, 20, GRAY);
        }


        EndDrawing();
    }
    void DrawLifeBar() {
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


    Color GetBackgroundColor() {
        switch (level) {
        case 1: return LIGHTGRAY;
        case 2: return BEIGE;
        case 3: return SKYBLUE;
        case 4: return YELLOW;
        case 5: return GREEN;
        default: return LIGHTGRAY;
        }
    }
};

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