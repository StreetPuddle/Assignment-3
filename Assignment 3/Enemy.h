#ifndef ENEMYH
#define ENEMYH
//#include "player.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	void DrawEnemy();
	void StartEnemy(int WIDTH, int HEIGHT);
	void UpdateEnemy();
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	int getX() { return x; }
	int getY() { return y; }
	bool getLive() { return live; }
	void setLive(bool l) { live = l; }
private:
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;
	static const char* EnemyFleet[5];

	ALLEGRO_BITMAP* image;
};
#endif
