#ifndef __SHOE_H
#define __SHE_H


#include "Maps.h"
#include "Character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供道具 : 加跑速的鞋子										   //
	// 道具可由箱子或擊殺怪物獲得												   //
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