/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <algorithm>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "Character.h"
#include "Util.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
		//
		// �}�l���J���
		//
		logo.LoadBitmap(IDB_BEGGERSWORD);
		Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
		//
	}

	void CGameStateInit::OnBeginState()
	{
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_SPACE)
			GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
		else if (nChar == KEY_ESC)								// Demo �����C������k
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
	}

	void CGameStateInit::OnShow()
	{
		//
		// �K�Wlogo
		//
		logo.SetTopLeft((SIZE_X - logo.Width()) / 2, SIZE_Y / 8);
		logo.ShowBitmap();
		//
		// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
		//
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->TextOut(195, 180, "����W:�^���j�C");
		pDC->TextOut(155, 220, "This game is namely a crap.");
		//pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
		//if (ENABLE_GAME_PAUSE)
		//	pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
		pDC->TextOut(170, 260, "Press Space to continue.");
		pDC->TextOut(60, 420, "107820005 ���l�� 107820012 ����");
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}

	void CGameStateOver::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
		//
		// �}�l���J���
		//
		Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// �̲׶i�׬�100%
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, "Game Over ! (%d)", counter / 30);
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g), NUMBALLS(28)
	{
		ball = new CBall[NUMBALLS];
		enemys1_1.push_back(new Scarecrow(400, 450, &player1));
		enemys1_1.push_back(new Scarecrow(384, 384, &player1));
		enemys1_1.push_back(new Scarecrow(400, 200, &player1));
		enemys1_1.push_back(new Scarecrow(400, 600, &player1));
		enemys1_1.push_back(new Scarecrow(400, 500, &player1));
		enemys1_1.push_back(new Scarecrow(500, 550, &player1));
		enemys1_1.push_back(new GreenSlime(150, 300, &player1));
		enemys1_1.push_back(new GreenSlime(200, 500, &player1));
		enemys1_1.push_back(new GreenSlime(500, 500, &player1));
	}

	CGameStateRun::~CGameStateRun()
	{
		delete[] ball;
		for (vector<Enemy*>::iterator it_i = enemys1_1.begin(); it_i != enemys1_1.end(); ++it_i) {
			delete *it_i;
		}
	}

	void CGameStateRun::OnBeginState()
	{
		const int BALL_GAP = 90;
		const int BALL_XY_OFFSET = 45;
		const int BALL_PER_ROW = 7;
		const int HITS_LEFT = 10;
		const int HITS_LEFT_X = 590;
		const int HITS_LEFT_Y = 0;
		const int BACKGROUND_X = 60;
		const int ANIMATION_SPEED = 15;
		for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
			int x_pos = i % BALL_PER_ROW;
			int y_pos = i / BALL_PER_ROW;
			ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
			ball[i].SetDelay(x_pos);
			ball[i].SetIsAlive(true);
		}
		eraser.Initialize();
		background.SetTopLeft(BACKGROUND_X, 0);				// �]�w�I�����_�l�y��
		help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
		hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
		hits_left.SetTopLeft(HITS_LEFT_X, HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
		CAudio::Instance()->Play(AUDIO_GOLDENWIND, true);			// ���� MIDI
		player1.Initialize();
		for (unsigned i = 0; i < enemys1_1.size(); i++) {
			enemys1_1[i]->Initialize();
		}
	}

	void CGameStateRun::OnMove()							// ���ʹC������
	{
		first_stage_map.OnMove();
		player1.OnMove(&first_stage_map, &enemys1_1);
		if (!player1.isAlive()) {
			GotoGameState(GAME_STATE_OVER);
		}
		//enemy1.OnMove(&first_stage_map);
		//first_stage_map.enemysOnMove();
		for (unsigned i = 0; i < enemys1_1.size(); i++) {
			enemys1_1[i]->OnMove(&first_stage_map);
		}
		//
		// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
		//
		// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
		//
		// ���ʭI���Ϫ��y��
		//
		if (background.Top() > SIZE_Y)
			background.SetTopLeft(60, -background.Height());
		background.SetTopLeft(background.Left(), background.Top() + 1);
		//
		// ���ʲy
		//
		int i;
		for (i = 0; i < NUMBALLS; i++)
			ball[i].OnMove();
		//
		// �������l
		//
		eraser.OnMove();
		//
		// �P�_���l�O�_�I��y
		//
		for (i = 0; i < NUMBALLS; i++)
			if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
				ball[i].SetIsAlive(false);
				hits_left.Add(-1);
				//
				// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
				//
				if (hits_left.GetInteger() <= 0) {
					CAudio::Instance()->Stop(AUDIO_GOLDENWIND);	// ���� MIDI
					GotoGameState(GAME_STATE_OVER);
				}
			}

		//
		// ���ʼu�����y
		//
		bball.OnMove();
		//�Ƨǳ��W��Enemy�̷�y�y��
		sort(enemys1_1.begin(), enemys1_1.end(), [](Enemy *a, Enemy *b) {return a->GetY1() < b->GetY1(); }); 
	}

	void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
		//
		// �}�l���J���
		//
		player1.LoadBitmap();
		//enemy1.LoadBitmap();
		for (unsigned i = 0; i < enemys1_1.size(); i++) {
			enemys1_1[i]->LoadBitmap();
		}
		//first_stage_map.enemysLoadBitmap();
		first_stage_map.LoadBitmap();
		int i;
		for (i = 0; i < NUMBALLS; i++)
			ball[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�
		eraser.LoadBitmap();
		background.LoadBitmap(IDB_BACKGROUND);					// ���J�I�����ϧ�
		//
		// ��������Loading�ʧ@�A�����i��
		//
		ShowInitProgress(50);
		Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// �~����J��L���
		//
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// ���J�������ϧ�
		corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
		corner.ShowBitmap(background);							// �Ncorner�K��background
		bball.LoadBitmap();										// ���J�ϧ�
		hits_left.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_GOLDENWIND, "sounds\\goldenwind.mp3");	// ���J�s��2���n��ntut.mid
		CAudio::Instance()->Load(AUDIO_SWORD, "sounds\\swing2.mp3");
		CAudio::Instance()->Load(AUDIO_FIRE, "sounds\\fireball.mp3");
		CAudio::Instance()->Load(AUDIO_SKILLE, "sounds\\swing4.mp3");
		CAudio::Instance()->Load(Audio_KNIFE,  "sounds\\knife.mp3");
		//
		// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		switch (nChar)
		{
		case KEY_LEFT: player1.SetMovingLeft(true); break;
		case KEY_RIGHT: player1.SetMovingRight(true); break;
		case KEY_UP: player1.SetMovingUp(true); break;
		case KEY_DOWN: player1.SetMovingDown(true); break;
		case KEY_A: player1.SetUsingA(true); break;
		case KEY_Q: 
			player1.SetUsingQ(true); 
			break;
		case KEY_W: player1.SetUsingW(true); break;
		case KEY_E: player1.SetUsingE(true); break;
		case KEY_R: player1.SetUsingR(true); break;
		default: return;
		}

		
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		switch (nChar)
		{
		case KEY_LEFT: player1.SetMovingLeft(false); break;
		case KEY_RIGHT: player1.SetMovingRight(false); break;
		case KEY_UP: player1.SetMovingUp(false); break;
		case KEY_DOWN: player1.SetMovingDown(false); break;
		default: return;
		}
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		//eraser.SetMovingLeft(true);
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		//eraser.SetMovingLeft(false);
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		eraser.SetMovingRight(true);
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		eraser.SetMovingRight(false);
	}

	void CGameStateRun::OnShow()
	{
		//
		//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
		//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
		//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
		//
		//
		//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
		//
		//ackground.ShowBitmap();			// �K�W�I����
		first_stage_map.OnShow();
		//help.ShowBitmap();					// �K�W������
		//hits_left.ShowBitmap();
		//for (int i=0; i < NUMBALLS; i++)
			//ball[i].OnShow();				// �K�W��i���y
		//bball.OnShow();						// �K�W�u�����y
		//eraser.OnShow();					// �K�W���l
		//
		//  �K�W���W�Υk�U��������
		//
		corner.SetTopLeft(0, 0);
		//corner.ShowBitmap();
		corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
		//corner.ShowBitmap();
		//enemy1.OnShow(&first_stage_map);
		//first_stage_map.enemysOnShow();
		int hero_position = -1;									//�p�GHero���y�Ф�̤W�����ĤH��W�� position = -1					
		for (unsigned i = 0; i < enemys1_1.size(); i++) {
			if (player1.GetY2() > enemys1_1[i]->GetY2()) {		//�v�@���Y�y�СA���Hero����m�b����өǪ�����
				hero_position = i;
			}
		}
		if (hero_position == -1) {
			player1.OnShow(&first_stage_map);
		}
		for (unsigned i = 0; i < enemys1_1.size(); i++) {
			enemys1_1[i]->OnShow(&first_stage_map);
			if (i == hero_position) {							//�p�Gshow�������쪺��m�Ashow hero
				player1.OnShow(&first_stage_map);
			}

		}

	}

};


