#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "Item.h"
#include "ProtectiveCover.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	//ProtectiveCover: Item class
	/////////////////////////////////////////////////////////////////////////////
	ProtectiveCover::ProtectiveCover()
	{
	}
	void ProtectiveCover::load()
	{
		clock_pic.LoadBitmap(".\\bitmaps\\protected_cover.bmp", RGB(195, 195, 195));
		item_on_status_bar.LoadBitmapA(".\\bitmaps\\protected_cover.bmp");
	}
	void ProtectiveCover::OnMove(Maps *m, Hero *h)
	{
		_x = getX();
		_y = getY();
		if (isExist() && intercect(h) && getNumOfBox() % 100 > 0 && getNumOfBox() % 100 <= 100)  //�p�Gnum_ofBox%100 = 0-20 �c�l�|���o�ӹD��
		{	
			//��num_of_box�M�w�o�ӹD��|���|����
			ProtectiveCover * p = new ProtectiveCover();
			p->load();
			h->addItem(p);
			setExist(false);
		}
	}
	void ProtectiveCover::OnShow(Maps *m)
	{
		if (isExist() && getNumOfBox() % 100 > 0 && getNumOfBox() % 100 <= 100)
		{
			clock_pic.SetTopLeft(m->screenX(_x), m->screenY(_y));
			clock_pic.ShowBitmap();
		}
	}
	void ProtectiveCover::effect(Hero *h)						
	{
		//�ϥιD�㪺�� �^���N�|�i�J���|�Q�����쪺�Ҧ�
		h->setCantBeDamaged(true);
		setIsUsed(false);
	}
	bool ProtectiveCover::intercect(Hero * h)
	{
		if (isExist()) {
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
