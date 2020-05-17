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

namespace game_framework {

	//若在Character和Enemy中都有一個hp，選擇直接用Character中的那個

	ABoss::ABoss()
	{
		_x = 384;
		_y = 384;
		attack_damage = 0;
	}

	ABoss::ABoss(int x, int y, Hero *h) : Enemy(x, y, 4800, "ABoss", h, ICE)
	{
		attack_damage = 20;
		attack_cool_down = 0;
		items.push_back(new ItemAttribute(_attribute));
		status = WALKING;
		status_counter = 840;
		step_size = 2;
	}

	ABoss::~ABoss()
	{
	}

	void ABoss::LoadBitmap()
	{
		boss_blood_bar.loadBloodBar();
		/////掉落道具
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->load();
		}
		/////怪物走路的動畫
		char *filename1_1[4] = { ".\\bitmaps\\ABossL1.bmp",".\\bitmaps\\ABossL2.bmp",".\\bitmaps\\ABossL3.bmp",".\\bitmaps\\ABossL2.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			walkingLeft.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		char *filename1_2[4] = { ".\\bitmaps\\ABossR1.bmp",".\\bitmaps\\ABossR2.bmp",".\\bitmaps\\ABossR3.bmp",".\\bitmaps\\ABossR2.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由6張圖形構成)
			walkingRight.AddBitmap(filename1_2[i], RGB(0, 0, 0));
		
		/////攻擊的動畫
		char *filename2_1[2] = { ".\\bitmaps\\ABoss_attackL1.bmp",".\\bitmaps\\ABoss_attackL2.bmp"};
		for (int i = 0; i < 2; i++)	// 載入動畫(由6張圖形構成)
			normalAttackL.AddBitmap(filename2_1[i], RGB(0, 0, 0));
		normalAttackL.SetDelayCount(3);
		char *filename2_2[2] = { ".\\bitmaps\\ABoss_attackR1.bmp",".\\bitmaps\\ABoss_attackR2.bmp"};
		for (int i = 0; i < 2; i++)	// 載入動畫(由6張圖形構成)
			normalAttackR.AddBitmap(filename2_2[i], RGB(0, 0, 0));
		normalAttackR.SetDelayCount(3);
		
		/////準備攻擊的動畫
		char *filename3_1[3] = { ".\\bitmaps\\Aboss_PrepareAttackL1.bmp",".\\bitmaps\\Aboss_PrepareAttackL2.bmp",".\\bitmaps\\Aboss_PrepareAttackL2.bmp" };
		for (int i = 0; i < 3; i++)	// 載入動畫(由6張圖形構成)
			prepare_attackL.AddBitmap(filename3_1[i], RGB(0, 0, 0));
		prepare_attackL.SetDelayCount(3);
		char *filename3_2[3] = { ".\\bitmaps\\Aboss_PrepareAttackR1.bmp",".\\bitmaps\\Aboss_PrepareAttackR2.bmp",".\\bitmaps\\Aboss_PrepareAttackR3.bmp" };
		for (int i = 0; i < 3; i++)	// 載入動畫(由6張圖形構成)
			prepare_attackR.AddBitmap(filename3_2[i], RGB(0, 0, 0));
		prepare_attackR.SetDelayCount(3);
		
