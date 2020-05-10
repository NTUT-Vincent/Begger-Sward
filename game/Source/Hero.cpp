#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "Maps.h"
#include "BloodBar.h"
#include "Util.h"
#include "Attack.h"
#define HMS HERO_MOVE_SPEED


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	Hero::Hero() : Character("Hero")
	{
		/*x = 480;
		y = 480;
		hp = 1200;
		attack = 20;
		skillTimes = 0;*/
		for (int i = 0; i < 6; i++) {
			items.push_back(nullptr);
		}
	}

	Hero::~Hero() {
		for (vector<Item*>::iterator it_i = items.begin(); it_i != items.end(); ++it_i) {
			delete *it_i;
			
		}
	}

	void Hero::LoadBitmap()
	{
		heroL.LoadBitmap(IDB_HERO_L, RGB(0, 0, 0));
		heroR.LoadBitmap(IDB_HERO_R, RGB(0, 0, 0));
		blood_bar.loadBloodBar();
		//�V�����ʵe
		char *filename1[6] = { ".\\bitmaps\\walkingL1.bmp",".\\bitmaps\\walkingL2.bmp",".\\bitmaps\\walkingL3.bmp",".\\bitmaps\\walkingL4.bmp", ".\\bitmaps\\walkingL3.bmp", ".\\bitmaps\\walkingL2.bmp" };
		for (int i = 0; i < 6; i++)	// ���J�ʵe(��6�i�ϧκc��)
			walkingLeft.AddBitmap(filename1[i], RGB(0, 0, 0));
		//�V�k���ʵe
		char *filename2[6] = { ".\\bitmaps\\walkingR1.bmp",".\\bitmaps\\walkingR2.bmp",".\\bitmaps\\walkingR3.bmp",".\\bitmaps\\walkingR4.bmp", ".\\bitmaps\\walkingR3.bmp", ".\\bitmaps\\walkingR2.bmp" };
		for (int i = 0; i < 6; i++)	// ���J�ʵe(��6�i�ϧκc��)
			walkingRight.AddBitmap(filename2[i], RGB(0, 0, 0));
		RectHero = heroL.ReturnCRect();
		//E�ʵe
		char *filenameW[8] = { ".\\bitmaps\\Clock1.bmp",".\\bitmaps\\Clock2.bmp",".\\bitmaps\\Clock3.bmp",".\\bitmaps\\Clock4.bmp", ".\\bitmaps\\Clock5.bmp", ".\\bitmaps\\Clock6.bmp", ".\\bitmaps\\Clock7.bmp", ".\\bitmaps\\Clock8.bmp" };
		for (int i = 0; i < 6; i++)	// ���J�ʵe(��6�i�ϧκc��)
			skillE.AddBitmap(filenameW[i], RGB(0, 0, 0));
		skillE.SetDelayCount(2);
		//���\�ʵe(��)
		normalAttackL.AddBitmap(IDB_COUNTER1, RGB(0, 0, 0));
		normalAttackL.AddBitmap(IDB_COUNTER2, RGB(0, 0, 0));
		normalAttackL.AddBitmap(IDB_COUNTER3, RGB(0, 0, 0));
		normalAttackL.SetDelayCount(5);
		//���\�ʵe(�k)
		normalAttackR.AddBitmap(IDB_CLOCK1, RGB(0, 0, 0));
		normalAttackR.AddBitmap(IDB_CLOCK2, RGB(0, 0, 0));
		normalAttackR.AddBitmap(IDB_CLOCK3, RGB(0, 0, 0));
		normalAttackR.SetDelayCount(5);
		//Q
		q_attack.loadBitmap();
	}

	void Hero::OnMove(Maps * m, vector<Enemy*> * enemys) {
		if (isMovingLeft && m->isEmpty(x - HMS, y) && m->isEmpty(x - HMS, GetY2()-10))
		{
			m->addSX(HMS);
			x -= HMS;
		}

		if (isMovingRight && m->isEmpty(GetX2() + HMS, y) && m->isEmpty(GetX2() + HMS, GetY2()-10))
		{
			m->addSX(-HMS);
			x += HMS;
		}
		if (isMovingUp && m->isEmpty(x+10, y - HMS) && m->isEmpty(GetX2()-10, y - HMS))
		{
			m->addSY(HMS);
			y -= HMS;
		}

		if (isMovingDown && m->isEmpty(x+10, GetY2() + HMS) && m->isEmpty(GetX2()-10, GetY2() + HMS))
		{
			m->addSY(-HMS);
			y += HMS;
		}
		if (gonnaBleeding(enemys, GetX1(), GetX2(), GetY1(), GetY2()))
		{
			//hp -= 10;
		}

		m->getHeroX(x);
		m->getHeroY(y);
		walkingLeft.OnMove();
		walkingRight.OnMove();
		skillEMove();
		skillQMove(m);
		normalAttackMove();

	}

	void Hero::OnShow(Maps *m)
	{
		blood_bar.setXY(x - 10, y - 10);
		blood_bar.showBloodBar(m, hp);
		if (isUsingSkill()) { 
			normalAttackShow(m);
			skillEShow();
			skillQShow(m);
		}
		else {
			heroShow(m);
		}
		showHeroStatus();
	}

	int Hero::GetX1() {
		return x;
	}

	int Hero::GetY1() {
		return y;
	}

	int Hero::GetX2()
	{
		return x + heroR.Width();
	}

	int Hero::GetY2()
	{
		return y + heroR.Height();
	}

	int Hero::GetQCoolDown()
	{
		return skill_q_cool_down;
	}

	int Hero::GetECoolDown()
	{
		return skill_e_cool_down;
	}

	int Hero::getHP()
	{
		return hp;
	}

	int Hero::getFullHP()
	{
		return blood_bar.getFullHP();
	}

	int Hero::get_attack_fire()
	{
		return attack_fire;
	}

	int Hero::get_attack_ice()
	{
		return attack_ice;
	}

	int Hero::get_attack_plant()
	{
		return attack_plant;
	}

	ELEMENT_ATTRIBUTE Hero::getCurrentAttribute()
	{
		return _attribute;
	}

	vector<Item*>* Hero::getItemsOfPlayer()
	{
		return &items;
	}

	void Hero::Initialize() {
		x = 480;
		y = 480;
		hp = 1200;
		attack_fire = SKILL_EVO_TVALUE; //�ɧڴ��@�Uflame�A���I��^�ӡC
		attack_ice = 20;
		attack_plant = 20;
		skillTimes = 0;
		isMovingDown = isMovingUp = isMovingLeft = isMovingRight = isAttack = false;
		isUsingA = isUsingQ = isUsingW = isUsingE = isUsingR = false;
		blood_bar.setFullHP(hp);
		walkingLeft.SetDelayCount(5);
		walkingRight.SetDelayCount(5);
		skill_e_cool_down = skill_q_cool_down = 0;
		_attribute = FIRE;
		for (int i = 0; i < 6; i++) {
			items.at(i) = nullptr;
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////
	
	void Hero::SetMovingDown(bool b) {
		isMovingDown = b;
		directionUD = 1;
	}

	void Hero::SetMovingUp(bool b) {
		isMovingUp = b;
		directionUD = 0;
	}

	void Hero::SetMovingLeft(bool b) {
		isMovingLeft = b;
		directionLR = 0;
	}

	void Hero::SetMovingRight(bool b) {
		isMovingRight = b;
		directionLR = 1;
	}

	void Hero::SetXY(int num_x, int num_y)
	{
		x = num_x;
		y = num_y;
	}
	
	/////////////////////////////////////////////////////////////////////////////
	
	void Hero::SetUsingA(bool b)
	{
		if (!isUsingSkill()) {
			if (b) {
				CAudio::Instance()->Play(AUDIO_SWORD);
			}

			isUsingA = b;
		}
	}
	
	void Hero::SetUsingQ(bool b)
	{
		if (!isUsingSkill() && skill_q_cool_down <= 0) {
			skill_q_cool_down = 60;
			if (b) {
				skillQ();
				CAudio::Instance()->Play(AUDIO_FIRE);
			}
			isUsingQ = b;
		}
	}
	
	void Hero::SetUsingW(bool b)
	{
		if (!isUsingSkill()) {
			isUsingW = b;
		}
	}
	
	void Hero::SetUsingE(bool b)
	{
		if (!isUsingSkill() && skill_e_cool_down <= 0) {
			skill_e_cool_down = 150;
			if (b) {
				CAudio::Instance()->Play(AUDIO_SKILLE);
			}
			isUsingE = b;
		}
	}
	
	void Hero::SetUsingR(bool b)
	{
		if (!isUsingSkill()) {
			isUsingR = b;
		}
	}

	void Hero::SetElementAttribute(ELEMENT_ATTRIBUTE e)
	{
		_attribute = e;
	}

	void Hero::SetAllCoolDownToZero()
	{
		skill_q_cool_down = skill_e_cool_down = 0;
	}
	
	/////////////////////////////////////////////////////////////////////////////
	
	bool Hero::gonnaBleeding(vector<Enemy*> * enemys, int x1, int x2, int y1, int y2)
	{
		int attack = 0;
		if (_attribute == FIRE) {
			attack = -1*attack_fire;
		}
		if (_attribute == ICE) {
			attack = -1*attack_ice;
		}
		if (_attribute == PLANT) {
			attack = -1*attack_plant;
		}
		//attack = -10000;
		for (unsigned i = 0; i < enemys->size(); i++)
		{
			if (enemys->at(i)->intersect(x1, x2, y1, y2))
			{
				return true;
			}
			//���\
			if (enemys->at(i)->intersect(x1 - 30, x2 - 30, y1 + 10, y2) && directionLR == 0 && isUsingA)
			{
				enemys->at(i)->offsetHP(attack, _attribute);
			}
			if (enemys->at(i)->intersect(x1 + 30, x2 + 30, y1 + 10, y2) && directionLR == 1 && isUsingA)
			{
				enemys->at(i)->offsetHP(attack, _attribute);
			}
			//Q�ޯ�
			if (enemys->at(i)->intersect(q_attack.getX1(), q_attack.getX2(), q_attack.getY1(), q_attack.getY2()) && isUsingQ)
			{
				if (attack_fire >= SKILL_EVO_TVALUE && _attribute == FIRE)
					enemys->at(i)->offsetHP(attack*2, _attribute);
				enemys->at(i)->offsetHP(attack, _attribute);
			}
			//E�ޯ�
			if (enemys->at(i)->intersect(x1 - 30, x2 + 30, y1 - 30, y2 + 30) && isUsingE)
			{
				enemys->at(i)->offsetHP(attack, _attribute);
			}
		}
		return false;
	}

	void Hero::offsetHp(int n)
	{
		hp -= n;
	}

	void Hero::addHp(int n)
	{
		hp += n;
	}

	void Hero::addAttack(int n, ELEMENT_ATTRIBUTE attribute)
	{
		if (attribute == FIRE) {
			attack_fire += n;
		}
		if (attribute == ICE) {
			attack_ice += n;
		}
		if (attribute == PLANT) {
			attack_plant += n;
		}
	}

	void Hero::addItem(Item * item)
	{
		int n = -1;
		for (int i = 5; i >= 0; i--) {
			if (items.at(i) == nullptr) {
				n = i;
			}
		}
		if (n != -1 && items.at(n) == nullptr) {
			items.at(n) = item;
		}
		else {
			delete item;
		}

	}

	/////////////////////////////////////////////////////////////////////////////

	bool Hero::isMoving()
	{
		if (isMovingDown || isMovingLeft || isMovingRight || isMovingUp) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Hero::isAlive()
	{
		if (hp > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Hero::isInFinishArea(Maps * m)
	{
		if (m->inFinishArea(x, y)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Hero::isUsingSkill()
	{
		if (isUsingA || isUsingQ || isUsingE ) {
			return true;
		}
		return false;
	}

	void Hero::heroShow(Maps *m)
	{
		if (directionLR == 0)
		{
			if (isMoving()) {
				walkingLeft.SetTopLeft(m->screenX(x), m->screenY(y));
				walkingLeft.OnShow();
			}
			else {
				heroL.SetTopLeft(m->screenX(x), m->screenY(y));
				heroL.ShowBitmap();
			}

		}
		else
		{
			if (isMoving()) {
				walkingRight.SetTopLeft(m->screenX(x), m->screenY(y));
				walkingRight.OnShow();
			}
			else {
				heroR.SetTopLeft(m->screenX(x), m->screenY(y));
				heroR.ShowBitmap();
			}

		}
	}

	/////////////////////////////////////////////////////////////////////////////

	void Hero::normalAttackMove()
	{
		normalAttackL.OnMove();
		normalAttackR.OnMove();
		if (!isUsingA) {
			normalAttackL.Reset();			//�S���Χޯ઺�ɭ� �nReset CAnimation�A�U���~�|�q�Ĥ@�i�϶]
			normalAttackR.Reset();
		}
	}

	void Hero::normalAttackShow(Maps *m)
	{
		if (directionLR == 0 && isUsingA) {
			normalAttackL.SetTopLeft(m->screenX(x) - 20, m->screenY(y) - 10);
			normalAttackL.OnShow();
			if (normalAttackL.IsFinalBitmap()) {
				isUsingA = false;
			}
		}
		if (directionLR == 1 && isUsingA) {
			normalAttackR.SetTopLeft(m->screenX(x) - 20, m->screenY(y) - 10);
			normalAttackR.OnShow();
			if (normalAttackR.IsFinalBitmap()) {
				isUsingA = false;
			}
		}
	}

	void Hero::showHeroStatus()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str,"Cool Down: Q:%d E:%d   HP: %d", skill_q_cool_down / 30,skill_e_cool_down / 30, hp);
		pDC->TextOut(0, 0, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC

	}

	void Hero::skillQ()
	{
		if (!isUsingSkill()) {
			q_attack.setXY(x, y);
			q_attack.setAttackIsFlying(true);
			if (directionLR == 0) {
				q_attack.setDirection(0);
			}
			if (directionLR == 1) {
				q_attack.setDirection(1);
			}
		}

	}

	void Hero::skillQMove(Maps *m)
	{
		if (isUsingQ) {
			q_attack.OnMove(m);
			q_attack.setXY(x, y);
		}
		if (skill_q_cool_down > 0) {
			skill_q_cool_down -= 1;
		}
		if (_attribute == FIRE) {
			q_attack.setAttackName(FIRE_BALL);
			if (attack_fire >= SKILL_EVO_TVALUE) {
				q_attack.setAttackName(FIRE_FLAME);
				if (!isUsingQ)
				{
					q_attack.resetAnimation(FIRE_FLAME);
				}
			}
		}
		if (_attribute == ICE) {
			q_attack.setAttackName(ICE_BALL);
		}
		if (_attribute == PLANT) {
			q_attack.setAttackName(GRASS_BALL);
		}
	}

	void Hero::skillQShow(Maps * m)
	{
		if (isUsingQ) {
			heroShow(m);
			q_attack.OnShow(m);
			skillTimes += 1;							//+1�N��]�F1/30��
			if (skillTimes > 20) {						//�w�p���L��2/3��
				isUsingQ = false;
				q_attack.setAttackIsFlying(false);
				skillTimes = 0;							//�]����ӧޯ��skillTime�]�^��0
			}
		}
	}

	void Hero::useItem(int n)
	{
		if (items.at(n - 1) != nullptr) {
			items.at(n - 1)->effect(this);
		}
		vector<Item*>::iterator it_i = items.begin();
		for (int i = 0; i < n - 1; i++) {
			++it_i;
		}
		delete *it_i;
		items.at(n - 1) = nullptr;
	}

	void Hero::skillEMove()
	{
		if (skill_e_cool_down > 0) {
			skill_e_cool_down -= 1;
		}
		skillE.OnMove();
		if (!isUsingE)
			skillE.Reset(); 
	}

	void Hero::skillEShow()
	{
		if (isUsingE) {
			skillE.SetTopLeft(280 - 25, 280 - 15);
			skillE.OnShow();
			if (skillE.IsFinalBitmap()) {
				skillTimes += 1;			//+1�N��]�F�@�^CAnimation
				if (skillTimes == 3) {
					skillTimes = 0;			//�]����ӧޯ��skillTime�]�^��0
					isUsingE = false;
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////

}
