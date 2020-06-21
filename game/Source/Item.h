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
		void showOnStatusBar(int n);					//��ܹD��Ϥ��b�W�����D����̭�
		void Initialize();
		bool isExist();									//return _isExist
		void setExist(bool b);							//�]�w _isExist
		void setNumOfBox(int n);						//�]�wnum_of_box
		void setXY(int x, int y);						//�]�wXY�y��
		void setRandomNum(int n);						//�]�wrandom_num
		int getX();										//�o��x�y��
		int getY();										//�o��Y�y��
		int getRandomNum();								//return random_num
		int getNumOfBox();								//return num_of_box
		bool intercect(Hero *h);						//�����O�_��O������y�Ц�m�ۥ�
		bool getIsUsed();								//return _isUsed
		void setIsUsed(bool b);							//�]�w_isUsed
	private:
		int _x, _y;										// XY�y��
		bool _isExist;									//�O�_�s�b
		int random_num;									//�@���H����
		bool _isUsed;									//�O�_�Q�ϥΤF
		int num_of_box;									//�@���H���ơA�ΨӧP�w�D��c�|�����ӹD��
<<<<<<< HEAD

=======
>>>>>>> b21484bf4faa30161cb87177111bbcf0ee7ce529
	protected:
		CMovingBitmap item_on_status_bar;
	};
}
#endif