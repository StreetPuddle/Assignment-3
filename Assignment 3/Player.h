#ifndef PLAYERH
#define PLAYERH

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Player
{
public:
	Player(int HEIGHT);
	~Player();
	void DrawPlayer();
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
	static const char* shipDamage[7];
	ALLEGRO_BITMAP* image;
	ALLEGRO_BITMAP* dmgImage;
	ALLEGRO_BITMAP* heartsImage;
};
#endif
