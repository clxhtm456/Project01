#include "missile.h"
#include "options.h"
#pragma once

class Player : public Unit
{
private:
	
	int bcount;
	int state_0_timer;
	int statecount;
	int tstatecount;
	int tstate;
	int firecooltime;
	bool firecool;
	int weapontype;
	int bullet;
	int heavy_cool_time;
	int heavy_delay;
	//double deg = atan((y - master->getyPos()) / (x - master->getxPos()));
	HBITMAP standbit[9], standmask[9],top[9], topmask[9];
	HINSTANCE hInst;
	missile *b1[16];
public:
	Player(HINSTANCE hinst,map* m, int x, int y) : Unit(hinst,m) {
		hInst = hinst;
		weapontype = 0;
		DMG = player_dmg;
		firecooltime = 0;
		weight = 0;
		state = 0;
		tstate = 0;
		statecount = 6;
		tstatecount = 6;
		acount = 0;
		ccount = 0;
		bcount = 0;
		MaxHP = PlayerHPMAX;
		HP = PlayerHPMAX;
		xPos = x;
		yPos = y;
		UpdateBitmap();
	};
	~Player()
	{
		for (int i = 0; i < 10; i++)
		{
		DeleteObject(standmask[i]);
		DeleteObject(topmask[i]);
		DeleteObject(standbit[i]);
		DeleteObject(top[i]);
		delete b1[i];
		}
		World->p[xpost][ypost] = NULL;
	}
	////////set
	void setweapon(int type);
	void setbullet(int mount);
	void fireshot(int type,int delay = 0,int angle = 0);
	void setfirecool(int cool = 0);
	/////animation state
	void setstate(int i);
	void settstate(int i);
	void Landing(BOOL l);
	////x yÁÂÇ¥·Î ÁúÇ³Âü
	void setwindmove(int x, int y);
	void spell_fireball();
	//////////////get
	
	int getbullet();
	int getweapon();
	bool getfirecool();
	int getfirecooltime();
	int getstate();
	int gettstate();
	/////////±âÅ¸
	void UpdateAnimation(HDC deshdc, HDC sourcehdc, int x, int y);
	void UpdateBitmap();
	void rightmove(int speed);
	void leftmove(int speed);
	void jump();
	void UpdateAI();
	void attack(Unit* U);
	void UpdateMap();

};