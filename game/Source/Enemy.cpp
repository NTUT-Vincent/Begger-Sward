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
#include "Enemy.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Enemy::Enemy(): Character(100)
	{
		x = 400;
		y = 400;
		hp = 1200;
		attack = 0;
	}

	void Enemy::LoadBitmap()
	{
		enemy.LoadBitmap(IDB_SCARECROW, RGB(0, 0, 0));
	}

	void Enemy::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
		///下面這些是想讓enemy跟著地圖一起動 但是我的邏輯好像不太對
		///我應該要把x, y變成怪物在地圖上的座標，但現在是在螢幕上顯示的座標
		///目前是只要感應到玩家按上下左右，就會移動，但是等玩家撞到牆後，他還會繼續動。
		///目前在研究跟老師地圖教學一樣的方法，有些註解掉的地方是跟著老師那個照做的

		m->setPos(x, y);
	}

	void Enemy::OnShow(Maps *m)
	{
		enemy.SetTopLeft(m->screenX(x), m->screenY(y));
		//enemy.SetTopLeft(x, y);
		enemy.ShowBitmap();
	}

	int Enemy::getX() {
		return x;
	}

	int Enemy::getY() {
		return y;
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
}
