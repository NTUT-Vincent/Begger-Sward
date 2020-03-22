#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "CBall.h"
#include "Hero.h"
#include "Maps.h"
#include "Enemy.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Enemy::Enemy(): Character(100)
	{
		x = 384;
		y = 384;
		hp = 1200;
		attack = 0;
	}

	void Enemy::LoadBitmap()
	{
		enemy.LoadBitmap(IDB_SCARECROW, RGB(0, 0, 0));
		//blood_bar.loadBloodBar();
		loadBloodBar();
	}

	void Enemy::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
		///下面這些是想讓enemy跟著地圖一起動 但是我的邏輯好像不太對
		///我應該要把x, y變成怪物在地圖上的座標，但現在是在螢幕上顯示的座標
		///目前是只要感應到玩家按上下左右，就會移動，但是等玩家撞到牆後，他還會繼續動。
		///目前在研究跟老師地圖教學一樣的方法，有些註解掉的地方是跟著老師那個照做的
		hp -= 10;
		m->setPos(x, y);
	}

	void Enemy::OnShow(Maps *m)
	{
		enemy.SetTopLeft(m->screenX(x), m->screenY(y));
		//enemy.SetTopLeft(x, y);
		enemy.ShowBitmap();
		//blood_bar.showBloodBar(m , hp);
		showBloodBar(m);
	}

	int Enemy::GetX1()
	{
		return x;
	}

	int Enemy::GetY1()
	{
		return y;
	}

	int Enemy::GetX2()
	{
		return x + enemy.Width();
	}

	int Enemy::GetY2()
	{
		return y + enemy.Height();
	}

	void Enemy::Initialize() {
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = false;
	}

	void Enemy::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void Enemy::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void Enemy::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void Enemy::SetMovingRight(bool b) {
		isMovingRight = b;
	}

	void Enemy::loadBloodBar() {
		blood_bar[3].LoadBitmap(IDB_BLOOD3OF4, RGB(0, 0, 0));
		blood_bar[2].LoadBitmap(IDB_BLOOD2OF4, RGB(0, 0, 0));
		blood_bar[1].LoadBitmap(IDB_BLOOD1OF4, RGB(0, 0, 0));
		blood_bar[0].LoadBitmap(IDB_BLOODALMOSTDIE, RGB(0, 0, 0));
		blood_bar[5].LoadBitmap(IDB_BLOODFULL, RGB(0, 0, 0));
		blood_bar[4].LoadBitmap(IDB_BLOODLITTLEDAMAGED, RGB(0, 0, 0));
	}

	void Enemy::showBloodBar(Maps *m1) {
		double proportion = hp / 1200.0;
		if (proportion < 1.0 / 9) {
			blood_bar[0].SetTopLeft(m1->screenX(x), m1->screenY(y - 20));
			blood_bar[0].ShowBitmap();
		}
		else if (proportion < 1.0 / 4) {
			blood_bar[1].SetTopLeft(m1->screenX(x), m1->screenY(y - 20));
			blood_bar[1].ShowBitmap();
		}
		else if (proportion < 2.0 / 4) {
			blood_bar[2].SetTopLeft(m1->screenX(x), m1->screenY(y - 20));
			blood_bar[2].ShowBitmap();
		}
		else if (proportion < 3.0 / 4)
		{
			blood_bar[3].SetTopLeft(m1->screenX(x), m1->screenY(y - 20));
			blood_bar[3].ShowBitmap();
		}
		else if (hp < 1100) {
			blood_bar[4].SetTopLeft(m1->screenX(x), m1->screenY(y - 20));
			blood_bar[4].ShowBitmap();
		}
		else {
			blood_bar[5].SetTopLeft(m1->screenX(x), m1->screenY(y - 20));
			blood_bar[5].ShowBitmap();
		}
	}
}
