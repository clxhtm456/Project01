#include "resource1.h"
#include "Unit.h"

void Unit::init(HINSTANCE hinst, map* m)
{
	hInst = hinst;
	World = m;
}
	//////////set
void Unit::increaseSeta(int goal)
{
	/*if (seta < 0)
		seta += 360;*/
	int t = goal % 360;
	int t2 = t - 360;
	if (seta ==t)
		return;
	if (abs(t - seta) < abs(seta - t2))
	{
		if(seta > t)
			seta -= Unit_angle_speed;
		else
			seta += Unit_angle_speed;
	}else
	{
		if (seta > t2)
			seta -= Unit_angle_speed;
		else
			seta += Unit_angle_speed;
	}
}
void Unit::setSeta(int goal)
{
	seta = goal % 360;
}
	void Unit::setright(bool r)
	{
		right = r;
	}
	void Unit::setxPos(int x)
	{
		xPos = (double)x;
	}
	void Unit::setyPos(int y)
	{
		yPos = (double)y;
	}
	void Unit::setlookdefault(bool t)
	{
		lookdefault = t;
	}
	////////get
	double Unit::getSeta()
	{
		return (PI*seta)/180;
	}
	int Unit::getOSeta()
	{
		return seta;
	}
	bool Unit::getright()
	{
		return right;
	}
	BOOL Unit::getLand()
	{
		return Land;
	}

	int Unit::getxPos()
	{
		if (xPos >= 0)
			return (int)xPos;
		else
			return 0;
	}


	int Unit::getyPos()
	{
		if (yPos >= 0)
			return (int)yPos;
		else
			return 0;
	}
	double Unit::getdxPos()
	{
		return xPos;
	}


	double Unit::getdyPos()
	{
		return yPos;
	}
	int Unit::getBitxPos()
	{
		return (int)xPos;
	}
	int Unit::getBityPos()
	{
		return (int)yPos;
	}
	int Unit::getjumpcount()
	{
		return jumpcount;
	}
	int Unit::getDamage()
	{
		return DMG;
	}
	double Unit::getHP()
	{
		return HP;
	}
	void Unit::setblock(bool t)
	{
		block = t;
	}
	////////get
	bool Unit::getblock()
	{
		return block;
	}
	bool Unit::getlookdefault()
	{
		return lookdefault;
	}
	void Unit::UpdateAI()
	{
		if (HP > PlayerHPMAX)
			HP = PlayerHPMAX;

		//Áß·Â
		landing(weight, World);
		weight += gravity_speed;
		if (weight > gravity_max)
			weight = gravity_max;

		//¶¥¹Ù´Úlanding//
		Postrans();
	}

	bool Unit::pow(Unit* U, int size)
	{
		return (sqrt((U->getxPos() - xPos)*(U->getxPos() - xPos) + (U->getyPos() - yPos)*(U->getyPos() - yPos)) < size);
	}

	bool Unit::RectToUnit(RECT rt)
	{
		if (rt.left <= getxPos() && getxPos() <= rt.right &&rt.top <= getyPos() && getyPos() <= rt.bottom)
			return true;
		else
			return false;
	}

	bool Unit::RectToRect(RECT rt)
	{
		if (rt.left < collision.right && 
			collision.left < rt.right && 
			rt.top < collision.bottom && 
			collision.top < rt.bottom)
			return true;
		else
			return false;
	}

	////////Çàµ¿
	//¿À¸¥ÂÊ ¿ÞÂÊ Ç¥½Ã
	void Unit::turn()
	{
		if (right)
		{
			right = false;
			setSeta(180);
		}
		else
		{
			right = true;
			setSeta(0);
		}
	}
	//¶¥ ÂøÁö¿©ºÎ
	void Unit::Landing(BOOL l)
	{
		if (l)
		{
			jumpcount = max_jumpcount;
			if (getOSeta() > 180)
			{
				if (right)
					setSeta(0);
				else
					setSeta(180);
			}
		}

		Land = l;
	}

	void Unit::jump()
	{

		if (getjumpcount() > 0)
		{
			jumpcount--;
			weight = -jumppower;
		}

	}
	//¶¥ ÂøÁöÁß
	void Unit::landing(double gravity,map* m)
	{
		if (Land)
		{
			if (gravity >= 0)
				gravity = 0;
		}
		yPos += gravity;

		bool t = false;
		for (int j = 10; j <sizey; j++)
		{
			for (int i = -(sizex/2); i < sizex / 2; i++)
			{
				if (World->p[getxPos() + i][getyPos() + j] && World->p[getxPos() + i][getyPos() + j] != this
					&&World->p[getxPos() +i][getyPos() + j]->getblock() && RectToRect(World->p[getxPos() + i][getyPos() + j]->getcollision()))
				{
					weight = -(jumppower/2);
				}
				if (World->collision[int(getxPos())/5 + i][int(getyPos()) + j] != 0)
				{
					if (i < 4 && i > -4 && j < 16 && j > 10)
					{
						Landing(TRUE);
						t = true;
					}
				}
			}
		}
		if (t == false)
			Landing(FALSE);

	}

	void Unit::rightmove(int speed)
	{
		if (getLand()&& !getright())
		{
			turn();
		}

		if (getxPos() + speed < Unit_limit_right)
		{
			moving(speed);
		}
	}
	void Unit::leftmove(int speed)
	{
		if (getLand() && getright())
		{
			turn();
		}
		if (getxPos() - speed > Unit_limit_left)
		{
			moving(-1 * (speed));
		}
	}
	//¿òÁ÷ÀÌ±â
	void Unit::moving(double speed)
	{
		if (speed == 0)
			return;
		if (speed > 0)
		{
			for (int j = 0; j <sizex; j++)
			{
				for (int i = -80; i < 30; i++)
				{
					if (World->p[getxPos() + j][getyPos() + i] && World->p[getxPos() + j][getyPos() + i] != this
						&&World->p[getxPos() + j][getyPos() + i]->getblock() && RectToRect(World->p[getxPos() + j][getyPos() + i]->getcollision()))
					{
						return;
					}
					if (World->collision[int(getxPos())/5 + j][int(getyPos()) - i] != 0)
					{
						if (i < 3 && i > 0 && j < 11 && j > 1)
							return;
					}
				}
			}
			for (int i = 8; i < 16; i++)
			{
				for (int j = 1; j < 11; j++)
				{
					if (World->collision[int(getxPos())/5 + j][int(getyPos()) + i] != 0)
					{
						setyPos(getyPos() - (16 - i));
					}
				}
			}
		}
		else if (speed < 0)
		{
			for (int j = 0; j <sizex; j++)
			{
				for (int i = -80; i < 30; i++)
				{
					if (World->p[getxPos() - j][getyPos() + i]&& World->p[getxPos() - j][getyPos() + i] != this
						&&World->p[getxPos() - j][getyPos() + i]->getblock() && RectToRect(World->p[getxPos() - j][getyPos() + i]->getcollision()))
					{
						return;
					}
					if (World->collision[int(getxPos())/5 - j][int(getyPos()) - i] != 0)
					{
						if (i < 3 && i > 0 && j < 11 && j > 1)
							return;
					}
				}
			}
			for (int i = 8; i < 16; i++)
			{
				for (int j = 1; j < 11; j++)
				{
					if (World->collision[int(getxPos())/5 - j][int(getyPos()) + i] != 0)
					{
						setyPos(getyPos() - (16 - i));
					}
				}
			}
		}
		xPos += speed;
	}
	BOOL Unit::Die()
	{
		return TRUE;
	}
	void Unit::attack(Unit* U)
	{
		U->HP -= DMG;
		if (U->HP <= 0)
			U->Die();
	}
	//Å¸°ÝÀÌÆåÆ® target ÁöÁ¤½Ã ÀÛµ¿
	void Unit::EffectAnimation(HDC deshdc, HDC sourcehdc, int kind)
	{
		/*if (!target)
			return;
		switch (kind)
		{
		case 0:
			effect[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HIT1));
			effect[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HIT2));
			effect[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HIT3));
			effect[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HIT4));
			effectmask[0] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HMASK1));
			effectmask[1] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HMASK2));
			effectmask[2] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HMASK3));
			effectmask[3] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_HMASK4));
			break;
		}
		eccount++;
		if (eccount > 2)
		{
			eacount++;
			eccount = 0;
		}
		eacount = eacount % 4;
		SelectObject(sourcehdc, effectmask[eacount]);
		StretchBlt(deshdc, (int)target->xPos - 105, (int)target->yPos - 102, 211, 205, sourcehdc, 0, 0, 211, 205, SRCAND);
		SelectObject(sourcehdc, effect[eacount]);
		StretchBlt(deshdc, (int)target->xPos - 105, (int)target->yPos - 102, 211, 205, sourcehdc, 0, 0, 211, 205, SRCPAINT);
		for (int i = 0; i < 10; i++)
		{
			DeleteObject(effect[i]);
			DeleteObject(effectmask[i]);
		}
		if (eccount == 0 && eacount == 0)
		{
			target = NULL;
		}*/
	}
	void Unit::HPregen(int c)
	{
		if (HP + c > MaxHP)
			HP = MaxHP;
		else
			HP += c;
	}
	void Unit::UpdateAnimation(HDC deshdc, HDC sourcehdc, int x, int y)
	{
	}
	void Unit::UpdateBitmap()
	{

	}
	void Unit::Postrans()
	{
		/*for (int x = 0; x<mapMaxsizeX; x++)
		{
			for (int y = 0; y<mapMaxsizeY; y++)
			{
				World->p[x][y] = NULL;
			}
		}*/
		if (this->getxPos() != xpost || this->getyPos() != ypost)
		{
			World->p[xpost][ypost] = NULL;
			World->p[this->getxPos()][this->getyPos()] = this;
			xpost = this->getxPos();
			ypost = this->getyPos();
			if (sizex >0 || sizey > 0)
				collisionresize();
		}
	}
	void Unit::collisionresize()
	{
		collision.bottom = getyPos() + (sizey / 2);
			collision.top = getyPos() - (sizey / 2);
			collision.left = getxPos() - (sizex / 2);
			collision.right = getxPos() + (sizex / 2);
	}
	int Unit::getcolxPos()
	{
		return collision.right;
	}
	RECT Unit::getcollision()
	{
		return collision;
	}
	void Unit::crouching()
	{
		
		if (!Land)
		{
			lookdefault = false;
			increaseSeta(270);
		}
	}
	void Unit::looktop()
	{
		lookdefault = false;
		increaseSeta(90);
	}