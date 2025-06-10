#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "Cannon.h"
#include "Enemy.h"

//cannon constructor
Cannon::Cannon(int WIDTH, int HEIGHT)
{
	x = WIDTH / 2;
	y = HEIGHT - 175;
	angle = 0.0f;
	hits = 0;
	image = al_load_bitmap("CANNON.png");
	if (!image) {
		al_show_native_message_box(nullptr, "ERROR", "Cannon constructor", "Could not load bullet.png", nullptr, 0);
		exit(1);
	}
	bullet = al_load_bitmap("bullet.png");
	if (!bullet) {
		al_show_native_message_box(nullptr, "ERROR", "Cannon constructor", "Could not load bullet.png", nullptr, 0);
		exit(1);
	}
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	bulletW = al_get_bitmap_width(bullet);
	bulletH = al_get_bitmap_height(bullet);
}

//cannon deconstructor
Cannon::~Cannon()
{
	al_destroy_bitmap(bullet);
	al_destroy_bitmap(image);
}

//renders the cannon and bullets
void Cannon::drawCannon()
{
	for (Bullet& b : bullets) {//rendering bulelts
		if (b.live) {
			al_draw_bitmap(bullet, b.x - bulletW / 2, b.y - bulletH / 2, 0);
		}
	}

	float centerX = boundx / 2.0f;//rendering cannon
	float pivotY = boundy;
	al_draw_rotated_bitmap(image, centerX, pivotY, x, y, angle, 0);
}

//increases the angle of the canonon up to -60 degrees
void Cannon::rotateLeft() {
	angle -= 0.05f;
	if (angle < -ALLEGRO_PI / 3) {
		angle = -ALLEGRO_PI / 3;
		//printf("Angle: %d", angle);//testing
	}
}

//increases the angle of the canonon up to 60 degrees
void Cannon::rotateRight() {
	angle += 0.05f;
	if (angle > ALLEGRO_PI / 3) {
		angle = ALLEGRO_PI / 3;
	}
}

//updates bullets visual trajectory and detects when a bullets reaches the screen bounds
void Cannon::updateCannonShots(int screenWidth, int screenHeight)
{
	for (Bullet& b : bullets) {//loop to update each bullets location
		b.x += b.dirX;
		b.y += b.dirY;
	}
	for (int i = 0; i < bullets.size(); i++) {
		Bullet& b = bullets[i];
		if (b.x < 0 || b.x > screenWidth || b.y < 64 || b.y > screenHeight) {//removes bullet if out of bounds of screen
			bullets.erase(bullets.begin() + i);
		}
	}
}

//creates a bullet, to be shot from the tip of cannon in the desired direction
void Cannon::fireCannon()
{
	float bulletSpeed = 8.0f;
	float angleAdjusted = angle - ALLEGRO_PI / 2;
	float fireFromX = x + cos(angleAdjusted) * boundy;//tip of the cannon's x cord
	float fireFromY = y + sin(angleAdjusted) * boundy;//tip of cannon's y cord
	float dirX = cos(angleAdjusted) * bulletSpeed;//directional speed
	float dirY = sin(angleAdjusted) * bulletSpeed;

	Bullet newBullet = { fireFromX, fireFromY, dirX, dirY };
	bullets.push_back(newBullet);//appends bullet to be drawn
}

//diterates through each bullet to see if it is colliding with an enemy ship, if so destroys both
void Cannon::killedEnemy(Enemy* enemies, int numEnemies) {
	for (Bullet& b : bullets) {

		if (b.live) {
			for (int i = 0; i < numEnemies; i++) {

				if (enemies[i].getLive()) {

					if (!(b.x > enemies[i].getX() + enemies[i].getBoundX() || b.x + bulletW < enemies[i].getX() ||
						b.y > enemies[i].getY() + enemies[i].getBoundY() || b.y + bulletH < enemies[i].getY())) {//collision with enemy bounds

						b.live = false;//destroys bullet
						if (enemies[i].getSpecial()) {//increments hits(score keeper)
							hits += 5;
						}
						else {
							hits++;
						}
						enemies[i].setLive(false);//destroys enemy
						break;
					}
				}
			}
		}
	}
}