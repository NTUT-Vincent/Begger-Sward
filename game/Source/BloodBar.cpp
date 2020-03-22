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
#include "BloodBar.h"
#include "BloodBar.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	BloodBar::BloodBar()
	{
		_x = 0;
		_y = 0;
		full_hp = 0;
	}


	void BloodBar::setFullHP(int n) {
		full_hp = n;
	}

	void BloodBar::setXY(int x, int y) {
		_x = x;
		_y = y;
	}

	void BloodBar::loadBloodBar() {
		blood_bar[3].LoadBitmap(IDB_BLOOD3OF4, RGB(0, 0, 0));
		blood_bar[2].LoadBitmap(IDB_BLOOD2OF4, RGB(0, 0, 0));
		blood_bar[1].LoadBitmap(IDB_BLOOD1OF4, RGB(0, 0, 0));
		blood_bar[0].LoadBitmap(IDB_BLOODALMOSTDIE, RGB(0, 0, 0));
		blood_bar[4].LoadBitmap(IDB_BLOODFULL, RGB(0, 0, 0));
	}

	void BloodBar::showBloodBar(Maps *m1, int hp) {
		double proportion = hp / full_hp;
		if (proportion < 1.0 / 9) {
			blood_bar[0].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[0].ShowBitmap();
		}
		else if (proportion < 1.0 / 4) {
			blood_bar[1].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[1].ShowBitmap();
		}
		else if (proportion < 2.0 / 4) {
			blood_bar[2].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[2].ShowBitmap();
		}
		else if (proportion < 3.0/4)
		{
			blood_bar[3].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[3].ShowBitmap();
		}
		else {
			blood_bar[4].SetTopLeft(m1->screenX(_x), m1->screenY(_y - 20));
			blood_bar[4].ShowBitmap();
		}
	}
}
