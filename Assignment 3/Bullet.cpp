#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <cmath>
#include "Bullet.h"

Bullet::Bullet(float startX, float startY, float angle) {
    image = al_load_bitmap("bullet.png");
    speed = 8.0f;
    x = startX;
    y = startY;
    dx = speed * cos(angle);
    dy = speed * sin(angle);
    isLive = true;
}

void Bullet::Update() {
    x += dx;
    y += dy;
}

void Bullet::Draw() {
    al_draw_bitmap(image, x, y, 0);
}

bool Bullet::isOffScreen(int screenWidth, int screenHeight) {
    return (x < 0 || x > screenWidth || y < 0 || y > screenHeight);
}
