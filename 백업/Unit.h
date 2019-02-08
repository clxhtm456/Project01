#include <Windows.h>
#include "World.h"
#include "options.h"
#pragma once

interface Unit
{
protected:
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
	int jumpcount;
	BOOL Land;
	BOOL Jump;
	double weight;
	int speedpenalt;
	HBITMAP effect[10], effectmask[10];
	HINSTANCE hInst;
	map* World;
	bool pow(Unit* U, int size);
	RECT collision;
public :
	
	Unit(HINSTANCE hinst, map* m)
	{
		lookdefault = true;
		hInst = hinst;
		state = 0;
		right = true;
		eacount = 0;
		eccount = 0;
		speedpenalt = 0;
		World = m;
		cruching = false;
		World->p[getxPos()][getyPos()] = this;
		xpost = 0;
		ypost = 0;
		block = false;
	}
	~Unit()
	{
		World->p[xpost][ypost] = NULL;
	}
	void init(HINSTANCE hinst, map*m);
	//////////set
	void increaseSeta(int goal);
	void setSeta(int goal);
	void setright(bool r);
	void setxPos(int x);
	void setyPos(int y);
	void setcruching(bool c);
	void setlookdefault(bool t);
	void setblock(bool t);
	////////get
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
	virtual int getBitxPos();
	virtual int getBityPos();
	virtual void rightmove(int speed);
	virtual void leftmove(int speed);
	virtual void jump();
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
	virtual void UpdateAnimation(HDC deshdc, HDC sourcehdc,int x,int y);
	virtual void UpdateBitmap();
	void collisionresize();
	RECT getcollision();
	void crouching();
	void looktop();
};