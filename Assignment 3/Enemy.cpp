#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Enemy.h"

//Enemy constructor
Enemy::Enemy()
{
	int i = rand() % 5;
	image = al_load_bitmap(EnemyFleet[i]);
	live = false;
	speed = 2;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
}

//Enemy desconstructor
Enemy::~Enemy()
{
	al_destroy_bitmap(image);
}

//renders enemy ship
void Enemy::DrawEnemy()
{
	al_draw_bitmap(image, x, y, 0);
}

//sets new enemy's random x
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

//updates enemies trajectpory and detects collition with ship
void Enemy::UpdateEnemy()
{
	if (live)
	{
		y += speed;
		if (y > 675)//contact with ship
		{
			live = false;
		}
	}

}

//Fleet of enemy ships that a game will utilize
const char* Enemy::EnemyFleet[5] = { "ENEMY1.png", "ENEMY2.png", "ENEMY3.png", "ENEMY4.png", "ENEMY5.png" };