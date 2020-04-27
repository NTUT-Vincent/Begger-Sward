#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include <ctgmath>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Enemy.h"
#include "Hero.h"
#include "Maps.h"
#include "Enemy.h"
#include "Scarecrow.h"
#include "GreenSlime.h"
#include "Util.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Enemy: Ball class
	/////////////////////////////////////////////////////////////////////////////

	//�Y�bCharacter�MEnemy�������@��hp�A��ܪ�����Character��������

	GreenSlime::GreenSlime()
	{
		_x = 384;
		_y = 384;
		attack_damage = 0;
	}

	GreenSlime::GreenSlime(int x, int y, Hero *h) : Enemy(x, y, 1200, "GreenSlime", h, PLANT)
	{
		attack_damage = 20;
		attack_cool_down = 0;
	}

	GreenSlime::~GreenSlime()
	{
	}

	void GreenSlime::LoadBitmap()
	{
		blood_bar.loadBloodBar();
		/////�Ǫ����ʵe
		char *filename[3] = { ".\\bitmaps\\greenslime1.bmp",".\\bitmaps\\greenslime2.bmp",".\\bitmaps\\greenslime3.bmp"};
		for (int i = 0; i < 3; i++)	// ���J�ʵe(��6�i�ϧκc��)
			slime.AddBitmap(filename[i], RGB(0, 0, 0));
		/////�������ʵe
		char *filename2[5] = { ".\\bitmaps\\greenslime_attack1.bmp",".\\bitmaps\\greenslime_attack2.bmp",".\\bitmaps\\greenslime_attack3.bmp", ".\\bitmaps\\greenslime_attack4.bmp", ".\\bitmaps\\greenslime_attack5.bmp" };
		for (int i = 0; i < 5; i++)	// ���J�ʵe(��6�i�ϧκc��)
			attack_animation.AddBitmap(filename2[i], RGB(0, 0, 0));
		attack_animation.SetDelayCount(3);
	}

	void GreenSlime::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
		if (isAlive()) {
			attack();
			attack_cool_down -= 1;
			slime.OnMove();
			movement(m);
		}
	}

	void GreenSlime::OnShow(Maps *m)
	{
		if (isAlive()) {
			if (isAttacking) {
				attackShow(m);
				blood_bar.setXY(GetX1(), GetY1() + 50);
				blood_bar.showBloodBar(m, hp);
			}
			else {
				slime.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
				//enemy.SetTopLeft(x, y);
				slime.OnShow();
				blood_bar.setXY(GetX1(), GetY1() + 50);
				blood_bar.showBloodBar(m, hp);
			}
		}

	}

	int GreenSlime::GetX1()
	{
		return _x;
	}

	int GreenSlime::GetY1()
	{
		return _y;
	}

	int GreenSlime::GetX2()
	{
		return _x + slime.Width();
	}

	int GreenSlime::GetY2()
	{
		return _y + slime.Height();
	}

	void GreenSlime::Initialize() {
		_x = ini_x;
		_y = ini_y;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttacking =  false;
		hp = 1200;
		blood_bar.setFullHP(hp);
		
	}

	bool GreenSlime::intersect(int x1, int x2, int y1, int y2)
	{
		//�U�����@�ǥ[��B��O�]���A�_��H��Bitmap������_��H������j�Ӧh�C
		if (isAlive()) {
			if (x2 >= _x + 20 && x1 <= _x + slime.Width() - 20 && y2 >= _y + 80 && y1 <= _y + slime.Height() - 15) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;

	}

	//bool Enemy::cannotPass(Hero * hero)
	//{
	//	// �˴����l�Һc�����x�άO�_�I��y
	//	return (hero->GetX2() >= x && hero->GetX1() <= x+enemy.Width() && hero->GetY2() >= y && hero->GetY1() <= y + enemy.Height());
	//}
	////���ڤ����D�쩳�o�Ӽg�bmap�٬Ohero�٬Oenemy�n�A���޿�O�o�Mhero���୫�|
	void GreenSlime::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void GreenSlime::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void GreenSlime::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void GreenSlime::SetMovingRight(bool b) {
		isMovingRight = b;
	}

	void GreenSlime::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void GreenSlime::movement(Maps *m)
	{
		int x = GetX1();
		int y = GetY1() + 64;
		int step_size = rand() % 3;
		if (hero_on_map->GetX1() > x && m->isEmpty(x + step_size, y)) {
			_x += step_size;
		}
		if (hero_on_map->GetX1() < x && m->isEmpty(x - step_size, y)) {
			_x -= step_size;
		}
		if (hero_on_map->GetY1() > y && m->isEmpty(x, y + step_size)) {
			_y += step_size;
		}
		if (hero_on_map->GetY1() < y && m->isEmpty(x, y - step_size)) {
			_y -= step_size;
		}
		
	}




	CRect * GreenSlime::GetRect()
	{
		return &EnemyRect;
	}

	void GreenSlime::attack()
	{
		if (intersect(hero_on_map->GetX1(), hero_on_map->GetX2(), hero_on_map->GetY1(), hero_on_map->GetY2()) && attack_cool_down <= 0) {
			isAttacking = true;
			hero_on_map->offsetHp(attack_damage);
		}
		attack_animation.OnMove();
		if (!isAttacking) {
			attack_animation.Reset();
		}
	}

	void GreenSlime::attackShow(Maps * m)
	{
		if (isAttacking) {
			attack_animation.SetTopLeft(m->screenX(_x), m->screenY(_y));
			attack_animation.OnShow();
			if (attack_animation.IsFinalBitmap()) {
				isAttacking = false;
				attack_cool_down = 90; //�C���������j3��
			}
		}
	}

}
