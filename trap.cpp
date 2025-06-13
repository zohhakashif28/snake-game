#include"trap.h"
#include "raylib.h"

Trap::Trap(Vector2 pos) {
    position = pos;
    size = { (float)SQUARE_SIZE, 4 };  // Thin horizontal line
    color = BLACK;
}

void Trap:: Draw()  {
    DrawRectangleV(position, size, color);
}

Rectangle Trap::GetRect() const  {
    return { position.x, position.y, size.x, size.y };
}