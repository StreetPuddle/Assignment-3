#pragma once
#include <vector>

struct Bullet {
    float x, y;
    float dx, dy;
};
class Cannon
{
public:
    Cannon(int W, int H);
    ~Cannon();
    void rotateLeft();
    void rotateRight();
    void Draw();
    void Update(int screenWidth, int screenHeight);
    void Fire();

private:
    int x, y;
    int boundx, boundy;
    float angle;
    ALLEGRO_BITMAP* image;
    ALLEGRO_BITMAP* bullet;
    std::vector<Bullet> bullets;
};