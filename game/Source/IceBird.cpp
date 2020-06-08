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

namespace game_framework {

	//若在Character和Enemy中都有一個hp，選擇直接用Character中的那個

	IceBird::IceBird()
	{
		_x = 384;
		_y = 384;
		attack_damage = 0;
	}

	IceBird::IceBird(int x, int y, Hero *h) : Enemy(x, y, 1200, "IceBird", h, ICE)
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
		 boss_blood_bar.loadBloodBar();
		/////掉落道具
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->load();
		}
		/////怪物的動畫
		char *filename1_1[10] = { ".\\bitmaps\\icebirdL1.bmp",".\\bitmaps\\icebirdL2.bmp",".\\bitmaps\\icebirdL3.bmp", ".\\bitmaps\\icebirdL4.bmp",  ".\\bitmaps\\icebirdL5.bmp",  ".\\bitmaps\\icebirdL6.bmp",  ".\\bitmaps\\icebirdL7.bmp",  ".\\bitmaps\\icebirdL8.bmp",  ".\\bitmaps\\icebirdL9.bmp",  ".\\bitmaps\\icebirdL10.bmp" };
		for (int i = 0; i < 10; i++)	// 載入動畫(由6張圖形構成)
			walkingLeft.AddBitmap(filename1_1[i], RGB(0, 0, 0));
		walkingLeft.SetDelayCount(3);
		char *filename1_2[10] = { ".\\bitmaps\\icebirdR1.bmp",".\\bitmaps\\icebirdR2.bmp",".\\bitmaps\\icebirdR3.bmp", ".\\bitmaps\\icebirdR4.bmp",  ".\\bitmaps\\icebirdR5.bmp",  ".\\bitmaps\\icebirdR6.bmp",  ".\\bitmaps\\icebirdR7.bmp",  ".\\bitmaps\\icebirdR8.bmp",  ".\\bitmaps\\icebirdR9.bmp",  ".\\bitmaps\\icebirdR10.bmp" };
		for (int i = 0; i < 10; i++)	// 載入動畫(由6張圖形構成)
			walkingRight.AddBitmap(filename1_2[i], RGB(0, 0, 0));
		walkingRight.SetDelayCount(3);
		/////攻擊的動畫
		char *filename2_1[10] = { ".\\bitmaps\\icebirdL1.bmp",".\\bitmaps\\icebirdL2.bmp",".\\bitmaps\\icebirdL3.bmp", ".\\bitmaps\\icebirdL4.bmp",  ".\\bitmaps\\icebirdL5.bmp",  ".\\bitmaps\\icebirdL6.bmp",  ".\\bitmaps\\icebirdL7.bmp",  ".\\bitmaps\\icebirdL8.bmp",  ".\\bitmaps\\icebirdL9.bmp",  ".\\bitmaps\\icebirdL10.bmp" };
		for (int i = 0; i < 10; i++)	// 載入動畫(由6張圖形構成)
			normalAttackL.AddBitmap(filename2_1[i], RGB(0, 0, 0));
		normalAttackL.SetDelayCount(1);
		char *filename2_2[10] = { ".\\bitmaps\\icebirdR1.bmp",".\\bitmaps\\icebirdR2.bmp",".\\bitmaps\\icebirdR3.bmp", ".\\bitmaps\\icebirdR4.bmp",  ".\\bitmaps\\icebirdR5.bmp",  ".\\bitmaps\\icebirdR6.bmp",  ".\\bitmaps\\icebirdR7.bmp",  ".\\bitmaps\\icebirdR8.bmp",  ".\\bitmaps\\icebirdR9.bmp",  ".\\bitmaps\\icebirdR10.bmp" };
		for (int i = 0; i < 10; i++)	// 載入動畫(由6張圖形構成)
			normalAttackR.AddBitmap(filename2_2[i], RGB(0, 0, 0));
		normalAttackR.SetDelayCount(1);
		ice_attack.loadBitmap();
	}

	void IceBird::OnMove(Maps * m) {
		TRACE("---%d", distanceToHero());
		const int STEP_SIZE = 4;
		if (isAlive()) {
			//attack();
			attack_cool_down -= 1;
			//arrowAttackCD -= 1;
			walkingLeft.OnMove();
			walkingRight.OnMove();
			normalAttackL.OnMove();
			normalAttackR.OnMove();
			movement(m);
			iceAttack();
			iceAttackMove(m);
			if (arrowAttackCD != 0) {
				arrowAttackCD--;
			}
		}
		if (!isAlive()) {
			itemsOnMove(m);
		}
	}

	void IceBird::OnShow(Maps *m)
	{
		if (isAlive()) {
			if (_direction == 0)
			{
				if (isAttacking) {
					 boss_blood_bar.setXY(GetX1(), GetY1()-16);
					 boss_blood_bar.showBloodBar(m, hp - 16);
					iceAttackShow(m);
				}
				else {
					walkingLeft.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					walkingLeft.OnShow();
					 boss_blood_bar.setXY(GetX1(), GetY1()-16);
					 boss_blood_bar.showBloodBar(m, hp);
				}
				
			}
			else
			{
				if (isAttacking) {
					 boss_blood_bar.setXY(GetX1(), GetY1()-16);
					 boss_blood_bar.showBloodBar(m, hp);
					iceAttackShow(m);
				}
				else {
					
					 boss_blood_bar.setXY(GetX1(), GetY1()-16);
					 boss_blood_bar.showBloodBar(m, hp);
					walkingRight.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
					walkingRight.OnShow();
				}
				
			}
			
		}
		if (!isAlive()) {
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

	void IceBird::Initialize() {
		_x = ini_x;
		_y = ini_y;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttacking = attackIsFlying = false;
		hp = 1200;
		arrorClock = 0;
		arrowAttackCD = 180;
		 boss_blood_bar.setFullHP(hp);
		//walkingLeft.SetDelayCount(3);
		//walkingRight.SetDelayCount(3);
		///道具
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->Initialize();
		}
		ice_attack.setAttackName(ICE_BALL);
	}

	bool IceBird::intersect(int x1, int x2, int y1, int y2)
	{
		//下面有一些加減運算是因為，稻草人的Bitmap本身比稻草人的身體大太多。
		if (isAlive()) {
			if (x2 >= _x + 80  && x1 <= _x + walkingRight.Width() - 80 && y2 >= _y  && y1 <= _y + walkingRight.Height() ) {
				return true;
			}
			else {
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

	//bool Enemy::cannotPass(Hero * hero)
	//{
	//	// 檢測擦子所構成的矩形是否碰到球
	//	return (hero->GetX2() >= x && hero->GetX1() <= x+enemy.Width() && hero->GetY2() >= y && hero->GetY1() <= y + enemy.Height());
	//}
	////其實我不知道到底這個寫在map還是hero還是enemy好，但邏輯是她和hero不能重疊
	void IceBird::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void IceBird::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void IceBird::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void IceBird::SetMovingRight(bool b) {
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
		if (x > hero_on_map->GetX1()) {
			_direction = 0;
		}
		else if(x - 4 < hero_on_map->GetX1()){
			_direction = 1;
		}
		//int step_size = rand() % 3;
		/*if (x != hero_on_map->GetX1() && y != hero_on_map->GetY1()) {
			if (abs(x - hero_on_map->GetX1()) > abs(y - hero_on_map->GetY1()))
			{
				if (y > hero_on_map->GetY1())
					_y -= step_size;
				else
					_y += step_size;
			}
			else
			{
				if (x > hero_on_map->GetX1())
					_x -= step_size;
				else
					_x += step_size;
			}
		}*/
		int step_size = 3;
		if (distanceToHero() < 500 && distanceToHero() > 180) {
			if (hero_on_map->GetX1() > x && m->isEmpty(GetX2() + step_size, _y) && m->isEmpty(GetX2() + step_size, GetY2())) {
				_x += step_size;
			}
			if (hero_on_map->GetX1() < x && m->isEmpty(x - step_size, _y) && m->isEmpty(x - step_size, GetY2())) {
				_x -= step_size;
			}
			if (hero_on_map->GetY1() > y && m->isEmpty(x, GetY2() + step_size) && m->isEmpty(GetX2(), GetY2() + step_size)) {
				_y += step_size;
			}
			if (hero_on_map->GetY1() < y && m->isEmpty(x,_y - step_size) && m->isEmpty(GetX2(), _y - step_size)) {
				_y -= step_size;
			}
		}

		
		
	}




	CRect * IceBird::GetRect()
	{
		return &EnemyRect;
	}

	void IceBird::attack()
	{
		/*if (intersect(hero_on_map->GetX1(), hero_on_map->GetX2(), hero_on_map->GetY1(), hero_on_map->GetY2()) && attack_cool_down <= 0 && !isAttacking) {
			CAudio::Instance()->Play(AUDIO_HITTING);
			isAttacking = true;
			hero_on_map->offsetHp(attack_damage);
		}
		normalAttackR.OnMove();
		if (!isAttacking) {
			normalAttackR.Reset();
		}*/
	}

	void IceBird::attackShow(Maps * m)
	{
		if (isAttacking) {
			normalAttackR.SetTopLeft(m->screenX(_x), m->screenY(_y));
			normalAttackR.OnShow();
			if (normalAttackR.IsFinalBitmap()) {
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
			/*attackIsFlying = true;
			arr.setArrowXY(_x, _y);*/
			ice_attack.setXY(x, y);
			/*if (y == hero_on_map->GetY1() && hero_on_map->GetX1() <= x)
			{
				arrorClock = 60;
				ice_attack.setAttackIsFlying(true);
				ice_attack.setStepSize(-8, 0);
				isAttacking = true;
				arrowAttackCD = 180;
			}
			if (y == hero_on_map->GetY1() && hero_on_map->GetX1() > x)
			{
				arrorClock = 60;
				ice_attack.setAttackIsFlying(true);
				ice_attack.setStepSize(8, 0);
				isAttacking = true;
				arrowAttackCD = 180;
			}
			if (x == hero_on_map->GetX1() && hero_on_map->GetY1() <= y )
			{
				arrorClock = 60;
				ice_attack.setAttackIsFlying(true);
				ice_attack.setStepSize(0, -8);
				isAttacking = true;
				arrowAttackCD = 180;
			}
			if (x == hero_on_map->GetX1() && hero_on_map->GetY1() > y )
			{
				arrorClock = 60;
				ice_attack.setAttackIsFlying(true);
				ice_attack.setStepSize(0, 8);
				isAttacking = true;
				arrowAttackCD = 180;
			}*/
			if (distanceToHero() <= 180) {
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
		if (isAttacking) {
			if (hero_on_map->intercect(ice_attack.getX1(), ice_attack.getX2(), ice_attack.getY1(), ice_attack.getY2())) {
				hero_on_map->offsetHp(attack_damage);
			}
		}
		/*if (arrowAttackCD == 0)
		{
			if (hero_on_map->intercect(arr.getX1(), arr.getX2(), arr.getY1(), arr.getY2())) {
				hero_on_map->offsetHp(attack_damage);
			}
		}*/
		if (isAttacking && arrorClock != 0) {
			arrorClock--;
			if (arrorClock == 0) {
				isAttacking = false;
				ice_attack.setAttackIsFlying(false);
			}
		}
		ice_attack.OnMove(m);
		
		
	}

	void IceBird::iceAttackShow(Maps * m)
	{
		if (isAttacking) {
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

}
