#pragma once
class Cannon
{
public:
	Cannon(int W, int H);
	~Cannon();
	void DrawEnemy();
	void UpdateCannon();
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

	ALLEGRO_BITMAP* image;
};

