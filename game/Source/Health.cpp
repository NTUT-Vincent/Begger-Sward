#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "Item.h"
#include "Health.h"
namespace game_framework {
	Health::Health(int n)											
	{
		to_heal = n;
	}
	void Health::load()
	{
		health_pic.LoadBitmap(IDB_ITEMHEALTH, RGB(0, 0, 0));
	}
	void Health::OnMove(Maps *m, Hero *h)
	{
		if (isExist() && intercect(h)) {										//�p�G�^���ߨ�[�ͩR �ߨ��N���s�b�a�ϤW�F
			h->addHp(to_heal);
			setExist(false);
		}
	}
	void Health::OnShow(Maps *m)
	{
		if (isExist()) {
			health_pic.SetTopLeft(m->screenX(getX()), m->screenY(getY()));
			health_pic.ShowBitmap();
		}
	}
	void Health::effect(Hero *h)												//�]�����O�D�ʨϥΪ��D�� �ҥH����effect
	{
	}
}
