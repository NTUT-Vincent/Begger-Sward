#ifndef __WEAPON_H
#define __WEAPON_H

#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
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
<<<<<<< HEAD

	Weapon::Weapon()
	{
	}

	Weapon::~Weapon()
	{
	}

}
=======
>>>>>>> 4995f6caefc1072dbbade996236175c69e4b9d5e

	
}
#endif
