#ifndef __RANDOMATTRIBUTE_H
#define __RANDOMATTRIBUTE_H
#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѹD�� : �H���ܴ��ݩ�										   //
	// �D��i�ѽc�l�������Ǫ���o											   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class RandomAttribute: public Item
	{
	public:
		RandomAttribute();
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);
		bool intercect(Hero *h) ;
	private:
		int _x, _y;
		int rand_num;
		CMovingBitmap random_attribute_pic;
	};
}
#endif