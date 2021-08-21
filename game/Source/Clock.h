#ifndef __CLOCK_H
#define __CLOCK_H
#include "Maps.h"
#include "Character.h"
namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供道具，可以重製所有招式的冷卻時間						   //
	// 道具可由箱子或擊殺怪物獲得											   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class Clock: public Item
	{
	public:
		Clock();
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);				//使用道具的效果
		bool intercect(Hero *h) ;
	private:
		int _x, _y;
		CMovingBitmap clock_pic;
	};
}
#endif