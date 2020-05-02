#ifndef __ITEM_H
#define __ITEM_H


#include "Maps.h"
#include "Hero.h"
#include "Character.h"

namespace game_framework {
	class Hero;
	class Item
	{
	public:
		Item();
		virtual void load() = 0;
		virtual void OnMove(Maps *m, Hero *h) = 0;
		virtual void OnShow(Maps *m) = 0;
		void Initialize();
		bool isExist();
		void setExist(bool b);
		void setXY(int x, int y);
		void setRandomNum(int n);
		int getX();
		int getY();
		int getRandomNum();
		bool intercect(Hero *h);
	
	private:
		int _x, _y;
		bool _isExist;
		int random_num;
	};
}

#endif // !Item_H