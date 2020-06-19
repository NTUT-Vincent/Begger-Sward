#ifndef __PRETECTEDCOVER_H
#define __PROTECTEDCOVER_H
#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѹD�� : ���@�n											   //
	// �D��i�ѽc�l�������Ǫ���o											   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class ProtectiveCover: public Item
	{
	public:
		ProtectiveCover();
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);				//�D�㪺�ĪG
		bool intercect(Hero *h) ;
	private:
		int _x, _y;
		CMovingBitmap clock_pic;
	};
}
#endif