#ifndef __SHOE_H
#define __SHE_H


#include "Maps.h"
#include "Character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѹD�� : �[�]�t���c�l										   //
	// �D��i�ѽc�l�������Ǫ���o												   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class Shoe: public Item
	{
	public:
		Shoe();
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);
		bool intercect(Hero *h) ;
		
	private:
		int _x, _y;
		CMovingBitmap clock_pic;
	};
}

#endif // !Health_H