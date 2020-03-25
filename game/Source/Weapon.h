#ifndef __WEAPON_H
#define __WEAPON_H

#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Weapon
	{
	public:
		Weapon();
		~Weapon();
		void LoadBitap();
		void ShowBitmap();
		void setXY(int x, int y);
		void skillQ();
		void skillW();
		void skillE();
		void skillR();
		void NAttack();

	private:
		int _x, _y;
	};

	
}
#endif
