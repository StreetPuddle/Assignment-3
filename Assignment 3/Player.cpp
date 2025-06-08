#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"


player::~player()
{
	al_destroy_bitmap(image);
}
player::player(int HEIGHT)
{
	image = al_load_bitmap("MainShip.png");
	x = 25;
	y = HEIGHT - 250;
	lives = 5;
	damageLvl = 0;//alligns with sprite array index
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	score = 0;
}
void player::DrawPlayer()
{
	al_draw_bitmap(image, x, y, 0);
}
void player::MoveLeft()
{
	//x -= speed;
	if (x < 0)
		x = 0;
}
void player::MoveRight()
{
	//x += speed;
	if (x > 300)
		x = 300;
}

//decrements lives, and sets sprite to next damaged sprite within the array
void player::removeLife() {
	lives--;
	damageLvl++;
	//al_destroy_bitmap(image);
	//image = al_load_bitmap(kirbs[damageLvl]);
}

//draws sprites at bottom of screen to represent lives left
void player::drawLives(ALLEGRO_FONT* font, int hits) {
	//ALLEGRO_BITMAP* tempImage = al_load_bitmap(kirbs[0]);
	int spaced = 20;
	for (int i = 0; i < lives; i++) {
		//al_draw_bitmap(tempImage, spaced, 400, 0);
		spaced += boundy + 10;
	}
	al_draw_textf(font, al_map_rgb(255, 255, 255), 320, 400, 0, "Enemies killed: %d", hits);
}