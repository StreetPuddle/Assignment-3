#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Player.h"

//Player constructor
Player::Player(int HEIGHT)
{
	image = al_load_bitmap(shipDamage[damageLvl]);
	heartsImage = al_load_bitmap("heart.png");
	x = 25;
	y = HEIGHT - 250;
	lives = 7;
	damageLvl = 0;//alligns with sprite array index
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	score = 0;
}

//Player deconstructor
Player::~Player()
{
	al_destroy_bitmap(image);
	al_destroy_bitmap(heartsImage);
	al_destroy_bitmap(dmgImage);
}

//renders main ship
void Player::DrawPlayer()
{
	al_destroy_bitmap(image);
	image = al_load_bitmap(shipDamage[damageLvl]);
	al_draw_bitmap(image, x, y, 0);
}



//draws sprites at bottom of screen to represent lives left
void Player::drawLives(ALLEGRO_FONT* font, int hits) {

	int spaced = 20;
	for (int i = 0; i < lives; i++) {
		al_draw_bitmap(heartsImage, spaced, 950, 0);
		spaced += al_get_bitmap_width(heartsImage) + 10;
	}
	al_draw_textf(font, al_map_rgb(255, 255, 255), 380, 960, 0, "Enemies killed: %d", hits);
}

//decrements lives, and sets sprite to next damaged sprite within the array
void Player::removeLife() {
	lives--;
	damageLvl++;
}

//ship images that reflect damage
const char* Player::shipDamage[7] = { "MainShip.png", "MainShip1.png", "MainShip2.png", "MainShip3.png", "MainShip4.png", "MainShip5.png", "MainShip6.png" };