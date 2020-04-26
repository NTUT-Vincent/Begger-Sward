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
#include "PlayerStatus.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	PlauerStatus::PlauerStatus()
	{
		_x = 0;
		_y = 0;
	}

	void PlauerStatus::Initialize(Hero * h)
	{
		_h = h;
	}

	void PlauerStatus::loadPlauerStatus() {
		status_bar.LoadBitmap(IDB_STATUSBAR, RGB(255, 255, 255));
		skill_q_fire_pic.LoadBitmap(IDB_SKILLQFIREPIC);
		skill_e_pic.LoadBitmap(IDB_SKILLEPIC);
		loadDigitsBitmap(Q_cooldown_first);
		loadDigitsBitmap(Q_cooldown_ten);
		loadDigitsBitmap(E_cooldown_first);
		loadDigitsBitmap(E_cooldown_ten);
		loadDigitsBitmap(HP_first);
		loadDigitsBitmap(HP_ten);
		loadDigitsBitmap(HP_hundred);
		loadDigitsBitmap(HP_thousand);
	}

	void PlauerStatus::showPlauerStatus() {
		status_bar.SetTopLeft(0, 0);
		status_bar.ShowBitmap();
		showQ();
		showE();
		showHP();
	}

	void PlauerStatus::setXY(int x, int y) {
		_x = x;
		_y = y;
	}

	void PlauerStatus::loadDigitsBitmap(CMovingBitmap a[])
	{
		a[0].LoadBitmap(IDB_0);
		a[1].LoadBitmap(IDB_1);
		a[2].LoadBitmap(IDB_2);
		a[3].LoadBitmap(IDB_3);
		a[4].LoadBitmap(IDB_4);
		a[5].LoadBitmap(IDB_5);
		a[6].LoadBitmap(IDB_6);
		a[7].LoadBitmap(IDB_7);
		a[8].LoadBitmap(IDB_8);
		a[9].LoadBitmap(IDB_9);
	}

	void PlauerStatus::showQ()
	{
		int q_cd = _h->GetQCoolDown();
		if (q_cd == 0) {
			skill_q_fire_pic.SetTopLeft(20, 0);
			skill_q_fire_pic.ShowBitmap();
		}
		if (q_cd != 0) {
			int first = q_cd % 10;
			q_cd /= 10;
			int second = q_cd % 10;
			Q_cooldown_first[first].SetTopLeft(50, 20);
			Q_cooldown_first[first].ShowBitmap();
			Q_cooldown_ten[second].SetTopLeft(40, 20);
			Q_cooldown_ten[second].ShowBitmap();
		}

	}

	void PlauerStatus::showE()
	{
		int e_cd = _h->GetECoolDown();
		if (e_cd == 0) {
			skill_e_pic.SetTopLeft(160, 0);
			skill_e_pic.ShowBitmap();
		}
		if (e_cd != 0) {
			int first = e_cd % 10;
			e_cd /= 10;
			int second = e_cd % 10;
			E_cooldown_first[first].SetTopLeft(200, 20);
			E_cooldown_first[first].ShowBitmap();
			E_cooldown_ten[second].SetTopLeft(190, 20);
			E_cooldown_ten[second].ShowBitmap();
		}
	}

	void PlauerStatus::showHP()
	{
		int hp = _h->getHP();
		if (hp != 0) {
			int first = hp % 10;
			hp /= 10;
			int second = hp % 10;
			hp /= 10;
			int third = hp % 10;
			hp /= 10;
			int forth = hp % 10;

			HP_first[first].SetTopLeft(500, 20);
			HP_first[first].ShowBitmap();
			HP_ten[second].SetTopLeft(490, 20);
			HP_ten[second].ShowBitmap();
			HP_hundred[third].SetTopLeft(480, 20);
			HP_hundred[third].ShowBitmap();
			HP_thousand[forth].SetTopLeft(470, 20);
			HP_thousand[forth].ShowBitmap();
		}
	}

	
}
