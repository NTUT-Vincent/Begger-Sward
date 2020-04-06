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
#include "Scarecrow.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Enemy: Ball class
	/////////////////////////////////////////////////////////////////////////////

	//�Y�bCharacter�MEnemy�������@��hp�A��ܪ�����Character��������

	Scarecrow::Scarecrow()
	{
		_x = 384;
		_y = 384;
		hp = 1200;
		attack = 0;
	}

	Scarecrow::Scarecrow(int x, int y) 
	{
		_x = x;
		_y = y;
		hp = 1200;
		attack = 0;
	}

	void Scarecrow::LoadBitmap()
	{
		enemy.LoadBitmap(IDB_SCARECROW, RGB(0, 0, 0));
		blood_bar.loadBloodBar();
		EnemyRect = enemy.ReturnCRect();
	}

	void Scarecrow::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
	}

	void Scarecrow::OnShow(Maps *m)
	{
		if (isAlive()) {
			enemy.SetTopLeft(m->screenX(_x), m->screenY(_y));
			//enemy.SetTopLeft(x, y);
			enemy.ShowBitmap();
			blood_bar.setXY(_x, _y+50);
			blood_bar.showBloodBar(m, hp);
		}
		
	}

	int Scarecrow::GetX1()
	{
		return _x;
	}

	int Scarecrow::GetY1()
	{
		return _y;
	}

	int Scarecrow::GetX2()
	{
		return _x + enemy.Width();
	}

	int Scarecrow::GetY2()
	{
		return _y + enemy.Height();
	}

	void Scarecrow::Initialize() {
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = false;
		blood_bar.setFullHP(hp);
	}

	bool Scarecrow::intersect(int x1, int x2, int y1, int y2)
	{
		//�U�����@�ǥ[��B��O�]���A�_��H��Bitmap������_��H������j�Ӧh�C
		if (isAlive()) {
			if (x2 >= _x + 20 && x1 <= _x + enemy.Width() - 20 && y2 >= _y + 60 && y1 <= _y + enemy.Height() - 15) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
		
	}

	//bool Enemy::cannotPass(Hero * hero)
	//{
	//	// �˴����l�Һc�����x�άO�_�I��y
	//	return (hero->GetX2() >= x && hero->GetX1() <= x+enemy.Width() && hero->GetY2() >= y && hero->GetY1() <= y + enemy.Height());
	//}
	////���ڤ����D�쩳�o�Ӽg�bmap�٬Ohero�٬Oenemy�n�A���޿�O�o�Mhero���୫�|
	void Scarecrow::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void Scarecrow::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void Scarecrow::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void Scarecrow::SetMovingRight(bool b) {
		isMovingRight = b;
	}

	void Scarecrow::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void Scarecrow::offsetHP(int offset)
	{
		hp += offset;
	}

	bool Scarecrow::isAlive()
	{
		if (hp <= 0) {
			return false;
		}
		return true;
	}

	CRect * Scarecrow::GetRect()
	{
		return &EnemyRect;
	}

}
