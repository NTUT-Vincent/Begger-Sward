/*
 * mygame.h: ���ɮ��x�C��������class��interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

class Map
{
public:
	virtual bool isEmpty(int x, int y) const = 0;
	virtual void addSX(int n) {};
	virtual void addSY(int n) {};
};

class BattleMap: public Map
{
public:
	BattleMap() {
		sx = -200;
		sy = -200;
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				if (i < 3 || i >11 || j < 5 || j > 10) {
					map[i][j] = 1;
				}
				else
				{
					map[i][j] = 0;
				}
			}
		}
		map[3][5] = map[3][6] = map[4][5] = map[5][4] = 1;
		map[4][10] = map[3][10] = map[3][9] = 1;
		map[11][5] = map[10][5] = map[11][6] = map[11][10] = map[10][10] = map[11][9] = 1;
	}

	bool isEmpty(int x, int y) const
	{
		int gx = x / 61;
		int gy = y / 64;
		if (map[gx][gy] == 0) {
			return true;
		}
		return false;
	}

	void OnMove() {
		
	}

	void LoadBitmap() {
		firstmap.LoadBitmap(IDB_MAP1);
	}

	void OnShow() {
		firstmap.SetTopLeft(sx, sy);
		firstmap.ShowBitmap();
	}


	void addSX(int n) override
	{
		sx += n;
	}

	void addSY(int n) override
	{
		sy += n;
	}

private:
	CMovingBitmap firstmap;
	int map[18][16];
	int sx , sy;							//�a�ϳ̥��W�����y��
	int stage_left, stage_top;			
};

class Player
{
public:
	Player();
	void LoadBitmap();
	void OnShow();
	void OnMove(Map *m);
	int getX();
	int getY();
	void Initialize();
	void SetMovingDown(bool b);
	void SetMovingUp(bool b);
	void SetMovingLeft(bool b);
	void SetMovingRight(bool b);
private:
	CMovingBitmap player;
	int x, y;
	bool isMovingRight;
	bool isMovingLeft;
	bool isMovingUp;
	bool isMovingDown;

};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap logo;								// csie��logo
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const int		NUMBALLS;	// �y���`��
		BattleMap		first_stage_map;
		Player			player1;
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
		CBall			*ball;		// �y���}�C
		CMovingBitmap	corner;		// ������
		CEraser			eraser;		// ��l
		CInteger		hits_left;	// �ѤU��������
		CBouncingBall   bball;		// ���мu�����y
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
	};

}