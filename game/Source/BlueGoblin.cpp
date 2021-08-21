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
#include "BlueGoblin.h"
#include "Util.h"
#include "Item.h"
#include "ItemAttribute.h"
namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// BlueGoblin: Enemy class												   //
	/////////////////////////////////////////////////////////////////////////////
	BlueGoblin::BlueGoblin()
	{
		_x = 384;
		_y = 384;
		attack_damage = 0;
	}
	BlueGoblin::BlueGoblin(int x, int y, Hero *h) : Enemy(x, y, 1200, "BlueGoblin", h, ICE)
	{
		attack_damage = 20;
		attack_cool_down = 0;
		items.push_back(new ItemAttribute(_attribute));
	}
	BlueGoblin::~BlueGoblin()
	{
	}
	void BlueGoblin::LoadBitmap()
	{
		blood_bar.loadBloodBar();
		/////掉落道具
		for (unsigned i = 0; i < items.size(); i++) 
		{
			items.at(i)->load();
		}
		/////怪物的動畫
		char *filename1_1[4] = { ".\\bitmaps\\bluegoblinL1.bmp",".\\bitmaps\\bluegoblinL2.bmp",".\\bitmaps\\bluegoblinL3.bmp", ".\\bitmaps\\bluegoblinL4.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫
			walkingLeft.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		char *filename1_2[4] = { ".\\bitmaps\\bluegoblinR1.bmp",".\\bitmaps\\bluegoblinR2.bmp",".\\bitmaps\\bluegoblinR3.bmp", ".\\bitmaps\\bluegoblinR4.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫
			walkingRight.AddBitmap(filename1_2[i], RGB(0, 0, 0));
		/////攻擊的動畫
		arrowAttackL.LoadBitmap(".\\bitmaps\\blue_arrow_attackL.bmp", RGB(0, 0, 0));
		arrowAttackR.LoadBitmap(".\\bitmaps\\blue_arrow_attackR.bmp", RGB(0, 0, 0));
		arr.loadBitmap();
	}
	void BlueGoblin::OnMove(Maps * m) 
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
	void BlueGoblin::OnShow(Maps *m)
	{
		if (isAlive())
		{									
			if (_direction == 0)					//向左的onShow
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
			{										//向右
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
	int BlueGoblin::GetX1()
	{
		return _x;
	}
	int BlueGoblin::GetY1()
	{
		return _y;
	}
	int BlueGoblin::GetX2()
	{
		return _x + walkingRight.Width();
	}
	int BlueGoblin::GetY2()
	{
		return _y + walkingRight.Height();
	}
	void BlueGoblin::Initialize() 
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
		///道具
		for (unsigned i = 0; i < items.size(); i++)
		{
			items.at(i)->Initialize();
		}
	}
	bool BlueGoblin::intersect(int x1, int x2, int y1, int y2)
	{
		//下面有一些加減運算是因為，Bitmap本身比身體大太多。
		if (isAlive()) 
		{
			if (x2 >= _x + 20 && x1 <= _x + walkingRight.Width() - 20 && y2 >= _y + 30 && y1 <= _y + walkingRight.Height() - 15) {
				return true;
			}
			else 
			{
				return false;
			}
		}
		return false;
	}
	void BlueGoblin::SetMovingDown(bool b) 
	{
		isMovingDown = b;
	}
	void BlueGoblin::SetMovingUp(bool b) 
	{
		isMovingUp = b;
	}
	void BlueGoblin::SetMovingLeft(bool b)
	{
		isMovingLeft = b;
	}
	void BlueGoblin::SetMovingRight(bool b)
	{
		isMovingRight = b;
	}
	void BlueGoblin::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}
	void BlueGoblin::movement(Maps *m)
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
	void BlueGoblin::attack()
	{
	}
	void BlueGoblin::attackShow(Maps * m)
	{
	}
	void BlueGoblin::arrowAttack()
	{
		if (!isAttacking && arrowAttackCD == 0)
		{
			if (_y == hero_on_map->GetY1() && hero_on_map->GetX1() <= _x)	//如果 y座標跟hero y座標一樣 英雄在左邊 射箭
			{
				arrorClock = 60;											//攻擊會飛兩秒
				arr.setAttackIsFlying(true);
				arr.setDirection(0);										//設定攻擊的方向 向左 因為英雄在左邊
				arr.setArrowXY(_x+32, _y+25);
				isAttacking = true;							
				arrowAttackCD = 180;										// 攻擊cd為6秒
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
	void BlueGoblin::arrowAttackMove(Maps * m)
	{
		if (isAttacking)
		{
			if (hero_on_map->intercect(arr.getX1(), arr.getX2(), arr.getY1(), arr.getY2())) {
				hero_on_map->offsetHp(attack_damage);
			}
		}
		if (isAttacking && arrorClock != 0) 
		{		//arrorClock每次onMove--
			arrorClock--;
			if (arrorClock == 0) {
				isAttacking = false;				//如果=0 isAttacking = false 離開攻擊狀態
			}
		}
	}
	void BlueGoblin::arrowAttackShow(Maps * m)
	{
		if (isAttacking)
		{
			if (_direction == 0)					//向左的時候
			{
				arrowAttackL.SetTopLeft(m->screenX(_x), m->screenY(_y));
				arrowAttackL.ShowBitmap();
				arr.OnShow(m);
			}
			if (_direction == 1)					//向左的時候
			{
				arrowAttackR.SetTopLeft(m->screenX(_x), m->screenY(_y));
				arrowAttackR.ShowBitmap();
				arr.OnShow(m);
			}
		}
	}
}
