#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "Player.h"

//ship images that reflect damage
const char* Player::shipDamage[7] = { "MainShip.png", "MainShip1.png", "MainShip2.png", "MainShip3.png", "MainShip4.png", "MainShip5.png", "MainShip6.png" };

//Player constructor
Player::Player(int HEIGHT)
{
	image = al_load_bitmap(shipDamage[damageLvl]);
	if (!image) {
		al_show_native_message_box(nullptr, "ERROR", "ALLEGRO ISSUE", "Could not load player png", nullptr, 0);
		exit(1);
	}
	heartsImage = al_load_bitmap("heart.png");
	if (!heartsImage) {
		al_show_native_message_box(nullptr, "ERROR", "ALLEGRO ISSUE", "Could not load hearts.png", nullptr, 0);
		exit(1);
	}
	x = 25;
	y = HEIGHT - 250;
	lives = 7;
	damageLvl = 0;//alligns with sprite array index
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
}

//Player deconstructor
Player::~Player()
{
	al_destroy_bitmap(image);
	al_destroy_bitmap(heartsImage);
	al_destroy_bitmap(dmgImage);
}

//renders main ship
void Player::drawPlayer()
{
	al_destroy_bitmap(image);
	image = al_load_bitmap(shipDamage[damageLvl]);
	if (!image) {
		al_show_native_message_box(nullptr, "ERROR", "Within drawPlayer", "Could not load player png", nullptr, 0);
		exit(-1);
	}
	al_draw_bitmap(image, x, y, 0);
}

//draws sprites at top of screen to represent lives left
void Player::drawHUD(ALLEGRO_FONT* font, int hits) {

	int spaced = 10;
	for (int i = 0; i < lives; i++) {
		al_draw_bitmap(heartsImage, spaced, 15, 0);
		spaced += al_get_bitmap_width(heartsImage) + 10;
	}
	al_draw_textf(font, al_map_rgb(255, 255, 255), 370, 15, 0, "Enemies killed: %d", hits);
}

//decrements lives, and sets sprite to next damaged sprite within the array
void Player::removeLife() {
	lives--;
	damageLvl++;
}