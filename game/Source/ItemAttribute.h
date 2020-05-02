#ifndef __ITEMATTRIBUTE_H
#define __ITEMATTRIBUTE_H


#include "Maps.h"
#include "Character.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class ItemAttribute: public Item
	{
	public:
		ItemAttribute(ELEMENT_ATTRIBUTE attribute);
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		bool intercect(Hero *h) ;
		
	private:
		CMovingBitmap fire_pic;
		CMovingBitmap ice_pic;
		CMovingBitmap plant_pic;
		ELEMENT_ATTRIBUTE _attribute;
		int _x, _y;
	};
}

#endif // !Health_H