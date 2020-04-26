#ifndef __PLAYERSTATUS_H
#define __PLAYERSTATUS_H


#include "Maps.h"
#include "Character.h"
#include "Hero.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class PlauerStatus
	{
	public:
		PlauerStatus();
		void Initialize(Hero *h);
		void loadPlauerStatus();
		void showPlauerStatus();
		void setXY(int x, int y);
		void loadDigitsBitmap(CMovingBitmap a[]);
		void showQ();
		void showE();
		void showHP();

	private:
		int _x, _y;
		CMovingBitmap status_bar;
		CMovingBitmap skill_q_fire_pic;
		CMovingBitmap skill_e_pic;
		CMovingBitmap HP_first[10];
		CMovingBitmap HP_ten[10];
		CMovingBitmap HP_hundred[10];
		CMovingBitmap HP_thousand[10];

		CMovingBitmap Q_cooldown_first[10];
		CMovingBitmap Q_cooldown_ten[10];
		CMovingBitmap E_cooldown_first[10];
		CMovingBitmap E_cooldown_ten[10];

		Hero *_h;
	};
}

#endif // !PlauerStatus_H