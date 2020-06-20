#ifndef __HEALTH_H
#define __HEALTH_H
#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѹD�� : �ä[�W�[�ͩR��										   //
	// �D��i�ѽc�l�������Ǫ���o												   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class Health: public Item
	{
	public:
		Health(int n);
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);				
	private:
		CMovingBitmap health_pic;
		int to_heal;						//�n�^�_�h�֥ͩR
	};
}
#endif