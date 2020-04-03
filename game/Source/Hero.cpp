#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "CBall.h"
#include "Hero.h"
#include "Maps.h"
#include "BloodBar.h"
#include "Util.h"
#include "Attack.h"
#define HMS HERO_MOVE_SPEED


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Hero::Hero() : Character("Hero")
	{
		x = 480;
		y = 480;
		hp = 400;
		attack = 20;
		skillTimes = 0;
	}

	void Hero::LoadBitmap()
	{
		heroL.LoadBitmap(IDB_HERO_L, RGB(0, 0, 0));
		heroR.LoadBitmap(IDB_HERO_R, RGB(0, 0, 0));
		blood_bar.loadBloodBar();
		//向左走動畫
		char *filename1[6] = { ".\\bitmaps\\walkingL1.bmp",".\\bitmaps\\walkingL2.bmp",".\\bitmaps\\walkingL3.bmp",".\\bitmaps\\walkingL4.bmp", ".\\bitmaps\\walkingL3.bmp", ".\\bitmaps\\walkingL2.bmp" };
		for (int i = 0; i < 6; i++)	// 載入動畫(由6張圖形構成)
			walkingLeft.AddBitmap(filename1[i], RGB(0, 0, 0));
		//向右走動畫
		char *filename2[6] = { ".\\bitmaps\\walkingR1.bmp",".\\bitmaps\\walkingR2.bmp",".\\bitmaps\\walkingR3.bmp",".\\bitmaps\\walkingR4.bmp", ".\\bitmaps\\walkingR3.bmp", ".\\bitmaps\\walkingR2.bmp" };
		for (int i = 0; i < 6; i++)	// 載入動畫(由6張圖形構成)
			walkingRight.AddBitmap(filename2[i], RGB(0, 0, 0));
		RectHero = heroL.ReturnCRect();
		//E動畫
		char *filenameW[8] = { ".\\bitmaps\\Clock1.bmp",".\\bitmaps\\Clock2.bmp",".\\bitmaps\\Clock3.bmp",".\\bitmaps\\Clock4.bmp", ".\\bitmaps\\Clock5.bmp", ".\\bitmaps\\Clock6.bmp", ".\\bitmaps\\Clock7.bmp", ".\\bitmaps\\Clock8.bmp" };
		for (int i = 0; i < 6; i++)	// 載入動畫(由6張圖形構成)
			skillE.AddBitmap(filenameW[i], RGB(0, 0, 0));
		skillE.SetDelayCount(2);
		//普功動畫(左)
		normalAttackL.AddBitmap(IDB_COUNTER1, RGB(0, 0, 0));
		normalAttackL.AddBitmap(IDB_COUNTER2, RGB(0, 0, 0));
		normalAttackL.AddBitmap(IDB_COUNTER3, RGB(0, 0, 0));
		normalAttackL.SetDelayCount(5);
		//普功動畫(右)
		normalAttackR.AddBitmap(IDB_CLOCK1, RGB(0, 0, 0));
		normalAttackR.AddBitmap(IDB_CLOCK2, RGB(0, 0, 0));
		normalAttackR.AddBitmap(IDB_CLOCK3, RGB(0, 0, 0));
		normalAttackR.SetDelayCount(5);
		//Q
		fire_attack.loadBitmap();
	}

	void Hero::OnMove(Maps * m, vector<Enemy*> * enemys) {
		if (isMovingLeft && m->isEmpty(x - HMS, y))
		{
			if (gonnaBleeding(enemys, GetX1(), GetX2(), GetY1(), GetY2()))
			{
				hp -= 10;
			}
			m->addSX(HMS);
			x -= HMS;
		}

		if (isMovingRight && m->isEmpty(x + HMS, y))
		{
			if (gonnaBleeding(enemys, GetX1(), GetX2(), GetY1(), GetY2()))
			{
				hp -= 10;
			}
			m->addSX(-HMS);
			x += HMS;
		}
		if (isMovingUp && m->isEmpty(x, y - HMS))
		{
			if (gonnaBleeding(enemys, GetX1(), GetX2(), GetY1(), GetY2()))
			{
				hp -= 10;
			}
			m->addSY(HMS);
			y -= HMS;
		}

		if (isMovingDown && m->isEmpty(x, y + HMS))
		{
			if (gonnaBleeding(enemys, GetX1(), GetX2(), GetY1(), GetY2()))
			{
				hp -= 10;
			}
			m->addSY(-HMS);
			y += HMS;
		}

		m->getHeroX(x);
		m->getHeroY(y);
		walkingLeft.OnMove();
		walkingRight.OnMove();
		skillEMove();
		skillQMove(m);
		normalAttackMove();

	}

	void Hero::OnShow(Maps *m)
	{
		blood_bar.setXY(x - 10, y - 10);
		blood_bar.showBloodBar(m, hp);
		if (UsingSkillBitmap()) {
			normalAttackShow();
			skillEShow();
		}
		else {
			skillQShow(m);
			if (directionLR == 0)
			{
				if (isMoving()) {
					walkingLeft.SetTopLeft(280, 280);
					walkingLeft.OnShow();
				}
				else {
					heroL.SetTopLeft(280, 280);
					heroL.ShowBitmap();
				}

			}
			else
			{
				if (isMoving()) {
					walkingRight.SetTopLeft(280, 280);
					walkingRight.OnShow();
				}
				else {
					heroR.SetTopLeft(280, 280);
					heroR.ShowBitmap();
				}

			}
		}

	}

	int Hero::GetX1() {
		return x;
	}

	int Hero::GetY1() {
		return y;
	}

	int Hero::GetX2()
	{
		return x + heroR.Width();
	}

	int Hero::GetY2()
	{
		return y + heroR.Height();
	}

	void Hero::Initialize() {
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttack = false;
		isUsingA = isUsingQ = isUsingW = isUsingE = isUsingR = false;
		blood_bar.setFullHP(hp);
		walkingLeft.SetDelayCount(5);
		walkingRight.SetDelayCount(5);
	}

	void Hero::SetMovingDown(bool b) {
		isMovingDown = b;
		directionUD = 1;
	}

	void Hero::SetMovingUp(bool b) {
		isMovingUp = b;
		directionUD = 0;
	}

	void Hero::SetMovingLeft(bool b) {
		isMovingLeft = b;
		directionLR = 0;
	}

	void Hero::SetMovingRight(bool b) {
		isMovingRight = b;
		directionLR = 1;
	}
	void Hero::SetUsingA(bool b)
	{
		isUsingA = b;
	}
	void Hero::SetUsingQ(bool b)
	{
		isUsingQ = b;
	}
	void Hero::SetUsingW(bool b)
	{
		isUsingW = b;
	}
	void Hero::SetUsingE(bool b)
	{
		isUsingE = b;
	}
	void Hero::SetUsingR(bool b)
	{
		isUsingR = b;
	}

	bool Hero::gonnaBleeding(vector<Enemy*> * enemys, int x1, int x2, int y1, int y2)
	{
		for (unsigned i = 0; i < enemys->size(); i++)
		{
			if (enemys->at(i)->heroExistingArea(x1, x2, y1, y2))
			{
				return true;
			}
			if (enemys->at(i)->heroExistingArea(x1 - 64, x2 - 64, y1, y2) && directionLR == 0 && isUsingA == 1)
			{
				enemys->at(i)->offsetHP(-200);
			}
			if (enemys->at(i)->heroExistingArea(x1 + 64, x2 + 64, y1, y2) && directionLR == 1 && isUsingA == 1)
			{
				enemys->at(i)->offsetHP(-200);
			}
			if (enemys->at(i)->heroExistingArea(x1 - 64, x2 + 64, y1 - 64, y2 + 64) && directionLR == 0 && isUsingE == 1)
			{
				enemys->at(i)->offsetHP(-200);
			}
			if (enemys->at(i)->heroExistingArea(x1 - 64, x2 + 64, y1 - 64, y2 + 64) && directionLR == 1 && isUsingE == 1)
			{
				enemys->at(i)->offsetHP(-200);
			}
		}
		return false;
	}

	bool Hero::isMoving()
	{
		if (isMovingDown || isMovingLeft || isMovingRight || isMovingUp) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Hero::UsingSkillBitmap()
	{
		if (isUsingA || isUsingW || isUsingE || isUsingR) {
			return true;
		}
		return false;
	}

	void Hero::skillEMove()
	{
		skillE.OnMove();
		if (!isUsingE)
			skillE.Reset();
	}

	void Hero::skillEShow()
	{
		if (isUsingE) {
			skillE.SetTopLeft(280 - 25, 280 - 15);
			skillE.OnShow();
			if (skillE.IsFinalBitmap()) {
				skillTimes += 1;			//+1代表跑了一回CAnimation
				if (skillTimes == 3) {
					skillTimes = 0;			//跑完整個技能把skillTime設回為0
					isUsingE = false;
				}
			}
		}
	}

	void Hero::normalAttackMove()
	{
		normalAttackL.OnMove();
		normalAttackR.OnMove();
		if (!isUsingA) {
			normalAttackL.Reset();			//沒有用技能的時候 要Reset CAnimation，下次才會從第一張圖跑
			normalAttackR.Reset();
		}
	}

	void Hero::normalAttackShow()
	{
		if (directionLR == 0 && isUsingA) {
			normalAttackL.SetTopLeft(280 - 20, 280 - 10);
			normalAttackL.OnShow();
			if (normalAttackL.IsFinalBitmap()) {
				isUsingA = false;
			}
		}
		if (directionLR == 1 && isUsingA) {
			normalAttackR.SetTopLeft(280 - 20, 280 - 10);
			normalAttackR.OnShow();
			if (normalAttackR.IsFinalBitmap()) {
				isUsingA = false;
			}
		}
	}

	void Hero::skillQ()
	{
		fire_attack.setXY(x, y);
		fire_attack.setFireIsFlying(true);
		if (directionLR == 0) {
			fire_attack.setDirection(0);
		}
		if (directionLR == 1) {
			fire_attack.setDirection(1);
		}
	}

	void Hero::skillQMove(Maps *m)
	{
		if (isUsingQ) {
			fire_attack.OnMove(m);
		}
	}

	void Hero::skillQShow(Maps * m)
	{
		if (isUsingQ) {
			fire_attack.OnShow(m);
			skillTimes += 1;
			if (skillTimes > 20) {
				isUsingQ = false;
				fire_attack.setFireIsFlying(false);
				skillTimes = 0;
			}
		}
	}

	Hero::~Hero()
	{
	}
}
