#ifndef __POTION_H
#define __POTION_H
#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供道具 : 藥水												   //
	// 道具可由箱子或擊殺怪物獲得											   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class Potion: public Item
	{
	public:
		Potion();
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);			//使用道具的效果
		bool intercect(Hero *h) ;
	private:
		int _x, _y;
		CMovingBitmap potion_pic;
	};
}
#endif