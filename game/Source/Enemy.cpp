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
		blood_bar.loadBloodBar();
	}

	void Enemy::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
		///�U���o�ǬO�Q��enemy��ۦa�Ϥ@�_�� ���O�ڪ��޿�n�����ӹ�
		///�����ӭn��x, y�ܦ��Ǫ��b�a�ϤW���y�СA���{�b�O�b�ù��W��ܪ��y��
		///�ثe�O�u�n�P���쪱�a���W�U���k�A�N�|���ʡA���O�����a�������A�L�ٷ|�~��ʡC
		///�ثe�b��s��Ѯv�a�ϱоǤ@�˪���k�A���ǵ��ѱ����a��O��ۦѮv���ӷӰ���
		hp -= 10;
		m->setPos(x, y);
		blood_bar.setXY(x, y);
	}

	void Enemy::OnShow(Maps *m)
	{
		enemy.SetTopLeft(m->screenX(x), m->screenY(y));
		//enemy.SetTopLeft(x, y);
		enemy.ShowBitmap();
		blood_bar.showBloodBar(m , hp);
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
		blood_bar.setFullHP(hp);
		
	}

	bool Enemy::cannotPass(Hero * hero)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return (hero->GetX2() >= x && hero->GetX1() <= x+enemy.Width() && hero->GetY2() >= y && hero->GetY1() <= y + enemy.Height());
	}
	//���ڤ����D�쩳�o�Ӽg�bmap�٬Ohero�٬Oenemy�n�A���޿�O�o�Mhero���୫�|
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
