#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Enemy.h"
#include "Player.h"

//Fleet of enemy ships that a game will utilize
const char* Enemy::EnemyFleet[5] = { "ENEMY1.png", "ENEMY2.png", "ENEMY3.png", "ENEMY4.png", "ENEMY5.png" };

//Enemy constructor
Enemy::Enemy()
{
	int i = rand() % 5;
	image = al_load_bitmap(EnemyFleet[i]);
	live = false;
	speed = (rand() % 3) + 2;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
}

//Enemy desconstructor
Enemy::~Enemy()
{
	al_destroy_bitmap(image);
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

//renders enemy ship
void Enemy::DrawEnemy()
{
	if (live) {
		al_draw_bitmap(image, x, y, 0);
	}
}

//updates enemies trajectpory and if collision with ship is detected, enemy dies and a life is removed
void Enemy::UpdateEnemy(Player* myPlayer)
{
	if (live)
	{
		y += speed;
		if (y + boundy >= myPlayer->getY())
		{
			live = false;
			myPlayer->removeLife();
		}
	}
}