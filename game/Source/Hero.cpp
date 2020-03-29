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

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Hero::Hero(): Character(100)
	{
		x = 480;
		y = 480;
		hp = 400;
		attack = 20;
	}

	void Hero::LoadBitmap()
	{
		heroL.LoadBitmap(IDB_HERO_L, RGB(0, 0, 0));
		heroR.LoadBitmap(IDB_HERO_R, RGB(0, 0, 0));
		char *filename1[6] = { ".\\bitmaps\\walkingL1.bmp",".\\bitmaps\\walkingL2.bmp",".\\bitmaps\\walkingL3.bmp",".\\bitmaps\\walkingL4.bmp", ".\\bitmaps\\walkingL3.bmp", ".\\bitmaps\\walkingL2.bmp" };
		for (int i = 0; i < 6; i++)	// 載入動畫(由6張圖形構成)
			walkingLeft.AddBitmap(filename1[i], RGB(0, 0, 0));
		char *filename2[6] = { ".\\bitmaps\\walkingR1.bmp",".\\bitmaps\\walkingR2.bmp",".\\bitmaps\\walkingR3.bmp",".\\bitmaps\\walkingR4.bmp", ".\\bitmaps\\walkingR3.bmp", ".\\bitmaps\\walkingR2.bmp" };
		for (int i = 0; i < 6; i++)	// 載入動畫(由6張圖形構成)
			walkingRight.AddBitmap(filename2[i], RGB(0, 0, 0));
	}

	void Hero::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
		if (isMovingLeft && m->isEmpty(x - STEP_SIZE, y) && !m->bumpIntoEnemy(GetX1() - STEP_SIZE, GetX2() - STEP_SIZE, GetY1(), GetY2())) {
			m->addSX(STEP_SIZE);
			x -= STEP_SIZE;
		}

		if (isMovingRight && m->isEmpty(x + STEP_SIZE, y) && !m->bumpIntoEnemy(GetX1() + STEP_SIZE, GetX2() + STEP_SIZE, GetY1(), GetY2())) {
			m->addSX(-STEP_SIZE);
			x += STEP_SIZE;
		}
		if (isMovingUp && m->isEmpty(x, y - STEP_SIZE) && !m->bumpIntoEnemy(GetX1(), GetX2(), GetY1() - STEP_SIZE, GetY2() - STEP_SIZE)) {
			m->addSY(STEP_SIZE);
			y -= STEP_SIZE;
		}

		if (isMovingDown && m->isEmpty(x, y + STEP_SIZE) && !m->bumpIntoEnemy(GetX1(), GetX2(), GetY1() + STEP_SIZE, GetY2() + STEP_SIZE)) {
			m->addSY(-STEP_SIZE);
			y += STEP_SIZE;
		}
		m->getHeroX(x);
		m->getHeroY(y);
		walkingLeft.OnMove();
		walkingRight.OnMove();
	}

	void Hero::OnShow()
	{
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

	bool Hero::cantPass(Maps * m)
	{
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


	Hero::~Hero()
	{
	}
}
