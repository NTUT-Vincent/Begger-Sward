#ifndef __ITEM_H
#define __ITEM_H
#include "Maps.h"
#include "Hero.h"
#include "Character.h"
namespace game_framework 
{
	class Hero;
	class Item
	{
	public:
		Item();
		virtual void load() = 0;
		virtual void OnMove(Maps *m, Hero *h) = 0;
		virtual void OnShow(Maps *m) = 0;
		virtual void effect(Hero *h) = 0;
		void showOnStatusBar(int n);					//顯示道具圖片在上面的道具欄裡面
		void Initialize();
		bool isExist();									//return _isExist
		void setExist(bool b);							//設定 _isExist
		void setNumOfBox(int n);						//設定num_of_box
		void setXY(int x, int y);						//設定XY座標
		void setRandomNum(int n);						//設定random_num
		int getX();										//得到x座標
		int getY();										//得到Y座標
		int getRandomNum();								//return random_num
		int getNumOfBox();								//return num_of_box
		bool intercect(Hero *h);						//偵測是否跟別的物件座標位置相交
		bool getIsUsed();								//return _isUsed
		void setIsUsed(bool b);							//設定_isUsed
	private:
		int _x, _y;										// XY座標
		bool _isExist;									//是否存在
		int random_num;									//一個隨機數
		bool _isUsed;									//是否被使用了
		int num_of_box;									//一個隨機數，用來判定道具箱會掉哪個道具
	protected:
		CMovingBitmap item_on_status_bar;
	};
}
#endif