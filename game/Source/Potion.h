#ifndef __POTION_H
#define __POTION_H
#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѹD�� : �Ĥ�												   //
	// �D��i�ѽc�l�������Ǫ���o											   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class Potion: public Item
	{
	public:
		Potion();
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);			//�ϥιD�㪺�ĪG
		bool intercect(Hero *h) ;
	private:
		int _x, _y;
		CMovingBitmap potion_pic;
	};
}
#endif