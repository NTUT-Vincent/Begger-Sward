#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Attack.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// ���ڤj�P�O��CBall.h�A�]����ı�o�l�uAttack�MCBall
	//�I��N�|�������S�ʫܹ�
	//�ҥH�ڦ�������Enemy�N�|is_exist = 0�����
	//���]���٨S��k���(�]���n��setTopLeft�~��K�Battack����
	//�u���bOnLMouseButtonDown�~�|�Qnew�A�ثe�٨S�Q�X���K)
	//�ҥH�]���T�w�L���ʪ�pattern�|�p��
	//mygame.cpp 259�榳��y�]��is_exist = 0���٨S��
	//�t�~��������attack���O����^������ڤ]�٨S��
	//�t�~enemy�Q��������|����ڤ]�٨S��
	//attack����F��|����collision�ڤ]�٨S��
	//HitWall�ڤ]�٨S��(�o�̤]�n��collision)
	//���μ�
	/////////////////////////////////////////////////////////////////////////////

	Attack::Attack()
	{

	}

	Attack::Attack(int hx, int hy):x(hx), y(hy)
	{
		is_exist = true;
	}

	bool Attack::HitEnemy(Enemy * enemy)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitObject(enemy->GetX1(), enemy->GetY1(),
			enemy->GetX2(), enemy->GetY2());
	}

	bool Attack::HitObject(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + 96;				// �y�����W��x�y��
		int y1 = y - 32;				// �y�����W��y�y��
		int x2 = x1 + 112;	// �y���k�U��x�y��
		int y2 = y1 + -42;	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	int Attack::GetX1()
	{
		return x;
	}

	int Attack::GetY1()
	{
		return y;
	}

	int Attack::GetX2()
	{
		return x + animation.Width();
	}

	int Attack::GetY2()
	{
		return y + animation.Height();
	}

	void Attack::LoadBitmap()
	{
		animation.LoadBitmap(IDB_ATTACK1, RGB(0, 0, 0));

	}

	bool Attack::isExist()
	{
		return is_exist;
	}

	void Attack::OnMove()
	{
		if (is_exist)
		{
			x += 8;
		}
	}

	void Attack::SetExist(bool flag)
	{
		is_exist = flag;
	}

	void Attack::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Attack::OnShow()
	{
		if (is_exist) {
			animation.SetTopLeft(x, y);
			animation.ShowBitmap();
		}
	}
}