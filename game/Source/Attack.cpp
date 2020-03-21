#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Attack.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 其實我大致是抄CBall.h，因為我覺得子彈Attack和CBall
	//碰到就會消失的特性很像
	//所以我有做撞到Enemy就會is_exist = 0的函示
	//但因為還沒辦法顯示(因為要先setTopLeft才能貼且attack物件
	//只有在OnLMouseButtonDown才會被new，目前還沒想出怎麼貼)
	//所以也不確定他移動的pattern會如何
	//mygame.cpp 259行有把球設為is_exist = 0我還沒做
	//另外攻擊產生attack的記憶體回收機制我也還沒做
	//另外enemy被攻擊打到會扣血我也還沒做
	//attack打到東西會產生collision我也還沒做
	//HitWall我也還沒做(這裡也要生collision)
	//先睡歐
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
		// 檢測擦子所構成的矩形是否碰到球
		return HitObject(enemy->GetX1(), enemy->GetY1(),
			enemy->GetX2(), enemy->GetY2());
	}

	bool Attack::HitObject(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + 96;				// 球的左上角x座標
		int y1 = y - 32;				// 球的左上角y座標
		int x2 = x1 + 112;	// 球的右下角x座標
		int y2 = y1 + -42;	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
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