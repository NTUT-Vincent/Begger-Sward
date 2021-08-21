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
#include "ABoss.h"
#include "Util.h"
#include "Item.h"
#include "ItemAttribute.h"
#include "Attack.h"
namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// ABoss: Enemy class													   //
	/////////////////////////////////////////////////////////////////////////////
	ABoss::ABoss()
	{
		_x = 384;
		_y = 384;
		attack_damage = 0;
	}

	ABoss::ABoss(int x, int y, Hero *h) : Enemy(x, y, 80000, "ABoss", h, ICE)
	{
		attack_damage = 20;
		attack_cool_down = 0;
		items.push_back(new ItemAttribute(_attribute));		//死掉會掉的道具
		status = WALKING;									//一開始是在走路的狀態
		status_counter = 840;								//用來算是否要換status
		step_size = 2;
	}
	ABoss::~ABoss()
	{
	}
	void ABoss::LoadBitmap()
	{
		boss_blood_bar.loadBloodBar();
		/////掉落道具
		for (unsigned i = 0; i < items.size(); i++) 
		{
			items.at(i)->load();
		}
		/////怪物走路的動畫
		char *filename1_1[4] = { ".\\bitmaps\\ABossL1.bmp",".\\bitmaps\\ABossL2.bmp",".\\bitmaps\\ABossL3.bmp",".\\bitmaps\\ABossL2.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫
			walkingLeft.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		char *filename1_2[4] = { ".\\bitmaps\\ABossR1.bmp",".\\bitmaps\\ABossR2.bmp",".\\bitmaps\\ABossR3.bmp",".\\bitmaps\\ABossR2.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫
			walkingRight.AddBitmap(filename1_2[i], RGB(0, 0, 0));
		/////攻擊的動畫
		char *filename2_1[2] = { ".\\bitmaps\\ABoss_attackL1.bmp",".\\bitmaps\\ABoss_attackL2.bmp"};
		for (int i = 0; i < 2; i++)	// 載入動畫
			normalAttackL.AddBitmap(filename2_1[i], RGB(0, 0, 0));
		normalAttackL.SetDelayCount(3);
		char *filename2_2[2] = { ".\\bitmaps\\ABoss_attackR1.bmp",".\\bitmaps\\ABoss_attackR2.bmp"};
		for (int i = 0; i < 2; i++)	// 載入動畫
			normalAttackR.AddBitmap(filename2_2[i], RGB(0, 0, 0));
		normalAttackR.SetDelayCount(3);
		q_attack.loadBitmap();
		for (int i = 0; i < 18; i++) 
		{
			ice_attack[i].loadBitmap();
		}
		/////準備攻擊的動畫
		char *filename3_1[3] = { ".\\bitmaps\\Aboss_PrepareAttackL1.bmp",".\\bitmaps\\Aboss_PrepareAttackL2.bmp",".\\bitmaps\\Aboss_PrepareAttackL2.bmp" };
		for (int i = 0; i < 3; i++)	// 載入動畫
			prepare_attackL.AddBitmap(filename3_1[i], RGB(0, 0, 0));
		prepare_attackL.SetDelayCount(3);
		char *filename3_2[3] = { ".\\bitmaps\\Aboss_PrepareAttackR1.bmp",".\\bitmaps\\Aboss_PrepareAttackR2.bmp",".\\bitmaps\\Aboss_PrepareAttackR3.bmp" };
		for (int i = 0; i < 3; i++)	// 載入動畫
			prepare_attackR.AddBitmap(filename3_2[i], RGB(0, 0, 0));
		prepare_attackR.SetDelayCount(3);
		/////回去走路的動畫
		char *filename4_1[3] = { ".\\bitmaps\\Aboss_PrepareAttackL3.bmp",".\\bitmaps\\Aboss_PrepareAttackL2.bmp",".\\bitmaps\\Aboss_PrepareAttackL1.bmp" };
		for (int i = 0; i < 3; i++)	// 載入動畫
			back_to_walkL.AddBitmap(filename4_1[i], RGB(0, 0, 0));
		back_to_walkL.SetDelayCount(3);
		char *filename4_2[3] = { ".\\bitmaps\\Aboss_PrepareAttackR3.bmp",".\\bitmaps\\Aboss_PrepareAttackR2.bmp",".\\bitmaps\\Aboss_PrepareAttackR1.bmp" };
		for (int i = 0; i < 3; i++)	// 載入動畫
			back_to_walkR.AddBitmap(filename4_2[i], RGB(0, 0, 0));
		back_to_walkR.SetDelayCount(3);
	}
	void ABoss::OnMove(Maps * m) 
	{
		const int STEP_SIZE = 3;
		if (isAlive())
		{					
			attack();											//每次onMove都會檢查是否要攻擊			
			attack_cool_down -= 1;								//每次onMove都會-1
			status_counter -= 1;								//
			movement(m);
			iceAttackMove(m);
			if (status_counter == 390 || status_counter == 180)
			{
				iceAttack();									//在statuscouter在這兩個數字時會攻擊
			}
		}
		if (!isAlive()) 
		{
			CAudio::Instance()->Stop(AUDIO_ABOSS_PREPARE);		//如果死掉要停止這些聲音
			CAudio::Instance()->Stop(AUDIO_ABOSS_WALK);
			itemsOnMove(m);
		}
	}
	void ABoss::OnShow(Maps *m)
	{
		if (isAlive())
		{
			switch (status)			//switch，在不同狀態有不同的動畫
			{
			case WALKING:
			{
				if (_direction == 0) //如果向左
				{
					walkingLeft.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					walkingLeft.OnShow();
					boss_blood_bar.setXY(GetX1() - 100, GetY1() -32);;
					boss_blood_bar.showBloodBar(m, hp);
				}
				if(_direction == 1)	//如果像右
				{
					walkingRight.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					walkingRight.OnShow();
					boss_blood_bar.setXY(GetX1() - 100, GetY1() -32);;
					boss_blood_bar.showBloodBar(m, hp);
				}
				break;
			}
			case PREPARE:
			{
				if (_direction == 0)
				{
					prepare_attackL.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					prepare_attackL.OnShow();
					boss_blood_bar.setXY(GetX1() - 100, GetY1() -32);;
					boss_blood_bar.showBloodBar(m, hp);
				}
				if(_direction == 1)
				{
					prepare_attackR.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					prepare_attackR.OnShow();
					boss_blood_bar.setXY(GetX1() - 100, GetY1() - 32);
					boss_blood_bar.showBloodBar(m, hp);
				}
				break;
			}
			case ATTACK:
			{
				if (_direction == 0)
				{
					normalAttackL.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					normalAttackL.OnShow();
					boss_blood_bar.setXY(GetX1() - 100, GetY1() - 32);;
					boss_blood_bar.showBloodBar(m, hp);
				}
				if(_direction == 1)
				{
					normalAttackR.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					normalAttackR.OnShow();
					boss_blood_bar.setXY(GetX1() - 100, GetY1() - 32);;
					boss_blood_bar.showBloodBar(m, hp);
				}
				break;
			}
			case BACK_TO_WALK:
			{
				if (_direction == 0)
				{
					back_to_walkL.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					back_to_walkL.OnShow();
					boss_blood_bar.setXY(GetX1()- 100, GetY1() - 32);;
					boss_blood_bar.showBloodBar(m, hp);
				}
				if (_direction == 1)
				{
					back_to_walkR.SetTopLeft(m->screenX(GetX1() - 100), m->screenY(GetY1()));
					back_to_walkR.OnShow();
					boss_blood_bar.setXY(GetX1(), GetY1() - 32 );;
					boss_blood_bar.showBloodBar(m, hp);
				}
				break;
			}
				break;
			}
			iceAttackShow(m);
		}
		if (!isAlive()) 
		{
			itemsOnShow(m);
		}
	}
	int ABoss::GetX1()
	{
		return _x;
	}
	int ABoss::GetY1()
	{
		return _y;
	}
	int ABoss::GetX2()
	{
		return _x + walkingRight.Width();
	}
	int ABoss::GetY2()
	{
		return _y + walkingRight.Height();
	}
	void ABoss::Initialize() 
	{
		_x = ini_x;
		_y = ini_y;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttacking = isUsingQ = false;
		skillTimes = 0;
		hp = 8000;
		boss_blood_bar.setFullHP(hp);
		status = WALKING;
		status_counter = 840;
		///道具
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->Initialize();
		}
	}
	bool ABoss::intersect(int x1, int x2, int y1, int y2)
	{
		//下面有一些加減運算是因為，稻草人的Bitmap本身比稻草人的身體大太多。
		if (isAlive()) 
		{
			if (x2 >= GetX1()  && x1 <= GetX2() && y2 >= GetY1()  && y1 <= GetY2()) 
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
	void ABoss::SetMovingDown(bool b) 
	{
		isMovingDown = b;
	}
	void ABoss::SetMovingUp(bool b)
	{
		isMovingUp = b;
	}
	void ABoss::SetMovingLeft(bool b) 
	{
		isMovingLeft = b;
	}
	void ABoss::SetMovingRight(bool b) {
		isMovingRight = b;
	}
	void ABoss::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}
	void ABoss::movement(Maps *m)
	{
		int x = (GetX1()+ GetX2()) / 2;
		int y = (GetY1() + GetY2()) / 2;
		if (distanceToHero() < 50000) {
			switch (status)						//switch 在不同的狀態有不同的移動方式
			{
			case WALKING:
			{step_size = 3;
			if (x <= hero_on_map->GetX1())
			{
				_direction = 1;
			}
			else {
				_direction = 0;
			}
			walkingLeft.OnMove();
			walkingRight.OnMove();
			if (hero_on_map->GetX1() > x && m->isEmpty(GetX2() + step_size, _y) && m->isEmpty(GetX2() + step_size, GetY2()))
			{
				_x += step_size;
			}
			if (hero_on_map->GetX1() < x && m->isEmpty(_x - step_size, _y) && m->isEmpty(_x - step_size, GetY2()))
			{
				_x -= step_size;
			}
			if (hero_on_map->GetY1() > y && m->isEmpty(_x, GetY2() + step_size) && m->isEmpty(GetX2(), GetY2() + step_size))
			{
				_y += step_size;
			}
			if (hero_on_map->GetY1() < y && m->isEmpty(_x, _y - step_size) && m->isEmpty(GetX2(), _y - step_size)) 
			{
				_y -= step_size;
			}
			if (status_counter <= 540)
			{
				status = PREPARE;
				CAudio::Instance()->Stop(AUDIO_ABOSS_WALK);
				CAudio::Instance()->Play(AUDIO_ABOSS_PREPARE);
			}
			break;}
			case PREPARE:
			{step_size = 0;
			prepare_attackL.OnMove();
			prepare_attackR.OnMove();
			if (status_counter <= 420 && status_counter > 300)
			{
				status = ATTACK;
			}
			attack_target_location_x = x + (hero_on_map->GetX1() - x)*2;
			attack_target_location_y = y + ((hero_on_map->GetY1()) - y)*2;
			if (attack_target_location_x > x) 
			{
				_direction = 1;
			}
			else 
			{
				_direction = 0;
			}
			if (status_counter <= 200)
			{
				status = ATTACK;
			}
			break;}
			case ATTACK:
			{step_size = 15;
			attack_damage = 60;
			normalAttackL.OnMove();
			normalAttackR.OnMove(); 
			if (attack_target_location_x > x && m->isEmpty(GetX2() + step_size, _y) && m->isEmpty(GetX2() + step_size, GetY2()))
			{
				_x += step_size;
			}
			if (attack_target_location_x < x && m->isEmpty(_x - step_size, _y) && m->isEmpty(_x - step_size, GetY2())) 
			{
				_x -= step_size;
			}
			if (attack_target_location_y > y && m->isEmpty(_x, GetY2() + step_size) && m->isEmpty(GetX2(), GetY2() + step_size)) 
			{
				_y += step_size;
			}
			if (attack_target_location_y < y && m->isEmpty(_x, _y - step_size) && m->isEmpty(GetX2(), _y - step_size))
			{
				_y -= step_size;
			}
			if (status_counter <= 300 && status_counter > 200)
			{
				status = PREPARE;
				CAudio::Instance()->Play(AUDIO_ABOSS_PREPARE);
			}
			if (status_counter <= 120)
			{
				status = BACK_TO_WALK;
			}
			break; }
			case BACK_TO_WALK:
			{step_size = 0;
			back_to_walkL.OnMove();
			back_to_walkR.OnMove();
			attack_damage = 20;
			if (status_counter == 0)
			{
				status = WALKING;
				status_counter = 840;
				CAudio::Instance()->Play(AUDIO_ABOSS_WALK, true);
			}
			break;}
		}
		}
	}
	void ABoss::attack()
	{
		if (intersect(hero_on_map->GetX1(), hero_on_map->GetX2(), hero_on_map->GetY1(), hero_on_map->GetY2()) && attack_cool_down <= 0) 
		{
			attack_cool_down = 40;					//如果跟hero位置重疊就會攻擊 40/30秒會攻擊一次
			hero_on_map->offsetHp(attack_damage);	//英雄扣血
		}
	}
	void ABoss::iceAttack()		//開始ice attack的function
	{
		if (!isUsingQ)
		{
			isUsingQ = true;
			q_attack.setXY(_x + 100, _y + 100);
			for (int i = 0; i < 18; i++) 
			{
				ice_attack[i].setXY(_x + 100, _y + 100);
			}
			if (_attribute == FIRE)
			{
				CAudio::Instance()->Play(AUDIO_FIRE);
			}
			if (_attribute == ICE)
			{
				CAudio::Instance()->Play(AUDIO_ICE);
			}
			if (_attribute == PLANT)
			{
				CAudio::Instance()->Play(AUDIO_GRASSBALL);
			}
			q_attack.setAttackIsFlying(true);
			for (int i = 0; i < 18; i++) 
			{
				ice_attack[i].setAttackIsFlying(true);
				ice_attack[i].setStepSize((int)(sin(i * 20.0 * 3.14159 / 180.0) * 10), (int)(cos(i * 20 * 3.14159 / 180.0) * 10));
			}
		}
	}
	void ABoss::iceAttackMove(Maps *m) //call attack的onMove 並檢查是否有碰到hero
	{
		if (isUsingQ) 
		{
			q_attack.OnMove(m);
			for (int i = 0; i < 18; i++)
			{
				ice_attack[i].OnMove(m);
				if (hero_on_map->intercect(ice_attack[i].getX1(), ice_attack[i].getX2(), ice_attack[i].getY1(), ice_attack[i].getY2()))
				{
					hero_on_map->offsetHp(attack_damage);
				}
			}
		}
		q_attack.setAttackName(ICE_BALL);
		for (int i = 0; i < 18; i++)
		{
			ice_attack[i].setAttackName(ICE_BALL);
		}
		if (!isUsingQ)
		{
			q_attack.resetAnimation(ICE_BALL);
			for (int i = 0; i < 18; i++)
			{
				ice_attack[i].resetAnimation(ICE_BALL);
			}
		}
	}
	void ABoss::iceAttackShow(Maps * m)					//ice attack的onShow
	{
		if (isUsingQ)
		{
			q_attack.OnShow(m);
			for (int i = 0; i < 18; i++) 
			{
				ice_attack[i].OnShow(m);
			}
			skillTimes += 1;							//+1代表跑了1/30秒
			if (skillTimes > 80) 
			{						//預計讓他飛80/30秒
				isUsingQ = false;
				q_attack.setAttackIsFlying(false);
				for (int i = 0; i < 18; i++)
				{
					ice_attack[i].setAttackIsFlying(false);
				}
				skillTimes = 0;							//跑完整個技能把skillTime設回為0
			}
		}
	}
}
