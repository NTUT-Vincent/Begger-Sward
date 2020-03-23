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
#include "Weapon.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
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

	Weapon::Weapon()
	{
	}

	Weapon::~Weapon()
	{
	}
	
}
