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
		x = 200;
		y = 200;
	}

	void Enemy::LoadBitmap()
	{
		player.LoadBitmap(IDB_PLAYER, RGB(255, 255, 255));
	}

	void Enemy::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
		///�U���o�ǬO�Q��enemy��ۦa�Ϥ@�_�� ���O�ڪ��޿�n�����ӹ�
		///�����ӭn��x, y�ܦ��Ǫ��b�a�ϤW���y�СA���{�b�O�b�ù��W��ܪ��y��
		///�ثe�O�u�n�P���쪱�a���W�U���k�A�N�|���ʡA���O�����a�������A�L�ٷ|�~��ʡC
		///�ثe�b��s��Ѯv�a�ϱоǤ@�˪���k�A���ǵ��ѱ����a��O��ۦѮv���ӷӰ���
		if (isMovingLeft) {
			x += STEP_SIZE;
		}

		if (isMovingRight) {
			x -= STEP_SIZE;
		}
		if (isMovingUp) {
			y += STEP_SIZE;
		}

		if (isMovingDown) {
			y -= STEP_SIZE;
		}
	}

	void Enemy::OnShow(Maps *m)
	{
		//player.SetTopLeft(m->screenX(x), m->screenY(y));
		player.SetTopLeft(x, y);
		player.ShowBitmap();
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
