#pragma once
class Bullet {
public:
    Bullet(float startX, float startY, float angle);
    void Update();
    void Draw();
    bool isOffScreen(int screenWidth, int screenHeight);
    bool isLive;

private:
    float x, y;
    float dx, dy;
    float speed;
    ALLEGRO_BITMAP* image;
};

