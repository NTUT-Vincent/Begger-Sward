#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include <ctgmath>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Hero.h"
#include "Maps.h"
#include "Enemy.h"
#include "RedSlime.h"
#include "Util.h"
#include "Item.h"
#include "ItemAttribute.h"

namespace game_framework {

	//�Y�bCharacter�MEnemy�������@��hp�A��ܪ�����Character��������

	RedSlime::RedSlime()
	{
		_x = 384;
		_y = 384;
		attack_damage = 0;
	}

	RedSlime::RedSlime(int x, int y, Hero *h) : Enemy(x, y, 1200, "RedSlime", h, FIRE)
	{
		attack_damage = 20;
		attack_cool_down = 0;
		items.push_back(new ItemAttribute(_attribute));
	}

	RedSlime::~RedSlime()
	{
	}

	void RedSlime::LoadBitmap()
	{
		blood_bar.loadBloodBar();
		/////�����D��
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->load();
		}
		/////�Ǫ����ʵe
		char *filename[3] = { ".\\bitmaps\\redslime1.bmp",".\\bitmaps\\redslime2.bmp",".\\bitmaps\\redslime3.bmp"};
		for (int i = 0; i < 3; i++)	// ���J�ʵe(��6�i�ϧκc��)
			slime.AddBitmap(filename[i], RGB(0, 0, 0));
		/////�������ʵe
		char *filename2[5] = { ".\\bitmaps\\redslime_attack1.bmp",".\\bitmaps\\redslime_attack2.bmp",".\\bitmaps\\redslime_attack3.bmp", ".\\bitmaps\\redslime_attack4.bmp", ".\\bitmaps\\redslime_attack5.bmp" };
		for (int i = 0; i < 5; i++)	// ���J�ʵe(��6�i�ϧκc��)
			attack_animation.AddBitmap(filename2[i], RGB(0, 0, 0));
		attack_animation.SetDelayCount(3);
	}

	void RedSlime::OnMove(Maps * m) {
		const int STEP_SIZE = 4;
		if (isAlive()) {
			attack();
			attack_cool_down -= 1;
			slime.OnMove();
			movement(m);
		}
		if (!isAlive()) {
			itemsOnMove(m);
		}
	}

	void RedSlime::OnShow(Maps *m)
	{
		if (isAlive()) {
			if (isAttacking) {
				attackShow(m);
				blood_bar.setXY(GetX1(), GetY1());
				blood_bar.showBloodBar(m, hp);
			}
			else {
				slime.SetTopLeft(m->screenX(GetX1()), m->screenY(GetY1()));
				//enemy.SetTopLeft(x, y);
				slime.OnShow();
				blood_bar.setXY(GetX1(), GetY1());
				blood_bar.showBloodBar(m, hp);
			}
		}
		if (!isAlive()) {
			itemsOnShow(m);
		}

	}

	int RedSlime::GetX1()
	{
		return _x;
	}

	int RedSlime::GetY1()
	{
		return _y;
	}

	int RedSlime::GetX2()
	{
		return _x + slime.Width();
	}

	int RedSlime::GetY2()
	{
		return _y + slime.Height();
	}

	void RedSlime::Initialize() {
		_x = ini_x;
		_y = ini_y;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttacking =  false;
		hp = 1200;
		blood_bar.setFullHP(hp);
		///�D��
		for (unsigned i = 0; i < items.size(); i++) {
			items.at(i)->Initialize();
		}
	}

	bool RedSlime::intersect(int x1, int x2, int y1, int y2)
	{
		//�U�����@�ǥ[��B��O�]���A�_��H��Bitmap������_��H������j�Ӧh�C
		if (isAlive()) {
			if (x2 >= _x + 20 && x1 <= _x + slime.Width() - 20 && y2 >= _y + 30 && y1 <= _y + slime.Height() - 15) {
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
	void RedSlime::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void RedSlime::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void RedSlime::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void RedSlime::SetMovingRight(bool b) {
		isMovingRight = b;
	}

	void RedSlime::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void RedSlime::movement(Maps *m)
	{
		int x = GetX1();
		int y = GetY1();
		int step_size = rand() % 3;
		if (distanceToHero() < 500) {
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
		
		
	}




	CRect * RedSlime::GetRect()
	{
		return &EnemyRect;
	}

	void RedSlime::attack()
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

	void RedSlime::attackShow(Maps * m)
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
