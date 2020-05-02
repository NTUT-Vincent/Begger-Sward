#ifndef __ATTACK_H

#define __ATTACK_H


#include "Maps.h"
#include "Character.h"
#include "Util.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Attack {
	public:
		Attack(int x, int y);
		Attack();
		void loadBitmap();
		void OnMove(Maps *m);
		void OnShow(Maps *m);
		void setAttribute(ELEMENT_ATTRIBUTE attribute);
		void setXY(int x, int y);
		void setDirection(int direction);
		void setAttackIsFlying(bool b);
		int getX1();
		int getX2();
		int getY1();
		int getY2();
	private:
		CMovingBitmap fire_attack;
		CMovingBitmap fire_attack_boom;
		CMovingBitmap ice_attack;
		CMovingBitmap plant_attack;
		int _x, _y;
		int _direction; //0=left, 1=right
		ELEMENT_ATTRIBUTE _attribute;
		bool _attackIsFlying;
	};
}

#endif 