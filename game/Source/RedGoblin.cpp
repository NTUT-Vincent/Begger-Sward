#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include <ctgmath>
#include "audio.h"
#include "gamelib.h"
#include "Arrow.h"
#include "Enemy.h"
#include "Hero.h"
#include "Maps.h"
#include "Enemy.h"
#include "RedGoblin.h"
#include "Util.h"
#include "Item.h"
#include "ItemAttribute.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//註解請參照BlueGoblin.cpp 												   //
	/////////////////////////////////////////////////////////////////////////////
	RedGoblin::RedGoblin()
	{
		_x = 384;
		_y = 384;
		attack_damage = 0;
	}
	RedGoblin::RedGoblin(int x, int y, Hero *h) : Enemy(x, y, 1200, "RedGoblin", h, FIRE)
	{
		attack_damage = 20;
		attack_cool_down = 0;
		items.push_back(new ItemAttribute(_attribute));
	}
	RedGoblin::~RedGoblin()
	{
	}
	void RedGoblin::LoadBitmap()
	{
		blood_bar.loadBloodBar();
		for (unsigned i = 0; i < items.size(); i++)
		{
			items.at(i)->load();
		}
		char *filename1_1[4] = { ".\\bitmaps\\redgoblinL1.bmp",".\\bitmaps\\redgoblinL2.bmp",".\\bitmaps\\redgoblinL3.bmp", ".\\bitmaps\\redgoblinL4.bmp" };
		for (int i = 0; i < 4; i++)	
			walkingLeft.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		char *filename1_2[4] = { ".\\bitmaps\\redgoblinR1.bmp",".\\bitmaps\\redgoblinR2.bmp",".\\bitmaps\\redgoblinR3.bmp", ".\\bitmaps\\redgoblinR4.bmp" };
		for (int i = 0; i < 4; i++)
			walkingRight.AddBitmap(filename1_2[i], RGB(0, 0, 0));
		arrowAttackL.LoadBitmap(".\\bitmaps\\red_arrow_attackL.bmp", RGB(0, 0, 0));
		arrowAttackR.LoadBitmap(".\\bitmaps\\red_arrow_attackR.bmp", RGB(0, 0, 0));
		arr.loadBitmap();
	}
	void RedGoblin::OnMove(Maps * m) 
	{
		const int STEP_SIZE = 4;
		if (isAlive()) 
		{
			attack_cool_down -= 1;
			walkingLeft.OnMove();
			walkingRight.OnMove();
			movement(m);
			arrowAttack();
			arr.OnMove(m);
			arrowAttackMove(m);
			if (arrowAttackCD != 0) 
			{
				arrowAttackCD--;
			}
		}
		if (!isAlive()) 
		{
			itemsOnMove(m);
		}
	}
	void RedGoblin::OnShow(Maps *m)
	{
		if (isAlive()) 
		{
			if (_direction == 0)
			{
				if (isAttacking)
				{
					blood_bar.setXY(GetX1(), GetY1()-16);
					blood_bar.showBloodBar(m, hp - 16);
					arrowAttackShow(m);
				}
				else 
				{
					walkingLeft.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					walkingLeft.OnShow();
					blood_bar.setXY(GetX1(), GetY1()-16);
					blood_bar.showBloodBar(m, hp);
				}
			}
			else
			{
				if (isAttacking) 
				{
					blood_bar.setXY(GetX1(), GetY1()-16);
					blood_bar.showBloodBar(m, hp);
					arrowAttackShow(m);
				}
				else 
				{
					blood_bar.setXY(GetX1(), GetY1()-16);
					blood_bar.showBloodBar(m, hp);
					walkingRight.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					walkingRight.OnShow();
				}
			}
		}
		if (!isAlive()) 
		{
			itemsOnShow(m);
		}
	}
	int RedGoblin::GetX1()
	{
		return _x;
	}
	int RedGoblin::GetY1()
	{
		return _y;
	}
	int RedGoblin::GetX2()
	{
		return _x + walkingRight.Width();
	}
	int RedGoblin::GetY2()
	{
		return _y + walkingRight.Height();
	}
	void RedGoblin::Initialize() 
	{
		_x = ini_x;
		_y = ini_y;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttacking = attackIsFlying = false;
		hp = 1200;
		arrorClock = 0;
		arrowAttackCD = 0;
		blood_bar.setFullHP(hp);
		walkingLeft.SetDelayCount(5);
		walkingRight.SetDelayCount(5);
		for (unsigned i = 0; i < items.size(); i++) 
		{
			items.at(i)->Initialize();
		}
	}
	bool RedGoblin::intersect(int x1, int x2, int y1, int y2)
	{
		if (isAlive()) 
		{
			if (x2 >= _x + 20 && x1 <= _x + walkingRight.Width() - 20 && y2 >= _y + 30 && y1 <= _y + walkingRight.Height() - 15)
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
		return false;
	}
	void RedGoblin::SetMovingDown(bool b) 
	{
		isMovingDown = b;
	}
	void RedGoblin::SetMovingUp(bool b) 
	{
		isMovingUp = b;
	}
	void RedGoblin::SetMovingLeft(bool b) 
	{
		isMovingLeft = b;
	}
	void RedGoblin::SetMovingRight(bool b) 
	{
		isMovingRight = b;
	}
	void RedGoblin::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}
	void RedGoblin::movement(Maps *m)
	{
		int x = GetX1();
		int y1 = GetY1() ;
		if (_x > hero_on_map->GetX1()) 
		{
			_direction = 0;
		}
		else 
		{
			_direction = 1;
		}
		int step_size = rand() % 3;
		if (_x != hero_on_map->GetX1() && _y != hero_on_map->GetY1()) 
		{
			if (abs(_x - hero_on_map->GetX1()) > abs(_y - hero_on_map->GetY1()))
			{
				if (_y > hero_on_map->GetY1())
					_y -= step_size;
				else
					_y += step_size;
			}
			else
			{
				if (_x > hero_on_map->GetX1())
					_x -= step_size;
				else
					_x += step_size;
			}
		}
	}
	void RedGoblin::arrowAttack()
	{
		if (!isAttacking && arrowAttackCD == 0)
		{
			if (_y == hero_on_map->GetY1() && hero_on_map->GetX1() <= _x)
			{
				arrorClock = 60;
				arr.setAttackIsFlying(true);
				arr.setDirection(0);
				arr.setArrowXY(_x+32, _y+25);
				isAttacking = true;
				arrowAttackCD = 180;
			}
			if (_y == hero_on_map->GetY1() && hero_on_map->GetX1() > _x)
			{
				arrorClock = 60;
				arr.setAttackIsFlying(true);
				arr.setDirection(1);
				arr.setArrowXY(_x+32, _y+25);
				isAttacking = true;
				arrowAttackCD = 180;
			}
			if (_x == hero_on_map->GetX1() && hero_on_map->GetY1() <= _y )
			{
				arrorClock = 60;
				arr.setAttackIsFlying(true);
				arr.setDirection(2);
				arr.setArrowXY(_x+32, _y+25);
				isAttacking = true;
				arrowAttackCD = 180;
			}
			if (_x == hero_on_map->GetX1() && hero_on_map->GetY1() > _y )
			{
				arrorClock = 60;
				arr.setAttackIsFlying(true);
				arr.setDirection(3);
				arr.setArrowXY(_x+32, _y+25);
				isAttacking = true;
				arrowAttackCD = 180;
			}
		}
	}
	void RedGoblin::arrowAttackMove(Maps * m)
	{
		if (isAttacking) 
		{
			if (hero_on_map->intercect(arr.getX1(), arr.getX2(), arr.getY1(), arr.getY2())) 
			{
				hero_on_map->offsetHp(attack_damage);
			}
		}
		if (isAttacking && arrorClock != 0) 
		{
			arrorClock--;
			if (arrorClock == 0) 
			{
				isAttacking = false;
			}
		}
	}
	void RedGoblin::arrowAttackShow(Maps * m)
	{
		if (isAttacking) 
		{
			if (_direction == 0)
			{
				arrowAttackL.SetTopLeft(m->screenX(_x), m->screenY(_y));
				arrowAttackL.ShowBitmap();
				arr.OnShow(m);
			}
			if (_direction == 1)
			{
				arrowAttackR.SetTopLeft(m->screenX(_x), m->screenY(_y));
				arrowAttackR.ShowBitmap();
				arr.OnShow(m);
			}
		}
	}
}
