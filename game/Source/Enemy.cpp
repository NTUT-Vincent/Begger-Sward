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

	//若在Character和Enemy中都有一個hp，選擇直接用Character中的那個

	Enemy::Enemy() : Character("scarecrow")
	{
		_x = 384;
		_y = 384;
		hp = 1200;
		attack = 0;
	}

	Enemy::Enemy(int x, int y, int monsterHp, string name, Hero *h, ELEMENT_ATTRIBUTE a) : Character(name)
	{
		_x = x;
		_y = y;
		ini_x = x;
		ini_y = y;
		hp = monsterHp;
		attack = 0;
		isAttacking = false;
		hero_on_map = h;
		_attribute = a;
	}

	Enemy::~Enemy()
	{
	}

	/*void Enemy::LoadBitmap()
	{
		enemy.LoadBitmap(IDB_SCARECROW, RGB(0, 0, 0));
		blood_bar.loadBloodBar();
		EnemyRect = enemy.ReturnCRect();
	}*/

	//void Enemy::OnMove(Maps * m) {
	//	const int STEP_SIZE = 4;
	//}

	//void Enemy::OnShow(Maps *m)
	//{
	//	if (isAlive()) {
	//		enemy.SetTopLeft(m->screenX(_x), m->screenY(_y));
	//		//enemy.SetTopLeft(x, y);
	//		enemy.ShowBitmap();
	//		blood_bar.setXY(_x, _y+50);
	//		blood_bar.showBloodBar(m, hp);
	//	}
	//	
	//}

	//int Enemy::GetX1()
	//{
	//	return _x;
	//}

	//int Enemy::GetY1()
	//{
	//	return _y;
	//}

	//int Enemy::GetX2()
	//{
	//	return _x + enemy.Width();
	//}

	//int Enemy::GetY2()
	//{
	//	return _y + enemy.Height();
	//}

	//void Enemy::Initialize() {
	//	isMovingDown = isMovingUp = isMovingLeft = isMovingRight = false;
	//	blood_bar.setFullHP(hp);
	//}

	//bool Enemy::intersect(int x1, int x2, int y1, int y2)
	//{
	//	//下面有一些加減運算是因為，稻草人的Bitmap本身比稻草人的身體大太多。
	//	if (isAlive()) {
	//		if (x2 >= _x + 20 && x1 <= _x + enemy.Width() - 20 && y2 >= _y + 60 && y1 <= _y + enemy.Height() - 15) {
	//			return true;
	//		}
	//		else {
	//			return false;
	//		}
	//	}
	//	return false;
	//	
	//}

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

	void Enemy::offsetHP(int offset, ELEMENT_ATTRIBUTE attribute)
	{
		if (isCounterAttribute(_attribute, attribute)) {
			hp += (offset * 2);
		}
		else if (isCounterAttribute(attribute, _attribute)) {
			hp += (offset / 2);
		}
		else {
			hp += offset;
		}
	}
		
	

	//void Enemy::showHp(Maps *m, int x, int y)
	//{
	//	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	//	CFont f, *fp;
	//	f.CreatePointFont(80, "Times New Roman");	// 產生 font f; 160表示16 point的字
	//	fp = pDC->SelectObject(&f);					// 選用 font f
	//	pDC->SetBkColor(RGB(0, 0, 0));
	//	pDC->SetTextColor(RGB(255, 255, 0));
	//	char str[80];								// Demo 數字對字串的轉換
	//	sprintf(str, "%d", hp);
	//	pDC->TextOut(m->screenX(x), m->screenY(y), str);
	//	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	//	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	//}

	bool Enemy::isAlive()
	{
		if (hp <= 0) {
			return false;
		}
		return true;
	}

	CRect * Enemy::GetRect()
	{
		return &EnemyRect;
	}

	bool Enemy::isAttack()
	{
		return isAttacking;
	}

	bool Enemy::isCounterAttribute(ELEMENT_ATTRIBUTE a, ELEMENT_ATTRIBUTE b)
	{
		if (a == FIRE) {
			if (b == ICE) {
				return true;
			}
		}
		if (a == ICE) {
			if (b == PLANT) {
				return true;
			}
		}
		if (a == PLANT) {
			if (b == FIRE) {
				return true;
			}
		}
		return false;
	}

}
