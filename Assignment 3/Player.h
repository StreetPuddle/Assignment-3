#ifndef PLAYERH
#define PLAYERH

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
class player
{
public:
	player(int HEIGHT);
	~player();
	void DrawPlayer();
	void MoveUp();
	void MoveDown(int HEIGHT);
	void MoveLeft();
	void MoveRight();
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	int getX() { return x; }
	int getY() { return y; }
	int getLives() { return lives; }
	void removeLife();
	void drawLives(ALLEGRO_FONT* font, int hits);

private:
	int x;
	int y;
	int lives;
	int bulletSpeed;
	int boundx;
	int boundy;
	int score;
	int damageLvl;
	ALLEGRO_BITMAP* image;
};
#endif
