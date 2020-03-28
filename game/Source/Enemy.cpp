#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Enemy.h"
#include "Hero.h"
#include "Maps.h"
#include "Enemy.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Enemy: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Enemy::Enemy() : Character(100)
	{
		_x = 384;
		_y = 384;
		hp = 1200;
		attack = 0;
	}

	Enemy::Enemy(int x, int y) : Character(100)
	{
		_x = x;
		_y = y;
		hp = 1200;
		attack = 0;
	}

	void Enemy::LoadBitmap()
	{
		enemy.LoadBitmap(IDB_SCARECROW, RGB(0, 0, 0));
		blood_bar.loadBloodBar();
	}

	void Enemy::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
		///下面這些是想讓enemy跟著地圖一起動 但是我的邏輯好像不太對
		///我應該要把x, y變成怪物在地圖上的座標，但現在是在螢幕上顯示的座標
		///目前是只要感應到玩家按上下左右，就會移動，但是等玩家撞到牆後，他還會繼續動。
		///目前在研究跟老師地圖教學一樣的方法，有些註解掉的地方是跟著老師那個照做的
		hp -= 10;
		m->setPos(_x, _y);
		blood_bar.setXY(_x, _y);
	}

	void Enemy::OnShow(Maps *m)
	{
		enemy.SetTopLeft(m->screenX(_x), m->screenY(_y));
		//enemy.SetTopLeft(x, y);
		enemy.ShowBitmap();
		blood_bar.showBloodBar(m, hp);
	}

	int Enemy::GetX1()
	{
		return _x;
	}

	int Enemy::GetY1()
	{
		return _y;
	}

	int Enemy::GetX2()
	{
		return _x + enemy.Width();
	}

	int Enemy::GetY2()
	{
		return _y + enemy.Height();
	}

	void Enemy::Initialize() {
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = false;
		blood_bar.setFullHP(hp);

	}

	bool Enemy::cannotPass(int x1, int x2, int y1, int y2)
	{
		//下面有一些加減運算是因為，稻草人的Bitmap本身比稻草人的身體大太多。
		return (x2 >= _x+20 && x1 <= _x+enemy.Width()-20 && y2 >= _y+60 && y1 <= _y + enemy.Height()-15);
	}

	//bool Enemy::cannotPass(Hero * hero)
	//{
	//	// 檢測擦子所構成的矩形是否碰到球
	//	return (hero->GetX2() >= x && hero->GetX1() <= x+enemy.Width() && hero->GetY2() >= y && hero->GetY1() <= y + enemy.Height());
	//}
	////其實我不知道到底這個寫在map還是hero還是enemy好，但邏輯是她和hero不能重疊
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

	void Enemy::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

}
