
#include "Camera.h"
#include "World.h"
#include "options.h"
#pragma once

interface Unit
{
protected:
	int faction;
	bool block;
	bool lookdefault;
	int seta;
	int acount;
	int ccount;
	int eacount;
	int eccount;
	int state;
	int statecount;
	int sizex = 16;
	int sizey = 24;
	bool cruching;
	bool right;
	double xPos;
	double yPos;
	int xpost;
	int ypost;
	double MaxHP;
	double HP;
	double DMG;
	int bullet;
	int jumpcount;
	BOOL Land;
	BOOL Jump;
	bool toping;
	double weight;
	bool dead = false;
	int speedpenalt;
	HBITMAP effect[10], effectmask[10];
	HINSTANCE hInst;
	map* World;
	Camera* m_cam;
	bool pow(Unit* U, int size);
	RECT collision;
public :
	
	Unit(HINSTANCE hinst, map* m,Camera* c,int fac = 0)
	{
		faction = fac;
		lookdefault = true;
		hInst = hinst;
		state = 0;
		right = true;
		eacount = 0;
		eccount = 0;
		speedpenalt = 0;
		World = m;
		cruching = false;
		
		xpost = 0;
		ypost = 0;
		m_cam = c;
		block = false;
		dead = false;
	}
	~Unit()
	{
		for (int i = 0; i < Unit_Max_Count; i++)
		{
			if (World->pUnit[i] == this)
			{
				World->pUnit[i] = NULL;
				break;
			}
		}
	}
	void init(HINSTANCE hinst, map*m);
	//////////set
	void setfaction(int t);
	void setdead(bool t);
	void increaseSeta(int goal);
	void setSeta(int goal);
	void setright(bool r);
	void setxPos(int x);
	void setyPos(int y);
	void setcruching(bool c);
	void setlookdefault(bool t);
	void setblock(bool t);
	void settopping(bool t);
	void setbullet(int mount);
	int getbullet();
	////////get
	int getfaction();
	bool getdead();
	bool gettopping();
	bool getblock();
	bool getlookdefault();
	double getSeta();
	int getOSeta();
	bool getright();
	bool getcruching();
	BOOL getLand();
	int getxPos();
	int getyPos();
	int getcolxPos();
	double getdxPos();
	double getdyPos();
	virtual void setstate(int i);
	virtual void settstate(int i);
	virtual int getBitxPos();
	virtual int getBityPos();
	virtual void rightmove(int speed);
	virtual void leftmove(int speed);
	virtual void jump();
	virtual void UpdateAnimation(HDC deshdc, HDC sourcehdc, int x, int y);
	virtual void UpdateBitmap();
	virtual void Damagetaken(double damage);
	int getjumpcount();
	int getDamage();
	double getHP();
	double getMP();
	virtual void UpdateAI();
	void Postrans();
	bool RectToUnit(RECT rt);
	bool RectToRect(RECT rt);
	////////행동
	//오른쪽 왼쪽 표시
	void turn();
	//땅 착지여부
	virtual void Landing(BOOL l);
	//땅 착지중
	void landing(double gravity, map* m);
	//움직이기
	virtual void moving(double speed);
	BOOL Die();
	void attack(Unit* U);
	//타격이펙트 target 지정시 작동
	void EffectAnimation(HDC deshdc, HDC sourcehdc, int kind);
	void HPregen(int c);
	void MPregen(int c);
	
	void collisionresize();
	RECT getcollision();
	void crouching();
	void looktop();
};