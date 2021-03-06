#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include <ctgmath>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Hero.h"
#include "Maps.h"
#include "Enemy.h"
#include "BlueSlime.h"
#include "Util.h"
#include "Item.h"
#include "ItemAttribute.h"
namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// BlueGoblin: Enemy class												   //
	/////////////////////////////////////////////////////////////////////////////
	BlueSlime::BlueSlime()
	{
		_x = 384;
		_y = 384;
		attack_damage = 0;
	}
	BlueSlime::BlueSlime(int x, int y, Hero *h) : Enemy(x, y, 1200, "BlueSlime", h, ICE)
	{
		attack_damage = 70;
		attack_cool_down = 0;
		items.push_back(new ItemAttribute(_attribute));				//推給怪物存著他死掉會掉的掉落物
	}
	BlueSlime::~BlueSlime()
	{
	}
	void BlueSlime::LoadBitmap()
	{
		blood_bar.loadBloodBar();
		/////掉落道具
		for (unsigned i = 0; i < items.size(); i++) 
		{
			items.at(i)->load();
		}
		/////怪物的動畫
		char *filename1_1[3] = { ".\\bitmaps\\blueslimeL1.bmp",".\\bitmaps\\blueslimeL2.bmp",".\\bitmaps\\blueslimeL3.bmp" };
		for (int i = 0; i < 3; i++)	// 載入動畫
			walkingLeft.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		char *filename1_2[3] = { ".\\bitmaps\\blueslimeR1.bmp",".\\bitmaps\\blueslimeR2.bmp",".\\bitmaps\\blueslimeR3.bmp"};
		for (int i = 0; i < 3; i++)	// 載入動畫
			walkingRight.AddBitmap(filename1_2[i], RGB(0, 0, 0));
		/////攻擊的動畫
		char *filename2_1[5] = { ".\\bitmaps\\blueslime_attackL1.bmp",".\\bitmaps\\blueslime_attackL2.bmp",".\\bitmaps\\blueslime_attackL3.bmp", ".\\bitmaps\\blueslime_attackL4.bmp", ".\\bitmaps\\blueslime_attackL5.bmp" };
		for (int i = 0; i < 5; i++)	// 載入動畫
			normalAttackL.AddBitmap(filename2_1[i], RGB(0, 0, 0));
		normalAttackL.SetDelayCount(3);
		char *filename2_2[5] = { ".\\bitmaps\\blueslime_attackR1.bmp",".\\bitmaps\\blueslime_attackR2.bmp",".\\bitmaps\\blueslime_attackR3.bmp", ".\\bitmaps\\blueslime_attackR4.bmp", ".\\bitmaps\\blueslime_attackR5.bmp" };
		for (int i = 0; i < 5; i++)	// 載入動畫
			normalAttackR.AddBitmap(filename2_2[i], RGB(0, 0, 0));
		normalAttackR.SetDelayCount(3);
	}
	void BlueSlime::OnMove(Maps * m)
	{
		const int STEP_SIZE = 4;
		if (isAlive())
		{						//如果活著
			attack();							//看是否要攻擊
			attack_cool_down -= 1;				//每次onMove減少攻擊的冷卻時間
			walkingLeft.OnMove();
			walkingRight.OnMove();
			movement(m);						//角色移動方式
		}
		if (!isAlive()) 
		{
			itemsOnMove(m);						//如果死掉 掉落道具
		}
	}
	void BlueSlime::OnShow(Maps *m)
	{
		if (isAlive()) 
		{						//如果活著
			if (_direction == 0)				//如果向左
			{
				if (isAttacking) 
				{				//如果在攻擊 會顯示攻擊的動畫
					attackShow(m);
					blood_bar.setXY(GetX1(), GetY1());
					blood_bar.showBloodBar(m, hp);
				}
				else
				{							//如果不是在攻擊，顯示一般時候的動畫
					walkingLeft.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					walkingLeft.OnShow();
					blood_bar.setXY(GetX1(), GetY1());
					blood_bar.showBloodBar(m, hp);
				}
			}
			else
			{									//如果向右
				if (isAttacking)
				{
					attackShow(m);
					blood_bar.setXY(GetX1(), GetY1());
					blood_bar.showBloodBar(m, hp);
				}
				else 
				{
					walkingRight.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					walkingRight.OnShow();
					blood_bar.setXY(GetX1(), GetY1());
					blood_bar.showBloodBar(m, hp);
				}
			}
			
		}
		if (!isAlive())
		{						//如果死掉 顯示掉落道具
			itemsOnShow(m);
		}
	}
	int BlueSlime::GetX1()
	{
		return _x;
	}
	int BlueSlime::GetY1()
	{
		return _y;
	}
	int BlueSlime::GetX2()					//x2 = x座標加上寬度
	{
		return _x + walkingRight.Width();
	}
	int BlueSlime::GetY2()					//y2 - y座標加上高度
	{
		return _y + walkingRight.Height();
	}
	void BlueSlime::Initialize()		//初始化
	{
		_x = ini_x;
		_y = ini_y;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttacking =  false;
		hp = 1200;
		blood_bar.setFullHP(hp);
		walkingLeft.SetDelayCount(5);
		walkingRight.SetDelayCount(5);
		///道具
		for (unsigned i = 0; i < items.size(); i++)
		{
			items.at(i)->Initialize();
		}
	}
	bool BlueSlime::intersect(int x1, int x2, int y1, int y2)
	{
		//下面有一些加減運算是因為，Bitmap本身比身體大太多。
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
	void BlueSlime::SetMovingDown(bool b)
	{
		isMovingDown = b;
	}
	void BlueSlime::SetMovingUp(bool b) 
	{
		isMovingUp = b;
	}
	void BlueSlime::SetMovingLeft(bool b)
	{
		isMovingLeft = b;
	}
	void BlueSlime::SetMovingRight(bool b) 
	{
		isMovingRight = b;
	}
	void BlueSlime::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}
	void BlueSlime::movement(Maps *m)
	{
		int x = GetX1();
		int y1 = GetY1() ;	
		int step_size = rand() % 3;				//每次移動 1-3步
		if (distanceToHero() < 500) 
		{	//如果跟hero的距離<500才會開始動
			if (hero_on_map->GetX1() > x && m->isEmpty(GetX2() + step_size, y1) && m->isEmpty(GetX2() + step_size, GetY2())) {
				_direction = 1;					//如果英雄在右邊 向右走
				_x += step_size;
			}
			if (hero_on_map->GetX1() < x && m->isEmpty(x - step_size, y1) && m->isEmpty(x - step_size, GetY2())) {
				_direction = 0;					//如果英雄在左邊，向左走
				_x -= step_size;
			}
			if (hero_on_map->GetY1() > y1 && m->isEmpty(x, GetY2() + step_size) && m->isEmpty(GetX2(), GetY2() + step_size)) {
				_y += step_size;				//如果英雄在下面，向下走
			}
			if (hero_on_map->GetY1() < y1 && m->isEmpty(x, y1 - step_size) && m->isEmpty(GetX2(), y1 - step_size)) {
				_y -= step_size;				//如果英雄在上面，向下走
			}
		}
	}
	void BlueSlime::attack()		//如果英雄在攻擊範圍內，且攻擊冷卻時間已經到了，會攻擊
	{
		if (intersect(hero_on_map->GetX1(), hero_on_map->GetX2(), hero_on_map->GetY1(), hero_on_map->GetY2()) && attack_cool_down <= 0 && !isAttacking)
		{
			CAudio::Instance()->Play(AUDIO_HITTING);
			isAttacking = true;
			hero_on_map->offsetHp(attack_damage);			//英雄扣血
		}
		normalAttackR.OnMove();
		if (!isAttacking)
		{
			normalAttackR.Reset();
		}
	}
	void BlueSlime::attackShow(Maps * m)
	{
		if (isAttacking) 
		{//如果正在攻擊，顯示攻擊的動畫
			normalAttackR.SetTopLeft(m->screenX(_x), m->screenY(_y));
			normalAttackR.OnShow();
			if (normalAttackR.IsFinalBitmap())
			{
				isAttacking = false;
				attack_cool_down = 90; //每次攻擊間隔3秒
			}
		}
	}
}
