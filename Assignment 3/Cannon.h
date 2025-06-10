#pragma once
#include <vector>
#include "Enemy.h"

struct Bullet {
    float x, y;
    float dx, dy;
    bool live = true;
};
class Cannon
{
public:
    Cannon(int W, int H);
    ~Cannon();
    void rotateLeft();
    void rotateRight();
    void drawCannon();
    void updateCannon(int screenWidth, int screenHeight);
    void fireCannon();
    void killedEnemy(Enemy* enemies, int numEnemies);
    int getHits(){ return hits; }

private:
    int x, y;
    int bulletW, bulletH;
    int boundx, boundy;
    float angle;
    int hits;
    ALLEGRO_BITMAP* image;
    ALLEGRO_BITMAP* bullet;
    std::vector<Bullet> bullets;
};