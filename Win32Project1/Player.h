#include "missile.h"
#include "options.h"
#pragma once

class Player : public Unit
{
private:
	
	int bcount;
	int state_0_timer;
	int tstate_0_timer;

	int statecount;
	int tstatecount;
	int tstate;

	int firecooltime;
	int granadecooltime;
	bool firecool;
	bool granadecool;
	int weapontype;
	int hasgranade;
	int heavy_delay;
	HINSTANCE hInst;
	HBITMAP standbit[9], standmask[9],top[9], topmask[9];
	missile *b1[missile_count];
public:
	Player(HINSTANCE hinst,map* m,Camera* c, int x, int y, int fac = 0) : Unit(hinst,m, c,fac) {
		//생성자 상속시 애니메이션 출력안됨 이유는모르겟음
		hInst = hinst;
		weapontype = 0;
		DMG = player_dmg;
		firecooltime = 0;
		weight = 0;
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
		for (int i = 0; i < Unit_Max_Count; i++)
		{
			if (World->pUnit[i] == NULL)
			{
				World->pUnit[i] = this;
				break;
			}
		}
		
	};
	~Player()
	{
		for (int i = 0; i < 9; i++)
		{
		DeleteObject(standmask[i]);
		DeleteObject(topmask[i]);
		DeleteObject(standbit[i]);
		DeleteObject(top[i]);
		}
		for(int i = 0; i< missile_count;i++)
			delete b1[i];
		//World->p[xpost][ypost] = NULL;
	}
	////////set
	void setgranade(int t);
	void setweapon(int type);
	void fireshot(int type,int delay = 0,int angle = 0);
	void throw_granade();
	void setgranadecool(int cool = 0);
	void setfirecool(int cool = 0);
	/////animation state
	void setstate(int i);
	void settstate(int i);
	void Landing(BOOL l);
	////x y좌표로 질풍참
	void setwindmove(int x, int y);
	void fire_shot();
	//////////////get
	int getgranade();
	int getweapon();
	bool getgranadecool();
	bool getfirecool();
	int getgranadecooltime();
	int getfirecooltime();
	int getstate();
	int gettstate();
	/////////기타
	void UpdateAnimation(HDC deshdc, HDC sourcehdc, int x, int y);
	void UpdateBitmap();
	void rightmove(int speed);
	void leftmove(int speed);
	void jump();
	void UpdateAI();
	void attack(Unit* U);
	void UpdateMap();

};