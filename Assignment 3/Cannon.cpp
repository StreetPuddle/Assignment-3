#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Cannon.h"
Cannon::~Cannon()
{
	al_destroy_bitmap(image);
}
Cannon::Cannon(int WIDTH, int HEIGHT)
{
	image = al_load_bitmap("CANNON.png");
	x = WIDTH / 2;
	y = HEIGHT - 250;
	//bulletSpeed = 7;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	score = 0;
}
void Cannon::DrawCannon()
{
	al_draw_bitmap(image, x, y, 0);
}