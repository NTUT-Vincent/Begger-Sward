#ifndef BLOODBAR_H
#define BLOODBAR_H


#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class BloodBar
	{
	public:
		BloodBar();
		void loadBloodBar();
		void showBloodBar(Maps *m, int hp);
		void setFullHP(int n);
		void setXY(int x, int y);

	private:
		CMovingBitmap blood_bar[5];
		int full_hp;
		int _x, _y;

	};
}

#endif // !BloodBar_H