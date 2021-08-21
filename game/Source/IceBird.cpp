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
#include "IceBird.h"
#include "Util.h"
#include "Item.h"
#include "ItemAttribute.h"
namespace game_framework
{
	//若在Character和Enemy中都有一個hp，選擇直接用Character中的那個
	IceBird::IceBird()
	{
		_x = 384;
		_y = 384;
		attack_damage = 0;
	}
	IceBird::IceBird(int x, int y, Hero *h) : Enemy(x, y, 70000, "IceBird", h, ICE)
	{
		attack_damage = 20;
		attack_cool_down = 0;
		items.push_back(new ItemAttribute(_attribute));
	}
	IceBird::~IceBird()
	{
	}
	void IceBird::LoadBitmap()
	{
		icewallLeft.LoadBitmap(".\\bitmaps\\icewallL1.bmp", RGB(255, 255, 255));
		icewallRight.LoadBitmap(".\\bitmaps\\icewallR1.bmp", RGB(255, 255, 255));
		boss_blood_bar.loadBloodBar();
		/////掉落道具
		for (unsigned i = 0; i < items.size(); i++)
		{
			items.at(i)->load();
		}
		/////怪物的動畫
		char *filename1_1[10] = { ".\\bitmaps\\icebirdL1.bmp",".\\bitmaps\\icebirdL2.bmp",".\\bitmaps\\icebirdL3.bmp", ".\\bitmaps\\icebirdL4.bmp",  ".\\bitmaps\\icebirdL5.bmp",  ".\\bitmaps\\icebirdL6.bmp",  ".\\bitmaps\\icebirdL7.bmp",  ".\\bitmaps\\icebirdL8.bmp",  ".\\bitmaps\\icebirdL9.bmp",  ".\\bitmaps\\icebirdL10.bmp" };
		for (int i = 0; i < 10; i++)	// 載入動畫
			walkingLeft.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		walkingLeft.SetDelayCount(3);
		char *filename1_2[10] = { ".\\bitmaps\\icebirdR1.bmp",".\\bitmaps\\icebirdR2.bmp",".\\bitmaps\\icebirdR3.bmp", ".\\bitmaps\\icebirdR4.bmp",  ".\\bitmaps\\icebirdR5.bmp",  ".\\bitmaps\\icebirdR6.bmp",  ".\\bitmaps\\icebirdR7.bmp",  ".\\bitmaps\\icebirdR8.bmp",  ".\\bitmaps\\icebirdR9.bmp",  ".\\bitmaps\\icebirdR10.bmp" };
		for (int i = 0; i < 10; i++)	// 載入動畫
			walkingRight.AddBitmap(filename1_2[i], RGB(0, 0, 0));
		walkingRight.SetDelayCount(3);
		/////攻擊的動畫
		char *filename2_1[10] = { ".\\bitmaps\\icebirdL1.bmp",".\\bitmaps\\icebirdL2.bmp",".\\bitmaps\\icebirdL3.bmp", ".\\bitmaps\\icebirdL4.bmp",  ".\\bitmaps\\icebirdL5.bmp",  ".\\bitmaps\\icebirdL6.bmp",  ".\\bitmaps\\icebirdL7.bmp",  ".\\bitmaps\\icebirdL8.bmp",  ".\\bitmaps\\icebirdL9.bmp",  ".\\bitmaps\\icebirdL10.bmp" };
		for (int i = 0; i < 10; i++)	// 載入動畫
			normalAttackL.AddBitmap(filename2_1[i], RGB(0, 0, 0));
		normalAttackL.SetDelayCount(1);
		char *filename2_2[10] = { ".\\bitmaps\\icebirdR1.bmp",".\\bitmaps\\icebirdR2.bmp",".\\bitmaps\\icebirdR3.bmp", ".\\bitmaps\\icebirdR4.bmp",  ".\\bitmaps\\icebirdR5.bmp",  ".\\bitmaps\\icebirdR6.bmp",  ".\\bitmaps\\icebirdR7.bmp",  ".\\bitmaps\\icebirdR8.bmp",  ".\\bitmaps\\icebirdR9.bmp",  ".\\bitmaps\\icebirdR10.bmp" };
		for (int i = 0; i < 10; i++)	// 載入動畫
			normalAttackR.AddBitmap(filename2_2[i], RGB(0, 0, 0));
		normalAttackR.SetDelayCount(1);
		/////冰牆的動畫
		char *filename_wallL[8] = { ".\\bitmaps\\icewallL1.bmp",".\\bitmaps\\icewallL2.bmp",".\\bitmaps\\icewallL3.bmp",".\\bitmaps\\icewallL4.bmp",".\\bitmaps\\icewallL5.bmp",".\\bitmaps\\icewallL6.bmp",".\\bitmaps\\icewallL7.bmp",".\\bitmaps\\icewallL8.bmp", };
		for (int i = 0; i < 8; i++)	// 載入動畫
			icewallL.AddBitmap(filename_wallL[i], RGB(255, 255, 255));
		icewallL.SetDelayCount(5);
		char *filename_wallR[8] = { ".\\bitmaps\\icewallR1.bmp",".\\bitmaps\\icewallR2.bmp",".\\bitmaps\\icewallR3.bmp",".\\bitmaps\\icewallR4.bmp",".\\bitmaps\\icewallR5.bmp",".\\bitmaps\\icewallR6.bmp",".\\bitmaps\\icewallR7.bmp",".\\bitmaps\\icewallR8.bmp",};
		for (int i = 0; i < 8; i++)	// 載入動畫
			icewallR.AddBitmap(filename_wallR[i], RGB(255, 255, 255));
		icewallR.SetDelayCount(5);
		ice_attack.loadBitmap();
		////暴風雪的動畫
		char *filename_storm[6] = { ".\\bitmaps\\storm1.bmp",".\\bitmaps\\storm2.bmp",".\\bitmaps\\storm3.bmp",".\\bitmaps\\storm4.bmp",".\\bitmaps\\storm5.bmp",".\\bitmaps\\storm6.bmp"};
		for (int i = 0; i < 6; i++)	// 載入動畫
			storm.AddBitmap(filename_storm[i], RGB(255, 255, 255));
	}
	void IceBird::OnMove(Maps * m) 
	{
		const int STEP_SIZE = 4;
		if (isAlive())
		{
			attack_cool_down -= 1;
			walkingLeft.OnMove();
			walkingRight.OnMove();
			normalAttackL.OnMove();
			normalAttackR.OnMove();
			movement(m);
			iceAttack();
			iceAttackMove(m);
			iceWall(m);
			iceStorm(m);
			iceStormMove(m);
			if (arrowAttackCD != 0)
			{
				arrowAttackCD--;
			}
		}
		iceWallMove(m);
		if (!isAlive())
		{
			isUsingIceWall = false;
			//如果冰鳥死掉，過門時回頭主角對冰鳥開噴
			CAudio::Instance()->Play(AUDIO_ICEBIRD_DIE);
			itemsOnMove(m);
		}
	}
	void IceBird::OnShow(Maps *m)
	{
		if (isAlive()) 
		{
			iceStormShow(m);
			if (_direction == 0)
			{
				iceWallShow(m);
				if (isAttacking)
				{
					boss_blood_bar.setXY(GetX1(), GetY1()-16);
					boss_blood_bar.showBloodBar(m, hp - 16);
					iceAttackShow(m);
				}
				else
				{
					walkingLeft.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					walkingLeft.OnShow();
					boss_blood_bar.setXY(GetX1(), GetY1()-16);
					boss_blood_bar.showBloodBar(m, hp);
				}
			}
			else
			{
				iceWallShow(m);
				if (isAttacking) 
				{
					boss_blood_bar.setXY(GetX1(), GetY1()-16);
					boss_blood_bar.showBloodBar(m, hp);
					iceAttackShow(m);
				}
				else 
				{
					boss_blood_bar.setXY(GetX1(), GetY1()-16);
					boss_blood_bar.showBloodBar(m, hp);
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
	int IceBird::GetX1()
	{
		return _x;
	}
	int IceBird::GetY1()
	{
		return _y;
	}
	int IceBird::GetX2()
	{
		return _x + walkingRight.Width();
	}
	int IceBird::GetY2()
	{
		return _y + walkingRight.Height();
	}
	void IceBird::Initialize() 
	{
		_x = ini_x;
		_y = ini_y;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttacking = attackIsFlying = isUsingIceWall = isUsingStorm = false;
		hp = 70000;
		arrorClock = 0;
		arrowAttackCD = 180;
		ice_wall_clock = 0;
		ice_wall_cd = 180;
		storm_clock = 0;
		storm_cd = 240;
		 boss_blood_bar.setFullHP(hp);
		///道具
		for (unsigned i = 0; i < items.size(); i++) 
		{
			items.at(i)->Initialize();
		}
		ice_attack.setAttackName(ICE_BALL);
	}
	bool IceBird::intersect(int x1, int x2, int y1, int y2)
	{
		//下面有一些加減運算是因為，Bitmap本身比身體大太多。
		if (isAlive()) 
		{
			if (x2 >= _x + 80  && x1 <= _x + walkingRight.Width() - 80 && y2 >= _y  && y1 <= _y + walkingRight.Height() ) {
				return true;
			}
			else 
			{
				return false;
			}
		}
		return false;
	}
	int IceBird::distanceToHero()
	{
		int x = (GetX1() + GetX2()) / 2;
		int y = (GetY1() + GetY2()) / 2;
		int x_distance = x - hero_on_map->GetX1();
		int y_distance = y - hero_on_map->GetY1();
		return (int)(sqrt(pow(x_distance, 2) + pow(y_distance, 2)));
	}
	void IceBird::SetMovingDown(bool b) 
	{
		isMovingDown = b;
	}
	void IceBird::SetMovingUp(bool b) 
	{
		isMovingUp = b;
	}
	void IceBird::SetMovingLeft(bool b) 
	{
		isMovingLeft = b;
	}
	void IceBird::SetMovingRight(bool b)
	{
		isMovingRight = b;
	}
	void IceBird::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}
	void IceBird::movement(Maps *m)
	{
		int x = (GetX1() + GetX2())/2;
		int y = (GetY1() + GetY2())/2;
		if (x > hero_on_map->GetX1())
		{
			_direction = 0;
		}
		else if(x - 4 < hero_on_map->GetX1())
		{
			_direction = 1;
		}
		int step_size = 3;
		if (distanceToHero() < 500 && distanceToHero() > 180)
		{
			if (hero_on_map->GetX1() > x )
			{
				_x += step_size;
			}
			if (hero_on_map->GetX1() < x )
			{
				_x -= step_size;
			}
			if (hero_on_map->GetY1() > y )
			{
				_y += step_size;
			}
			if (hero_on_map->GetY1() < y )
			{
				_y -= step_size;
			}
		}
	}
	void IceBird::attack()
	{
	}
	void IceBird::attackShow(Maps * m)
	{
		if (isAttacking) 
		{
			normalAttackR.SetTopLeft(m->screenX(_x), m->screenY(_y));
			normalAttackR.OnShow();
			if (normalAttackR.IsFinalBitmap()) 
			{
				isAttacking = false;
				attack_cool_down = 90; //每次攻擊間隔3秒
			}
		}
	}
	void IceBird::iceAttack()
	{
		if (!isAttacking && arrowAttackCD == 0)
		{
			int x = (GetX1() + GetX2()) / 2;
			int y = (GetY1() + GetY2()) / 2;
			ice_attack.setXY(x, y);
			if (distanceToHero() <= 180) 
			{
				int x = (GetX1() + GetX2()) / 2;
				int y = (GetY1() + GetY2()) / 2;
				double x_distance =  hero_on_map->GetX1() - x;
				double y_distance =  hero_on_map->GetY1() - y;
				int ice_step_size_x = (int)(10 * x_distance / distanceToHero());
				int ice_step_size_y = (int)(10 * y_distance / distanceToHero());
				arrorClock = 60;
				ice_attack.setAttackIsFlying(true);
				ice_attack.setStepSize(ice_step_size_x, ice_step_size_y);
				isAttacking = true;
				arrowAttackCD = 180;
			}
		}
	}
	void IceBird::iceAttackMove(Maps * m)
	{
		if (isAttacking) 
		{
			if (hero_on_map->intercect(ice_attack.getX1(), ice_attack.getX2(), ice_attack.getY1(), ice_attack.getY2())) 
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
				ice_attack.setAttackIsFlying(false);
			}
		}
		ice_attack.OnMove(m);
	}
	void IceBird::iceAttackShow(Maps * m)
	{
		if (isAttacking)
		{
			if (_direction == 0)
			{
				normalAttackL.SetTopLeft(m->screenX(_x), m->screenY(_y));
				normalAttackL.OnShow();
				ice_attack.OnShow(m);
			}
			if (_direction == 1)
			{
				normalAttackR.SetTopLeft(m->screenX(_x), m->screenY(_y));
				normalAttackR.OnShow();;
				ice_attack.OnShow(m);
			}
		}
	}
	void IceBird::iceWall(Maps *m)
	{
		if (!isUsingIceWall &&ice_wall_cd == 0) 
		{
			icewall_direction = _direction;
			if (icewall_direction == 0)
			{
				ice_wall_x = ((hero_on_map->GetX1() - 36) / 64) * 64;
				ice_wall_y = ((_y-100) / 64) * 64;
				isUsingIceWall = true;
				ice_wall_clock = 180;
				for (int i = 0; i < 7; i++)
				{
					m->setIceWallPos(ice_wall_x, ice_wall_y + (64 * i), 1);
				}
			}
			if (icewall_direction == 1) 
			{
				ice_wall_x = ((hero_on_map->GetX1() + 100) / 64) * 64;
				ice_wall_y = ((_y - 100) / 64) * 64;
				isUsingIceWall = true;
				ice_wall_clock = 180;
				for (int i = 0; i < 7; i++)
				{
					m->setIceWallPos(ice_wall_x, ice_wall_y + (64 * i), 1);
				}
			}
		}
	}
	void IceBird::iceWallMove(Maps * m)
	{
		
		if (ice_wall_clock > 0 && isUsingIceWall) 
		{
			ice_wall_clock--;
			if (ice_wall_clock <= 40 && ice_wall_clock >=0 )
			{
				if (icewall_direction == 0 && !icewallL.IsFinalBitmap())
				{
					icewallL.OnMove();
				}
				if (icewall_direction == 1 && ! icewallR.IsFinalBitmap())
				{
					icewallR.OnMove();
				}
			}
			if (ice_wall_clock == 0)
			{
				isUsingIceWall = false;
				icewallL.Reset();
				icewallR.Reset();
				ice_wall_cd = 180;
			}
			if (!isAlive())
			{
				isUsingIceWall = false;
			}
			if (!isUsingIceWall)
			{
				for (int i = 0; i < 7; i++)
				{
					m->setIceWallPos(ice_wall_x, ice_wall_y + (64 * i), -1);
				}
			}
		}
		if (ice_wall_cd > 0) 
		{
			ice_wall_cd--;
		}
	}
	void IceBird::iceWallShow(Maps * m)
	{
		if (isUsingIceWall)
		{
			if (ice_wall_clock > 40 && ice_wall_clock <= 180)
			{
				if (icewall_direction == 0)
				{
					icewallLeft.SetTopLeft(m->screenX(ice_wall_x)-80, m->screenY(ice_wall_y));
					icewallLeft.ShowBitmap();
				}
				if (icewall_direction == 1)
				{
					icewallRight.SetTopLeft(m->screenX(ice_wall_x), m->screenY(ice_wall_y));
					icewallRight.ShowBitmap();
				}
			}
			if (ice_wall_clock <= 40 && ice_wall_clock >=0)
			{
				if (icewall_direction == 0)
				{
					icewallL.SetTopLeft(m->screenX(ice_wall_x)-80, m->screenY(ice_wall_y));
					icewallL.OnShow();
				}
				if(icewall_direction)
				{
					icewallR.SetTopLeft(m->screenX(ice_wall_x), m->screenY(ice_wall_y));
					icewallR.OnShow();
				}
			}
		}
	}
	void IceBird::iceStorm(Maps * m)
	{
		if (!isUsingStorm && storm_cd == 0)
		{	
			storm_x = hero_on_map->GetX1();
			storm_y = hero_on_map->GetY2();
			storm_x -= 120;
			storm_y -= 130;
			isUsingStorm = true;
			storm_clock = 120;
		}
	}
	void IceBird::iceStormMove(Maps * m)
	{
		if (storm_clock > 0)
		{
			storm_clock--;
			storm.OnMove();
			if (storm_clock == 0)
			{
				isUsingStorm = false;
				storm.Reset();
				storm_cd = 240;
			}
		}
		if (storm_cd > 0) 
		{
			storm_cd--;
		}
		if (isUsingStorm) 
		{
			if (intersectStorm(hero_on_map->GetX1(), hero_on_map->GetX2(), hero_on_map->GetY1(), hero_on_map->GetY2())) {
				if (hero_on_map->GetIsMovingLeft())
				{
					hero_on_map->addSX(2, m);
				}
				if (hero_on_map->GetIsMovingRight())
				{
					hero_on_map->addSX(-2, m);
				}
				if (hero_on_map->GetIsMovingUp())
				{
					hero_on_map->addSY(2, m);
				}
				if (hero_on_map->GetIsMovingDown())
				{
					hero_on_map->addSY(-2, m);
				}
				if (storm_clock % 5 == 1) 
				{
					hero_on_map->offsetHp(5);
				}
			}
		}
	}
	void IceBird::iceStormShow(Maps * m)
	{
		if (isUsingStorm) 
		{
			storm.SetTopLeft(m->screenX(storm_x), m->screenY(storm_y));
			storm.OnShow();
		}
	}
	bool IceBird::intersectStorm(int x1, int x2, int y1, int y2)
	{
		if (isUsingStorm) 
		{
			if (x2 >= storm_x + 50 && x1 <= storm_x + storm.Width() - 50 && y2 >= storm_y + 100 && y1 <= storm_y + storm.Height() - 100) {
				return true;
			}
			else 
			{
				return false;
			}
		}
		return false;
	}
}