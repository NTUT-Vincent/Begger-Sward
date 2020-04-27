#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Enemy.h"
#include "Enemy.h"
#include "Hero.h"
#include "Maps.h"
#include "Enemy.h"

namespace game_framework {

	Enemy::Enemy() : Character("scarecrow")
	{
		_x = 384;
		_y = 384;
		hp = 1200;
		attack = 0;
	}

	Enemy::Enemy(int x, int y, int monsterHp, string name, Hero *h) : Character(name)
	{
		_x = x;
		_y = y;
		ini_x = x;
		ini_y = y;
		hp = monsterHp;
		attack = 0;
		isAttacking = false;
		hero_on_map = h;
	}

	Enemy::~Enemy()
	{
	}

	void Enemy::SetMovingDown(bool b) {
		isMovingDown = b;
	}

	void Enemy::SetMovingUp(bool b) {
		isMovingUp = b;
	}

	void Enemy::SetMovingLeft(bool b) {
		isMovingLeft = b;
	}

	void Enemy::SetMovingRight(bool b) {
		isMovingRight = b;
	}

	void Enemy::SetXY(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void Enemy::offsetHP(int offset)
	{
		hp += offset;
	}

	bool Enemy::isAlive()
	{
		if (hp <= 0) {
			return false;
		}
		return true;
	}

	CRect * Enemy::GetRect()
	{
		return &EnemyRect;
	}

	bool Enemy::isAttack()
	{
		return isAttacking;
	}

}
