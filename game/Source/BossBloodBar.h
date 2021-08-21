#ifndef __BOSSBLOODBAR_H
#define __BOSSBLOODBAR_H
#include "Maps.h"
#include "Character.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供boss的血條												   //
	/////////////////////////////////////////////////////////////////////////////
	class BossBloodBar
	{
	public:
		BossBloodBar();
		void loadBloodBar();
		void showBloodBar(Maps *m, int hp);
		void setFullHP(int n);
		void setXY(int x, int y);
		int getFullHP();
	private:
		CMovingBitmap blood_bar[12];
		double full_hp;
		int _x, _y;
	};
}
#endif 