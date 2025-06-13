#include"gameobject.h"

GameObject::GameObject() {}
GameObject::GameObject(Vector2 pos, Vector2 sz, Color col) : position(pos), size(sz), color(col) {}

void GameObject:: Draw() {
    DrawRectangleV(position, size, color);
}

Rectangle GameObject::GetRect() const {
    return { position.x, position.y, size.x, size.y };
}