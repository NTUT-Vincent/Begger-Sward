#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "Item.h"
#include "Potion.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//Potion: Item class
	/////////////////////////////////////////////////////////////////////////////
	Potion::Potion()
	{
	}
	void Potion::load()
	{
		potion_pic.LoadBitmap(IDB_ITEMPOTION);
		item_on_status_bar.LoadBitmapA(IDB_ITEMPOTION);
	}
	void Potion::OnMove(Maps *m, Hero *h)
	{
		_x = getX();
		_y = getY();
		if (isExist() && intercect(h) && getNumOfBox() % 100 > 50 &&  getNumOfBox() % 100 <= 75)  //�p�Gnum_ofBox%100 = 50-75 �c�l�|���o�ӹD��
		{
			Potion * p = new Potion();
			p->load();
			h->addItem(p);					//push���^���D���檺vector
			setExist(false);
		}
	}
	void Potion::OnShow(Maps *m)
	{
		if (isExist() && getNumOfBox() % 100 > 50 && getNumOfBox() % 100 <= 75)
		{
			potion_pic.SetTopLeft(m->screenX(_x), m->screenY(_y));
			potion_pic.ShowBitmap();
		}
	}
	void Potion::effect(Hero *h)
	{
		for (int i = 0; i < 100; i++)				//�ϥ��Ĥ���|�W�[100hp�A�����|�[�W�L�̤j�ͩR
		{
			if (h->getHP() < h->getFullHP()) 
			{
				h->addHp(1);
			}
		}
		setIsUsed(false);
	}
	bool Potion::intercect(Hero * h)
	{
		if (isExist()) 
		{
			if (h->GetX2() >= _x + 10 && h->GetX1() <= _x + 20 && h->GetY2() >= _y + 10 && h->GetY1() <= _y + 20) 
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
		return false;
	}
}
