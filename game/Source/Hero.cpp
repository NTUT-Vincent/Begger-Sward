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
#include "Weapon.h"

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
		hero.LoadBitmap(IDB_HERO1, RGB(0, 0, 0));
	}

	void Hero::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
		if (isMovingLeft && m->isEmpty(x - STEP_SIZE, y)) {
			m->addSX(STEP_SIZE);
			x -= STEP_SIZE;
		}

		if (isMovingRight && m->isEmpty(x + STEP_SIZE, y)) {
			m->addSX(-STEP_SIZE);
			x += STEP_SIZE;
		}
		if (isMovingUp && m->isEmpty(x, y - STEP_SIZE)) {
			m->addSY(STEP_SIZE);
			y -= STEP_SIZE;
		}

		if (isMovingDown && m->isEmpty(x, y + STEP_SIZE)) {
			m->addSY(-STEP_SIZE);
			y += STEP_SIZE;
		}
		m->getHeroX(x);
		m->getHeroY(y);
	}

	void Hero::OnShow()
	{
		hero.SetTopLeft(280, 280);
		hero.ShowBitmap();
	}

	int Hero::GetX1() {
		return x;
	}

	int Hero::GetY1() {
		return y;
	}

	int Hero::GetX2()
	{
		return x + hero.Width();
	}

	int Hero::GetY2()
	{
		return y + hero.Height();
	}

	void Hero::Initialize() {
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttack = false;
		isUsingA = isUsingQ = isUsingW = isUsingE = isUsingR = false;
	}

	void Hero::SetMovingDown(bool b) {
		isMovingDown = b;
		direction = 2;
	}

	void Hero::SetMovingUp(bool b) {
		isMovingUp = b;
		direction = 1;
	}

	void Hero::SetMovingLeft(bool b) {
		isMovingLeft = b;
		direction = 3;
	}

	void Hero::SetMovingRight(bool b) {
		isMovingRight = b;
		direction = 4;
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
	Hero::~Hero()
	{
	}
}
