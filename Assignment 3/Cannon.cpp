#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Cannon.h"

//cannon deconstructor
Cannon::~Cannon()
{
	al_destroy_bitmap(bullet);
	al_destroy_bitmap(image);
}

//cannon constructor
Cannon::Cannon(int WIDTH, int HEIGHT)
{
	image = al_load_bitmap("CANNON.png");
	bullet = al_load_bitmap("bullet.png");
	x = WIDTH / 2;
	y = HEIGHT - 175;
	angle = 0.0f;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
}

//renders the cannon and bullets
void Cannon::Draw()
{
	for (Bullet& b : bullets) {//bulelts
		int bulletW = al_get_bitmap_width(bullet);
		int bulletH = al_get_bitmap_height(bullet);
		al_draw_bitmap(bullet, b.x - bulletW / 2, b.y - bulletH / 2, 0);
	}

	float centerX = boundx / 2.0f;//cannon
	float pivotY = boundy;
	al_draw_rotated_bitmap(image, centerX, pivotY, x, y, angle, 0);
}

//increases the angle of the canonon
void Cannon::rotateLeft() {
	angle -= 0.05f;
}

//increases the angle of the canonon
void Cannon::rotateRight() {
	angle += 0.05f;
}

//updates bullets visual trajectory and detects when a bullets reaches the screen bounds
void Cannon::Update(int screenWidth, int screenHeight)
{
	for (Bullet& b : bullets) {//loop to update each bullets location
		b.x += b.dx;
		b.y += b.dy;
	}

	for (int i = 0; i < bullets.size(); ) {
		Bullet& b = bullets[i];

		if (b.x < 0 || b.x > screenWidth || b.y < 0 || b.y > screenHeight) {//removes bullets at i if out of bounds of screen
			bullets.erase(bullets.begin() + i);
		}
		else {
			i++;
		}
	}
}

//Creates a bullet, to be shot from the tip of cannon in the desired direction
void Cannon::Fire()
{

	float angleAdjusted = angle - ALLEGRO_PI / 2;

	float tipX = x + cos(angleAdjusted) * boundy;//tip of the cannon's x cord
	float tipY = y + sin(angleAdjusted) * boundy;//tip of cannon's y cord

	float bulletSpeed = 8.0f;
	float dx = cos(angleAdjusted) * bulletSpeed;//directional speed
	float dy = sin(angleAdjusted) * bulletSpeed;

	Bullet newBullet = { tipX, tipY, dx, dy };
	bullets.push_back(newBullet);//appends bullet to be drawn
}