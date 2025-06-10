#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "Enemy.h"
#include "Player.h"

//Fleet of enemy ships that a game will utilize
const char* Enemy::EnemyFleet[5] = { "ENEMY1.png", "ENEMY2.png", "ENEMY3.png", "ENEMY4.png", "ENEMY5.png" };

//Enemy constructor
Enemy::Enemy()
{
	int i = rand() % 5;
	image = al_load_bitmap(EnemyFleet[i]);
	if (!image) {
		al_show_native_message_box(nullptr, "ERROR", "ALLEGRO ISSUE", "Could not load Enemy image", nullptr, 0);
		exit(1);
	}
	live = false;
	special = false;
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
void Enemy::startEnemy(int WIDTH, int HEIGHT)
{
	if (!live)
	{
		if (rand() % 500 == 0)
		{
			if ((float)rand() / RAND_MAX < 0.10f) {
				special = true;
			}
			live = true;
			x = rand() % (WIDTH - boundx);
			y = 64;

		}
	}
}

//renders enemy ship, 10% chance of being special and worth more!
void Enemy::drawEnemy()
{
	if (live) {
		if (special) {
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			special = true;
			al_draw_tinted_bitmap(image, al_map_rgba_f(r, g, b, 1), x, y, 0);
		}
		else {
			al_draw_bitmap(image, x, y, 0);
		}
	}
}

//updates enemies trajectpory and if collision with ship is detected, enemy dies and a life is removed
void Enemy::updateEnemy(Player* myPlayer)
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