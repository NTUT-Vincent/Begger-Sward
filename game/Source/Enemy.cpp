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

	//�Y�bCharacter�MEnemy�������@��hp�A��ܪ�����Character��������

	Enemy::Enemy() : Character("scarecrow")
	{
		_x = 384;
		_y = 384;
		hp = 1200;
		attack = 0;
	}

	Enemy::Enemy(int x, int y, int monsterHp, string name) : Character(name)
	{
		_x = x;
		_y = y;
		hp = monsterHp;
		attack = 0;
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
	//	//�U�����@�ǥ[��B��O�]���A�_��H��Bitmap������_��H������j�Ӧh�C
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
	//	// �˴����l�Һc�����x�άO�_�I��y
	//	return (hero->GetX2() >= x && hero->GetX1() <= x+enemy.Width() && hero->GetY2() >= y && hero->GetY1() <= y + enemy.Height());
	//}
	////���ڤ����D�쩳�o�Ӽg�bmap�٬Ohero�٬Oenemy�n�A���޿�O�o�Mhero���୫�|
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

	void Enemy::offsetHP(int offset)
	{
		hp += offset;
	}

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

}
