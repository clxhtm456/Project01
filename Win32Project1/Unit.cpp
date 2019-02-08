#include "resource1.h"
#include "Unit.h"

void Unit::init(HINSTANCE hinst, map* m)
{
	hInst = hinst;
	World = m;
}
void Unit::setstate(int i)
{

}
void Unit::settstate(int i)
{

}
void Unit::setfaction(int t)
{
	faction = t;
}
int Unit::getfaction()
{
	return faction;
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

	UpdateBitmap();
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
		if (abs(m_cam->getxPos() - this->getxPos()) > screensizeX/10)
			return;
		if (HP > PlayerHPMAX)
			HP = PlayerHPMAX;
		if (HP < 0)
		{
			setstate(setstate_dead);
		}

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
	void Unit::setbullet(int mount)
	{
		if (mount < 0)
			bullet = 0;
		else
			bullet = mount;
	}
	int Unit::getbullet()
	{
		return bullet;
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
		double grav = gravity;
		if (Land)
		{
			if (gravity >= 0)//¶¥¿¡ºÙ¾îÀÕ¾îµµ Á¡ÇÁ´Â °¡´É
				grav = 0;
		}
		

		
			for (int i = 0; i < Unit_Max_Count; i++)
			{
				if (World->pUnit[i] && World->pUnit[i] != this
					&&World->pUnit[i]->getblock() && RectToRect(World->pUnit[i]->getcollision()))
				{
					weight = -(jumppower/2);
				}
			}
		//for(int i = 0~À¯´ÖÃÑ°³¼ö)
		//{
		//	if(À¯´Ö[i]ÀÇ x yÁÂÇ¥¶û this ÀÇ x yÁÂÇ¥¸¦ ºñ±³ÇØ Ãæµ¹ÇÒ°æ¿ì)
		//	{
		//		weight = -(jumppower/2);
		//	}
		//}
		for (int i = 0; i <= grav; i++)
		{
			if (World->collision[(screensizeX / 2 - 5 * (m_cam->getxPos() - getxPos())) % screensizeX][screensizeY/2-5*((m_cam->getyPos() - (getyPos())+(i-1)))] != 0)
			{
				yPos += i;
				Landing(TRUE);
				return;
			}
		}
		/*if (yPos >= 80)
		{
			Landing(TRUE);
			return;
		}*/
		yPos += grav;
		Landing(FALSE);

	}

	void Unit::rightmove(int speed)
	{
		if (getLand()&& !getright())
		{
			turn();
		}

		if (getxPos() + speed < m_cam->getxPos() + screensizeX / 10)
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
		/*if (getxPos() - speed > m_cam->getxPos() - screensizeX / 10)
		{*/
			moving(-1 * (speed));
		//}
	}
	//¿òÁ÷ÀÌ±â
	void Unit::moving(double speed)
	{
		if (speed == 0)
			return;

		if (speed > 0)
		{
			
				for (int i = 0; i < Unit_Max_Count; i++)
				{
					if (World->pUnit[i] && World->pUnit[i] != this
						&&World->pUnit[i]->getblock() && RectToRect(World->pUnit[i]->getcollision()))
					{
						return;
					}
				}
			//for(int i = 0~À¯´ÖÃÑ°³¼ö)
			//{
			//	if(À¯´Ö[i]ÀÇ x yÁÂÇ¥¶û this ÀÇ x yÁÂÇ¥¸¦ ºñ±³ÇØ Ãæµ¹ÇÒ°æ¿ì)
			//	{
			//		return;
			//	}
			//}
			for (int i = sizey; i > 0; i--)
			{
				if (World->collision[(screensizeX / 2 - 5 * (m_cam->getxPos() - getxPos())+ 5*Player_speed)% screensizeX][screensizeY / 2 - 5 * ((m_cam->getyPos() - getyPos()))-5*(i-1)] != 0)
				{
					if (i < 10)
						setyPos(getyPos() - i);
					else
						return;
				}
			}
		}
		else if (speed < 0)
		{
			
			for (int i = 0; i < Unit_Max_Count; i++)
			{
				if (World->pUnit[i] && World->pUnit[i] != this
					&&World->pUnit[i]->getblock() && RectToRect(World->pUnit[i]->getcollision()))
				{
					return;
				}
			}
			for (int i = int(sizey); i > 0; i--)
			{
				if (World->collision[(screensizeX / 2 - 5 * (m_cam->getxPos() - getxPos() ) - 5*Player_speed) % screensizeX][screensizeY / 2 - 5 * ((m_cam->getyPos() - getyPos())) - 5 * (i - 1)] != 0)
				{
					if (i < 10)
						setyPos(getyPos() - i);
					else
						return;
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
		if (this->getxPos() != xpost || this->getyPos() != ypost)
		{
			xpost = this->getxPos();
			ypost = this->getyPos();
			if (sizex >0 || sizey > 0)
				collisionresize();
		}
	}
	void Unit::collisionresize()
	{
		collision.bottom = getyPos();
			collision.top = getyPos() - (sizey);
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
		if (!getLand())
		{
			setcruching(true);
			lookdefault = false;
			increaseSeta(270);
		}
	}
	void Unit::looktop()
	{
		lookdefault = false;
		increaseSeta(90);
		settopping(true);
	}

	void Unit::settopping(bool t)
	{
		toping = t;
	}
	////////get
	bool Unit::gettopping()
	{
		return toping;
	}
	void Unit::setcruching(bool t)
	{
		cruching = t;
	}
	bool Unit::getcruching()
	{
		return cruching;
	}
	bool Unit::getdead()
	{
		return dead;
	}
	void Unit::setdead(bool t)
	{
		dead = t;
	}
void Unit::Damagetaken(double damage)
{
	HP -= damage;
	if (HP <= 0)
		setstate(setstate_dead);
}