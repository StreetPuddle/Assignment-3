#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Enemy.h"

Enemy::Enemy()
{
	int i = rand() % 5;
	image = al_load_bitmap(EnemyFleet[i]);
	live = false;
	speed = 4;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);


}
Enemy::~Enemy()
{
	al_destroy_bitmap(image);
}
void Enemy::DrawEnemy()
{
	al_draw_bitmap(image, x, y, 0);
}
void Enemy::StartEnemy(int WIDTH, int HEIGHT)
{
	if (!live)
	{
		if (rand() % 500 == 0)
		{
			live = true;
			x = rand() % (WIDTH - boundx);
			y = 0;

		}
	}
}
void Enemy::UpdateEnemy()
{

	if (live)
	{
		y += speed;
		if (y > 800) // assuming 800 is screen height
		{
			live = false; // deactivate when out of bounds
		}
	}

}
//void Enemy::CollideEnemy(){}
const char* Enemy::EnemyFleet[5] = { "ENEMY1.png", "ENEMY2.png", "ENEMY3.png", "ENEMY4.png", "ENEMY5.png" };