		/////回去走路的動畫
		char *filename4_1[3] = { ".\\bitmaps\\Aboss_PrepareAttackL3.bmp",".\\bitmaps\\Aboss_PrepareAttackL2.bmp",".\\bitmaps\\Aboss_PrepareAttackL1.bmp" };
		for (int i = 0; i < 3; i++)	// 載入動畫(由6張圖形構成)
			back_to_walkL.AddBitmap(filename4_1[i], RGB(0, 0, 0));
		back_to_walkL.SetDelayCount(3);
		char *filename4_2[3] = { ".\\bitmaps\\Aboss_PrepareAttackR3.bmp",".\\bitmaps\\Aboss_PrepareAttackR2.bmp",".\\bitmaps\\Aboss_PrepareAttackR1.bmp" };
		for (int i = 0; i < 3; i++)	// 載入動畫(由6張圖形構成)
			back_to_walkR.AddBitmap(filename4_2[i], RGB(0, 0, 0));
		back_to_walkR.SetDelayCount(3);
	}

	void ABoss::OnMove(Maps * m) {
		const int STEP_SIZE = 3;
		if (isAlive()) {
			attack();
			attack_cool_down -= 1;
			status_counter -= 1;
			movement(m);
		}
		if (!isAlive()) {
			itemsOnMove(m);
		}
	}

	void ABoss::OnShow(Maps *m)
	{
		//TRACE("-----------------------------%d %d %d \n", status_counter, status, _direction);
		if (isAlive()) {
			switch (status)
			{
			case WALKING:
			{
				if (_direction == 0)
				{
					walkingLeft.SetTopLeft(m->screenX(GetX1()+104), m->screenY(GetY1()+32));
					walkingLeft.OnShow();
					boss_blood_bar.setXY(GetX1(), GetY1());;
					boss_blood_bar.showBloodBar(m, hp);
				}
				if(_direction == 1)
				{
					walkingRight.SetTopLeft(m->screenX(GetX1()+104), m->screenY(GetY1()+32));
					walkingRight.OnShow();
					boss_blood_bar.setXY(GetX1(), GetY1());;
					boss_blood_bar.showBloodBar(m, hp);
				}
				break;
			}
			case PREPARE:
			{
				if (_direction == 0)
				{
					prepare_attackL.SetTopLeft(m->screenX(GetX1()+104), m->screenY(GetY1()+32));
					prepare_attackL.OnShow();
					boss_blood_bar.setXY(GetX1(), GetY1());;
					boss_blood_bar.showBloodBar(m, hp);
				}
				if(_direction == 1)
				{
					prepare_attackR.SetTopLeft(m->screenX(GetX1()+104), m->screenY(GetY1()+32));
					prepare_attackR.OnShow();
					boss_blood_bar.setXY(GetX1(), GetY1());
					boss_blood_bar.showBloodBar(m, hp);
				}
				break;
			}
			case ATTACK:
			{
				if (_direction == 0)
				{
					normalAttackL.SetTopLeft(m->screenX(GetX1()+104), m->screenY(GetY1()+32));
					normalAttackL.OnShow();
					boss_blood_bar.setXY(GetX1(), GetY1());;
					boss_blood_bar.showBloodBar(m, hp);
				}
				if(_direction == 1)
				{
					normalAttackR.SetTopLeft(m->screenX(GetX1()+104), m->screenY(GetY1()+32));
					normalAttackR.OnShow();
					boss_blood_bar.setXY(GetX1(), GetY1());;
					boss_blood_bar.showBloodBar(m, hp);
				}
				break;
			}
			case BACK_TO_WALK:
			{
				if (_direction == 0)
				{
					back_to_walkL.SetTopLeft(m->screenX(GetX1()+104), m->screenY(GetY1()+32));
					back_to_walkL.OnShow();
					boss_blood_bar.setXY(GetX1(), GetY1());;
					boss_blood_bar.showBloodBar(m, hp);
				}
				if (_direction == 1)
				{
					back_to_walkR.SetTopLeft(m->screenX(GetX1()+104), m->screenY(GetY1()+32));
					back_to_walkR.OnShow();
					boss_blood_bar.setXY(GetX1(), GetY1());;
					boss_blood_bar.showBloodBar(m, hp);
				}
				break;
			}
				break;
			}
			
			
		}
		if (!isAlive()) {
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

	void ABoss::Initialize() {
		_x = ini_x;
		_y = ini_y;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttacking =  false;
		hp = 2400;
		boss_blood_bar.setFullHP(hp);
		///道具
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->Initialize();
		}
	}

	bool ABoss::intersect(int x1, int x2, int y1, int y2)
	{
		//下面有一些加減運算是因為，稻草人的Bitmap本身比稻草人的身體大太多。
		if (isAlive()) {
			if (x2 >= _x + 64 && x1 <= _x + walkingRight.Width() - 64 && y2 >= _y + 64 && y1 <= _y + walkingRight.Height() - 15) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}

	//bool Enemy::cannotPass(Hero * hero)
	//{
	//	// 檢測擦子所構成的矩形是否碰到球
	//	return (hero->GetX2() >= x && hero->GetX1() <= x+enemy.Width() && hero->GetY2() >= y && hero->GetY1() <= y + enemy.Height());
	//}
	////其實我不知道到底這個寫在map還是hero還是enemy好，但邏輯是她和hero不能重疊
	void ABoss::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void ABoss::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void ABoss::SetMovingLeft(bool b) {
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
		int x = GetX1();
		int y = (GetY1() + GetY2()) / 2;
		if (distanceToHero() < 50000) {
			switch (status)
			{
			case WALKING:
			{step_size = 3;
			if (x <= hero_on_map->GetX1()) {
				_direction = 1;
			}
			else {
				_direction = 0;
			}
			walkingLeft.OnMove();
			walkingRight.OnMove();
			if (hero_on_map->GetX1() > x && m->isEmpty(GetX2() + step_size, y) && m->isEmpty(GetX2() + step_size, GetY2())) {
				_x += step_size;
			}
			if (hero_on_map->GetX1() < x && m->isEmpty(x - step_size, y) && m->isEmpty(x - step_size, GetY2())) {
				_x -= step_size;
			}
			if (hero_on_map->GetY1() > y && m->isEmpty(x, GetY2() + step_size) && m->isEmpty(GetX2(), GetY2() + step_size)) {
				_y += step_size;
			}
			if (hero_on_map->GetY1() < y && m->isEmpty(x, y - step_size) && m->isEmpty(GetX2(), y - step_size)) {
				_y -= step_size;
			}
			if (status_counter <= 540)
			{
				status = PREPARE;
			}
			break; }
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
			if (attack_target_location_x > x) {
				_direction = 1;
			}
			else {
				_direction = 0;
			}
			if (status_counter <= 200)
			{
				status = ATTACK;
			}
			break; }
			case ATTACK:
			{step_size = 15;
			normalAttackL.OnMove();
			normalAttackR.OnMove(); 
			if (attack_target_location_x > x && m->isEmpty(GetX2() + step_size, y) && m->isEmpty(GetX2() + step_size, GetY2())) {
				//_direction = 1;
				_x += step_size;
			}
			if (attack_target_location_x < x && m->isEmpty(x - step_size, y) && m->isEmpty(x - step_size, GetY2())) {
				//_direction = 0;
				_x -= step_size;
			}
			if (attack_target_location_y > y && m->isEmpty(x, GetY2() + step_size) && m->isEmpty(GetX2(), GetY2() + step_size)) {
				_y += step_size;
			}
			if (attack_target_location_y < y && m->isEmpty(x, y - step_size) && m->isEmpty(GetX2(), y - step_size)) {
				_y -= step_size;
			}
			if (status_counter <= 300 && status_counter > 200) {
				status = PREPARE;
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
			if (status_counter == 0)
			{
				status = WALKING;
				status_counter = 840;
			}
			break; }
		}
			/*if (hero_on_map->GetX1() > x && m->isEmpty(GetX2() + step_size, y) && m->isEmpty(GetX2() + step_size, GetY2())) {
				_direction = 1;
				_x += step_size;
			}
			if (hero_on_map->GetX1() < x && m->isEmpty(x - step_size, y) && m->isEmpty(x - step_size, GetY2())) {
				_direction = 0;
				_x -= step_size;
			}
			if (hero_on_map->GetY1() > y && m->isEmpty(x, GetY2() + step_size) && m->isEmpty(GetX2(), GetY2() + step_size)) {
				_y += step_size;
			}
			if (hero_on_map->GetY1() < y && m->isEmpty(x, y - step_size) && m->isEmpty(GetX2(), y - step_size)) {
				_y -= step_size;
			}*/
		}
		
		
	}




	CRect * ABoss::GetRect()
	{
		return &EnemyRect;
	}

	void ABoss::attack()
	{
		if (intersect(hero_on_map->GetX1(), hero_on_map->GetX2(), hero_on_map->GetY1(), hero_on_map->GetY2()) && attack_cool_down <= 0) {
			attack_cool_down = 40;
			hero_on_map->offsetHp(attack_damage);
		}
	}
}
