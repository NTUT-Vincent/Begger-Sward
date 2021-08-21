#ifndef __RANDOMATTRIBUTE_H
#define __RANDOMATTRIBUTE_H
#include "Maps.h"
#include "Character.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供道具 : 隨機變換屬性										   //
	// 道具可由箱子或擊殺怪物獲得											   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class RandomAttribute: public Item
	{
	public:
		RandomAttribute();
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		void effect(Hero *h);				//使用道具後的效果
		bool intercect(Hero *h) ;
	private:
		int _x, _y;
		int rand_num;
		CMovingBitmap random_attribute_pic;
	};
}
#endif