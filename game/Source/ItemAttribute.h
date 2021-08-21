#ifndef __ITEMATTRIBUTE_H
#define __ITEMATTRIBUTE_H
#include "Maps.h"
#include "Character.h"
namespace game_framework
{
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供道具 : 屬性點數增加										   //
	// 道具可由箱子或擊殺怪物獲得												   //
	/////////////////////////////////////////////////////////////////////////////
	class Hero;
	class ItemAttribute: public Item					//這class是掉落物 是屬性 怪死掉會 掉落
	{
	public:
		ItemAttribute(ELEMENT_ATTRIBUTE attribute);		
		void load();
		void OnMove(Maps *m, Hero *h);
		void OnShow(Maps *m);
		bool intercect(Hero *h) ;						//檢測是否相交
		void effect(Hero *h);	
	private:
		CMovingBitmap fire_pic;
		CMovingBitmap ice_pic;
		CMovingBitmap plant_pic;
		ELEMENT_ATTRIBUTE _attribute;					//掉落物的屬性
		int _x, _y;
	};
}
#endif