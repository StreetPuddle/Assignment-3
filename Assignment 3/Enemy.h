#ifndef ENEMYH
#define ENEMYH
#include "Player.h"

class Enemy
{
public:
	Enemy();
	~Enemy();
	void drawEnemy();
	void startEnemy(int WIDTH, int HEIGHT);
	void updateEnemy(Player* myPlayer);
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	int getX() { return x; }
	int getY() { return y; }
	bool getLive() { return live; }
	void setLive(bool l) { live = l; }
	bool getSpecial() { return special; }

private:
	int x;
	int y;
	bool live;
	bool special;
	int speed;
	int boundx;
	int boundy;
	static const char* EnemyFleet[5];
	ALLEGRO_BITMAP* image;
	
};
#endif
