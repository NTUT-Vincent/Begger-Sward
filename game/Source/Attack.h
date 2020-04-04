#ifndef __ATTACK_H

#define __ATTACK_H


#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class Attack {
	public:
		Attack(int x, int y);
		Attack();
		void loadBitmap();
		void OnMove(Maps *m);
		void OnShow(Maps *m);
		void setAttribute(int n);
		void setXY(int x, int y);
		void setDirection(int direction);
		void setFireIsFlying(bool b);
		int getX1();
		int getX2();
		int getY1();
		int getY2();
	private:
		CMovingBitmap fire_attack;
		CMovingBitmap fire_attack_boom;
		int _x, _y;
		int _direction; //0=left, 1=right
		int _attribute; //1=fire
		bool _fireIsFlying;
	};
}

#endif 