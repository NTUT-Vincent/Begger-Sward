#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "CBall.h"
#include "Hero.h"
#include "Map.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Hero::Hero()
	{
		x = 480;
		y = 480;
	}

	void Hero::LoadBitmap()
	{
		player.LoadBitmap(IDB_HERO1, RGB(0, 0, 0));
	}

	void Hero::OnMove(Map *m) {
		const int STEP_SIZE = 4;
		if (isMovingLeft && m->isEmpty(x - 4, y)) {
			m->addSX(STEP_SIZE);
			x -= STEP_SIZE;
		}

		if (isMovingRight && m->isEmpty(x + 4, y)) {
			m->addSX(-4);
			x += STEP_SIZE;
		}
		if (isMovingUp && m->isEmpty(x, y - 4)) {
			m->addSY(4);
			y -= STEP_SIZE;
		}

		if (isMovingDown && m->isEmpty(x, y + 4)) {
			m->addSY(-4);
			y += STEP_SIZE;
		}
	}

	void Hero::OnShow()
	{
		player.SetTopLeft(280, 280);
		player.ShowBitmap();
	}

	int Hero::getX() {
		return x;
	}

	int Hero::getY() {
		return y;
	}

	void Hero::Initialize() {
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = false;
	}

	void Hero::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void Hero::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void Hero::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void Hero::SetMovingRight(bool b) {
		isMovingRight = b;
	}
}
