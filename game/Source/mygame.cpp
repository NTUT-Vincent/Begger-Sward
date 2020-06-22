#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <algorithm>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "Character.h"
#include "BlueSlime.h"
#include "GreenSlime.h"
#include "RedSlime.h"
#include "RedGoblin.h"
#include "IceBird.h"
#include "Util.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// mygame.cpp: 本檔案儲遊戲本身的class的implementation					   //
	// 這個class為遊戲的遊戲開頭畫面物件										   //
	/////////////////////////////////////////////////////////////////////////////
	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}
	void CGameStateInit::OnInit()
	{
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		// 等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		ShowInitProgress(0);	// 一開始的loading進度為0%
		// 開始載入資料
		CAudio::Instance()->Load(AUDIO_CHOOSE, "sounds\\choose.mp3");	
		goto_status = isHelp = isAbout = 0;
		logo.LoadBitmap(IDB_STARTBACKGROUND);
		selection.LoadBitmap(".\\bitmaps\\choose.bmp");
		help.LoadBitmap(".\\RES\\help.bmp");
		about.LoadBitmap(".\\RES\\credits.bmp");
		choose.LoadBitmap(".\\Bitmaps\\choose.bmp", RGB(0, 0, 0));
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	}
	void CGameStateInit::OnBeginState()
	{
	}
	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_UP && goto_status > 0)
		{
			CAudio::Instance()->Play(AUDIO_CHOOSE, false);
			goto_status -= 1;
		}
		if (nChar == KEY_DOWN && goto_status < 2)
		{
			CAudio::Instance()->Play(AUDIO_CHOOSE, false);
			goto_status += 1;
		}
		if (nChar == KEY_SPACE)
		{
			if (goto_status == 0)
				GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
			else if (goto_status == 1)
			{
				if (isHelp == 0)
				{
					isHelp = 1;
				}
				else
					isHelp = 0;
			}
			else if (goto_status == 2)
			{
				if (isAbout == 0)
				{
					isAbout = 1;
				}
				else
					isAbout = 0;
			}	
		}
		else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
	}
	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
	}
	void CGameStateInit::OnShow()
	{
		//
		// 貼上logo
		//
		logo.SetTopLeft(0, 0);
		logo.ShowBitmap();
		if (isHelp)
		{
			help.SetTopLeft(0, 0);
			help.ShowBitmap();
		}
		if (isAbout)
		{
			about.SetTopLeft(0, 0);
			about.ShowBitmap();
		}
		if (!isAbout && !isHelp)
		{
			if (goto_status == 0)
			{
				choose.SetTopLeft(200, 300);
			}
			if (goto_status == 1)
			{
				choose.SetTopLeft(200, 352);
			}
			if (goto_status == 2)
			{
				choose.SetTopLeft(200, 396);
			}
			choose.ShowBitmap();
		}
		//
		// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
		//
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////
	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}
	void CGameStateOver::OnMove()
	{
		counter--;
		gameover.OnMove();
		if (counter < 0)
		{
			CAudio::Instance()->Stop(AUDIO_GOLDENWIND);
			GotoGameState(GAME_STATE_INIT);
		}
	}
	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 3; // 4 seconds
		CAudio::Instance()->Play(AUDIO_GAMEOVER, false);
	}
	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		// 最終進度為100%
		//
		ShowInitProgress(100);
		char *filename_gameover[15] = { ".\\bitmaps\\GAME_OVER_0.bmp",".\\bitmaps\\GAME_OVER_1.bmp",".\\bitmaps\\GAME_OVER_2.bmp",".\\bitmaps\\GAME_OVER_3.bmp",".\\bitmaps\\GAME_OVER_4.bmp",".\\bitmaps\\GAME_OVER_5.bmp",".\\bitmaps\\GAME_OVER_6.bmp",".\\bitmaps\\GAME_OVER_7.bmp",".\\bitmaps\\GAME_OVER_8.bmp",".\\bitmaps\\GAME_OVER_9.bmp",".\\bitmaps\\GAME_OVER_10.bmp",".\\bitmaps\\GAME_OVER_11.bmp",".\\bitmaps\\GAME_OVER_12.bmp",".\\bitmaps\\GAME_OVER_13.bmp",".\\bitmaps\\GAME_OVER_14.bmp",};
		for (int i = 0; i < 15; i++)
			gameover.AddBitmap(filename_gameover[i], RGB(0, 0, 0));
		gameover.SetDelayCount(6);
		CAudio::Instance()->Load(AUDIO_GAMEOVER, "sounds\\gameover.mp3");
	}
	void CGameStateOver::OnShow()
	{
			gameover.SetTopLeft(0, 100);
			gameover.OnShow();
	}
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////
	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g), NUMBALLS(28)
	{
		current_stage = STAGE_1_1;
		enemys1_1.push_back(new Scarecrow(400, 450, &player1));
		enemys1_1.push_back(new Box(256, 384, &player1));
		enemys1_2.push_back(new RedGoblin(300, 450, &player1));
		enemys1_2.push_back(new RedGoblin(300, 550, &player1));
		for (int i = 0; i < 3; i++) {
			enemys1_1.push_back(new Box((64 * 3 * i) + 128, 448, &player1));
			enemys1_2.push_back(new Box((64 * 3*i)+128, 448, &player1));
			enemys1_4.push_back(new Box((64 * 3 * i) + 128, 448, &player1));
			enemys2_1.push_back(new Box((64 * 3 * i) + 128, 448, &player1));
			enemys2_2.push_back(new Box((64 * 3 * i) + 128, 448, &player1));
		}
		for (int i = 0; i < 2; i++) {
			enemys1_2.push_back(new RedSlime((64 * 3*i)+400, 448, &player1));
		}
		for (int i = 0; i < 2; i++) {
			enemys1_2.push_back(new GreenSlime((64 * 3 * i) + 300, 400, &player1));
		}
		for (int i = 0; i < 2; i++) {
			enemys1_2.push_back(new BlueSlime((64 * 3 * i) + 200, 496, &player1));
		}
		enemys1_3.push_back(new RedGoblin(300, 550, &player1));
		for (int i = 0; i < 5; i++) {
			/*enemys1_4.push_back(new GreenSlime(200, (300 + 64*i), &player1));
			enemys1_4.push_back(new RedSlime(900, (300 + 64 * i), &player1));
			enemys1_4.push_back(new BlueSlime( (200 + 64*i), 900, &player1));
			enemys1_4.push_back(new Scarecrow(500, (200 + 64*i), &player1));*/
		}
		enemys1_4.push_back(new ABoss(800, 300, &player1));
		enemys2_1.push_back(new RedSlime(600, 600, &player1));
		enemys2_1.push_back(new RedGoblin(320, 320, &player1));
		enemys2_1.push_back(new BlueGoblin(896, 640, &player1));
		enemys2_1.push_back(new GreenSlime(500, 600, &player1));
		enemys2_2.push_back(new GreenGoblin(192, 384, &player1));
		enemys2_2.push_back(new BlueSlime(200, 386, &player1));
		enemys2_2.push_back(new RedSlime(600, 600, &player1));
		enemys2_2.push_back(new BlueGoblin(960, 640, &player1));
		enemys2_2.push_back(new RedGoblin(640, 192, &player1));
		enemys2_2.push_back(new GreenGoblin(640, 832, &player1));
		enemys2_3.push_back(new GreenGoblin(192, 384, &player1));
		enemys2_3.push_back(new BlueSlime(200, 386, &player1));
		enemys2_3.push_back(new RedSlime(600, 600, &player1));
		enemys2_3.push_back(new BlueGoblin(960, 640, &player1));
		enemys2_4.push_back(new IceBird(600, 500, &player1));
		enemys2_4.push_back(new BlueSlime(500, 500, &player1));
	}
	CGameStateRun::~CGameStateRun()
	{
		for (vector<Enemy*>::iterator it_i = enemys1_1.begin(); it_i != enemys1_1.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys1_2.begin(); it_i != enemys1_2.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys1_3.begin(); it_i != enemys1_3.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys1_4.begin(); it_i != enemys1_4.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys2_1.begin(); it_i != enemys2_1.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys2_2.begin(); it_i != enemys2_2.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys2_3.begin(); it_i != enemys2_3.end(); ++it_i) {
			delete *it_i;
		}
		for (vector<Enemy*>::iterator it_i = enemys2_4.begin(); it_i != enemys2_4.end(); ++it_i) {
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
		isAllLevelPass = all_level_pass_count = 0;
		CAudio::Instance()->Play(AUDIO_GOLDENWIND, true);			// 撥放 MIDI
		player1.Initialize();
		//第一關怪物
		for (unsigned i = 0; i < enemys1_1.size(); i++) 
		{
			enemys1_1[i]->Initialize();
		}
		//第二關怪物
		for (unsigned i = 0; i < enemys1_2.size(); i++)
		{
			enemys1_2[i]->Initialize();
		}
		//1_3怪物
		for (unsigned i = 0; i < enemys1_3.size(); i++)
		{
			enemys1_3[i]->Initialize();
		}
		//第六關怪物
		for (unsigned i = 0; i < enemys1_4.size(); i++) 
		{
			enemys1_4[i]->Initialize();
		}
		//2_1怪物
		for (unsigned i = 0; i < enemys2_1.size(); i++)
		{
			enemys2_1[i]->Initialize();
		}
		//2_2怪物
		for (unsigned i = 0; i < enemys2_2.size(); i++)
		{
			enemys2_2[i]->Initialize();
		}
		//2_3怪物
		for (unsigned i = 0; i < enemys2_3.size(); i++) 
		{
			enemys2_3[i]->Initialize();
		}
		//2_4怪物
		for (unsigned i = 0; i < enemys2_4.size(); i++)
		{
			enemys2_4[i]->Initialize();
		}
		current_stage = STAGE_1_1;
		map_stg1_1.Initialize();
		map_stg1_4.Initialize();
		map_stg1_2.Initialize();
		map_stg1_3.Initialize();
		map_stg2_1.Initialize();
		map_stg2_2.Initialize();
		map_stg2_3.Initialize();
		map_stg2_4.Initialize();
		player_status.Initialize(&player1);
	}
	void CGameStateRun::stage_process_move(Maps & stage_map, Hero & player, vector<Enemy*> & enemy_array, STAGE next_stage)
	{
		//王關會有不一樣的音樂
		if ((current_stage == STAGE_1_4 || current_stage == STAGE_2_4) && change_song)
		{
			CAudio::Instance()->Stop(AUDIO_GOLDENWIND);			// 撥放 MIDI
			CAudio::Instance()->Play(AUDIO_AWAKEN, true);			// 撥放 MIDI
			change_song = 0;
		}
		if (!(current_stage == STAGE_1_4 || current_stage == STAGE_2_4) && change_song )
		{
			CAudio::Instance()->Stop(AUDIO_AWAKEN);			// 撥放 MIDI
			CAudio::Instance()->Play(AUDIO_GOLDENWIND);			// 撥放 MIDI
			change_song = 0;
		}
		player.OnMove(&stage_map, &enemy_array);
		for (unsigned i = 0; i < enemy_array.size(); i++)
		{
			enemy_array[i]->OnMove(&stage_map);
		}
		sort(enemy_array.begin(), enemy_array.end(), [](Enemy *a, Enemy *b) {return a->GetY2() < b->GetY2(); });
		int next_x, next_y = 0;
		switch (next_stage)
		{
		case STAGE_1_2: next_x = 480; next_y = 480;
			break;
		case STAGE_1_3: next_x = 480; next_y = 480;
			break;
		case STAGE_1_4: next_x = 780; next_y = 1470;
			break;
		case STAGE_2_1: next_x = 480; next_y = 480;
			break;
		case STAGE_2_2: next_x = 480; next_y = 480;
			break;
		case STAGE_2_3: next_x = 480; next_y = 480;
			break;
		case STAGE_2_4: next_x = 480; next_y = 480;
			break;
		}
		stage_map.setClear(allEnemyDie(enemy_array));
		int random_scold = rand() % 100;
		//如果打所有怪物打死且主角進入下一關的區域
		if (allEnemyDie(enemy_array) && player.isInFinishArea(&stage_map))
		{
			//怪物被主角消滅，主角覺得怪物太爛了於是大罵一聲，爛!
			if (random_scold <= 40)
				CAudio::Instance()->Play(AUDIO_SCOLD, false);
			//若通關播放通關畫面6秒
			if (next_stage == CONGRATULATION)
			{
				all_level_pass_count = 180;
				isAllLevelPass = 1;
			}
			if (current_stage == STAGE_1_3 || current_stage == STAGE_2_3 || current_stage == STAGE_1_4)
				change_song = 1;
			current_stage = next_stage;
			player.SetXY(next_x, next_y);
		}
	}

	void CGameStateRun::OnMove()							// 移動遊戲元素
	{
		switch (current_stage)
		{
			case STAGE_1_1:
				stage_process_move(map_stg1_1, player1, enemys1_1, STAGE_1_2);
				break;
			case STAGE_1_2:
				stage_process_move(map_stg1_2, player1, enemys1_2, STAGE_1_3);
				break;
			case STAGE_1_3:
				stage_process_move(map_stg1_3, player1, enemys1_3, STAGE_1_4);
				break;
			case STAGE_1_4:
				stage_process_move(map_stg1_4, player1, enemys1_4, STAGE_2_1);
				break;
			case STAGE_2_1:
				stage_process_move(map_stg2_1, player1, enemys2_1, STAGE_2_2);
				break;
			case STAGE_2_2:
				stage_process_move(map_stg2_2, player1, enemys2_2, STAGE_2_3);
				break;
			case STAGE_2_3:
				stage_process_move(map_stg2_3, player1, enemys2_3, STAGE_2_4);
				break;
			case STAGE_2_4:
				stage_process_move(map_stg2_4, player1, enemys2_4, CONGRATULATION);
				break;
		}
		//如果主角死了
		if (!player1.isAlive()) 
		{
			GotoGameState(GAME_STATE_OVER);
			for (int i = 0; i < 6; i++)
			{
				player1.useItem(i + 1);
			}
		}
		if (isAllLevelPass && all_level_pass_count>= 0)
		{
			all_level_pass_count -= 1;
			CAudio::Instance()->Play(AUDIO_ICEBIRD_DIE, false);
		}
		if (isAllLevelPass && all_level_pass_count <= 0)
		{
			for (int i = 0; i < 6; i++)
			{
				player1.useItem(i + 1);
			}
			GotoGameState(GAME_STATE_INIT);
		}
		if (background.Top() > SIZE_Y)
			background.SetTopLeft(60, -background.Height());
		background.SetTopLeft(background.Left(), background.Top() + 1);
	}
	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//
		player1.LoadBitmap();
		player_status.loadPlayerStatus();
		change_song = 0;
		//1-1怪物
		for (unsigned i = 0; i < enemys1_1.size(); i++) 
		{
			enemys1_1[i]->LoadBitmap();
		}
		//1-2怪物
		for (unsigned i = 0; i < enemys1_2.size(); i++)
		{
			enemys1_2[i]->LoadBitmap();
		}
		//1_3怪物
		for (unsigned i = 0; i < enemys1_3.size(); i++)
		{
			enemys1_3[i]->LoadBitmap();
		}
		//1-4怪物
		for (unsigned i = 0; i < enemys1_4.size(); i++)
		{
			enemys1_4[i]->LoadBitmap();
		}
		//2_1怪物
		for (unsigned i = 0; i < enemys2_1.size(); i++)
		{
			enemys2_1[i]->LoadBitmap();
		}
		//2_2怪物
		for (unsigned i = 0; i < enemys2_2.size(); i++)
		{
			enemys2_2[i]->LoadBitmap();
		}
		//2_3怪物
		for (unsigned i = 0; i < enemys2_3.size(); i++)
		{
			enemys2_3[i]->LoadBitmap();
		}
		//2_4怪物
		for (unsigned i = 0; i < enemys2_4.size(); i++) 
		{
			enemys2_4[i]->LoadBitmap();
		}
		background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形
		map_stg1_1.LoadBitmap();
		map_stg1_2.LoadBitmap();
		map_stg1_3.LoadBitmap();
		map_stg1_4.LoadBitmap();
		map_stg2_1.LoadBitmap();
		map_stg2_2.LoadBitmap();
		map_stg2_3.LoadBitmap();
		map_stg2_4.LoadBitmap();
		//
		// 完成部分Loading動作，提高進度
		//
		ShowInitProgress(50);
		//
		// 繼續載入其他資料
		//
		help.LoadBitmap(IDB_HELP, RGB(255, 255, 255));				// 載入說明的圖形
		you_win.LoadBitmap(".\\RES\\You_win.bmp");
		corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
		corner.ShowBitmap(background);							// 將corner貼到background
		hits_left.LoadBitmap();
		CAudio::Instance()->Load(AUDIO_GOLDENWIND, "sounds\\goldenwind.mp3");	// 載入編號2的聲音ntut.mid
		CAudio::Instance()->Load(AUDIO_SWORD, "sounds\\swing2.mp3");
		CAudio::Instance()->Load(AUDIO_FIRE, "sounds\\fireball.mp3");
		CAudio::Instance()->Load(AUDIO_SKILLE, "sounds\\swing4.mp3");
		CAudio::Instance()->Load(AUDIO_SKILLR_1, "sounds\\skillR_1.mp3");
		CAudio::Instance()->Load(AUDIO_SKILLR_2, "sounds\\skillR_2.mp3");
		CAudio::Instance()->Load(Audio_KNIFE,  "sounds\\knife2.mp3");
		CAudio::Instance()->Load(AUDIO_ICE, "sounds\\iceball.mp3");
		CAudio::Instance()->Load(AUDIO_HITTING, "sounds\\hitting4.mp3");
		CAudio::Instance()->Load(AUDIO_GRASSBALL, "sounds\\grassball.mp3");
		CAudio::Instance()->Load(AUDIO_BEGGER, "sounds\\begger.mp3");
		CAudio::Instance()->Load(AUDIO_AWAKEN, "sounds\\awaken.mp3");
		CAudio::Instance()->Load(AUDIO_DAMAGE1, "sounds\\damage1.mp3");
		CAudio::Instance()->Load(AUDIO_ABOSS_WALK, "sounds\\footsteps_of_a_giant.mp3");
		CAudio::Instance()->Load(AUDIO_ABOSS_PREPARE, "sounds\\ABoss_prepare.mp3");
		CAudio::Instance()->Load(AUDIO_GOODFLASH, "sounds\\goodflash.mp3");
		CAudio::Instance()->Load(AUDIO_BADFLASH, "sounds\\badflash.mp3");
		CAudio::Instance()->Load(AUDIO_ICEBIRD_DIE, "sounds\\icebirddie.mp3");
		CAudio::Instance()->Load(AUDIO_BEING_ATTACKED, "sounds\\being_attacked.mp3");
		CAudio::Instance()->Load(AUDIO_SCOLD, "sounds\\scold.mp3");
		CAudio::Instance()->Load(AUDIO_SHOE, "sounds\\shoe.mp3");
		CAudio::Instance()->Load(AUDIO_SING, "sounds\\sing.mp3");
		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		int n = rand() % 3;
		switch (nChar)
		{
		case KEY_LEFT: player1.SetMovingLeft(true); break;
		case KEY_RIGHT: player1.SetMovingRight(true); break;
		case KEY_UP: player1.SetMovingUp(true); break;
		case KEY_DOWN: player1.SetMovingDown(true); break;
		case NUM_0:
			if(n == 0)
				player1.SetElementAttribute(FIRE);
			if (n == 1)
				player1.SetElementAttribute(ICE);
			if (n == 2)
				player1.SetElementAttribute(PLANT);
			break;
		case NUM_1: player1.useItem(1); break;
		case NUM_2: player1.useItem(2); break;
		case NUM_3: player1.useItem(3); break;
		case NUM_4: player1.useItem(4); break;
		case NUM_5: player1.useItem(5); break;
		case NUM_6: player1.useItem(6); break;
		case NUM_9: 
			player1.addHp(50);
			player1.addAttack(5, FIRE);
			player1.addAttack(5, PLANT);
			player1.addAttack(5, ICE);
			break; 
		case KEY_A: player1.SetUsingA(true); break;
		case KEY_Q: player1.SetUsingQ(true); break;
		case KEY_W: 
			player1.setShadePosition();
			player1.SetUsingW(true); break;
		case KEY_E: player1.SetUsingE(true); break;
		case KEY_R: player1.SetUsingR(true); break;
		case J_STG1_1: current_stage = STAGE_1_1; player1.SetXY(480, 480); map_stg1_1.Initialize(); change_song = 1; break;	//z
		case J_STG1_2: current_stage = STAGE_1_2; player1.SetXY(480, 480); map_stg1_2.Initialize(); change_song = 1; break;	//x
		case J_STG1_4: current_stage = STAGE_1_3; player1.SetXY(480, 480); map_stg1_3.Initialize(); change_song = 1; break;	//c
		case J_STG1_6: current_stage = STAGE_1_4; player1.SetXY(780, 1470); map_stg1_4.Initialize(); change_song = 1; break;	//v
		case J_STG2_1: current_stage = STAGE_2_1; player1.SetXY(480, 480); map_stg2_1.Initialize(); change_song = 1; break;	//b
		case J_STG2_2: current_stage = STAGE_2_2; player1.SetXY(480, 480); map_stg2_2.Initialize(); change_song = 1; break;	//n
		case J_STG2_3: current_stage = STAGE_2_3; player1.SetXY(480, 480); map_stg2_3.Initialize(); change_song = 1; break;	//m
		case J_STG2_4: current_stage = STAGE_2_4; player1.SetXY(480, 480); map_stg2_4.Initialize(); change_song = 1; break;	//j

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
		case 27:GotoGameState(GAME_STATE_INIT); for (int i = 0; i < 6; i++)
		{
			player1.useItem(i + 1);
		}
				GotoGameState(GAME_STATE_INIT); break;
		default: return;
		}
	}
	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
	}
	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
	}
	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
	}
	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
	}
	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
	}
	bool CGameStateRun::allEnemyDie(vector<Enemy*> enemys)
	{
		for (unsigned i = 0; i < enemys.size(); i++)
		{
			if (enemys.at(i)->isAlive() && enemys.at(i)->GetName() != "Box") 
			{
				return false;
			}
		}
		return true;
	}
	void CGameStateRun::OnShow()
	{
		//
		//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
		//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
		//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
		corner.SetTopLeft(0, 0);
		corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
		/////////////////////////////////////////////1-1
		if (current_stage == STAGE_1_1) 
		{
			map_stg1_1.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys1_1.size(); i++) 
			{
				if (player1.GetY2() > enemys1_1[i]->GetY2()) 
				{		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1) 
			{
				player1.OnShow(&map_stg1_1);
			}
			for (unsigned i = 0; i < enemys1_1.size(); i++) 
			{
				enemys1_1[i]->OnShow(&map_stg1_1);
				if (i == hero_position)
				{							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg1_1);
				}
			}
		}
		/////////////////////////////////////////////1-2
		if (current_stage == STAGE_1_2)
		{
			map_stg1_2.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys1_2.size(); i++)
			{
				if (player1.GetY2() > enemys1_2[i]->GetY2()) 
				{		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1)
			{
				player1.OnShow(&map_stg1_2);
			}
			for (unsigned i = 0; i < enemys1_2.size(); i++)
			{
				enemys1_2[i]->OnShow(&map_stg1_2);
				if (i == hero_position)
				{							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg1_2);
				}
			}
		}
		/////////////////////////////////////////////1-3
		if (current_stage == STAGE_1_3)
		{
			map_stg1_3.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys1_3.size(); i++) 
			{
				if (player1.GetY2() > enemys1_3[i]->GetY2()) 
				{		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1)
			{
				player1.OnShow(&map_stg1_3);
			}
			for (unsigned i = 0; i < enemys1_3.size(); i++)
			{
				enemys1_3[i]->OnShow(&map_stg1_3);
				if (i == hero_position) 
				{							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg1_3);
				}
			}
		}
		/////////////////////////////////////////////1-4
		if (current_stage == STAGE_1_4)
		{
			map_stg1_4.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys1_4.size(); i++) 
			{
				if (player1.GetY2() > enemys1_4[i]->GetY2()) 
				{		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1) 
			{
				player1.OnShow(&map_stg1_4);
			}
			for (unsigned i = 0; i < enemys1_4.size(); i++) 
			{
				enemys1_4[i]->OnShow(&map_stg1_4);
				if (i == hero_position)
				{							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg1_4);
				}
			}
		}
		/////////////////////////////////////////////2-1
		if (current_stage == STAGE_2_1) 
		{
			map_stg2_1.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys2_1.size(); i++) 
			{
				if (player1.GetY2() > enemys2_1[i]->GetY2())
				{		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1)
			{
				player1.OnShow(&map_stg2_1);
			}
			for (unsigned i = 0; i < enemys2_1.size(); i++)
			{
				enemys2_1[i]->OnShow(&map_stg2_1);
				if (i == hero_position)
				{							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg2_1);
				}
			}
		}
		/////////////////////////////////////////////2_2
		if (current_stage == STAGE_2_2)
		{
			map_stg2_2.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys2_2.size(); i++)
			{
				if (player1.GetY2() > enemys2_2[i]->GetY2())
				{		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1)
			{
				player1.OnShow(&map_stg2_2);
			}
			for (unsigned i = 0; i < enemys2_2.size(); i++) 
			{
				enemys2_2[i]->OnShow(&map_stg2_2);
				if (i == hero_position) 
				{							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg2_2);
				}
			}
		}
		/////////////////////////////////////////////2_3
		if (current_stage == STAGE_2_3) 
		{
			map_stg2_3.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys2_3.size(); i++) 
			{
				if (player1.GetY2() > enemys2_3[i]->GetY2())
				{		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1)
			{
				player1.OnShow(&map_stg2_3);
			}
			for (unsigned i = 0; i < enemys2_3.size(); i++)
			{
				enemys2_3[i]->OnShow(&map_stg2_3);
				if (i == hero_position) {							//如果show到剛剛比較到的位置，show hero
					player1.OnShow(&map_stg2_3);
				}
			}
		}
		/////////////////////////////////////////////2_4
		if (current_stage == STAGE_2_4)
		{
			map_stg2_4.OnShow();
			int hero_position = -1;									//如果Hero的座標比最上面的敵人更上面 position = -1					
			for (unsigned i = 0; i < enemys2_4.size(); i++) 
			{
				if (player1.GetY2() > enemys2_4[i]->GetY2())
				{		//逐一比較Y座標，找到Hero的位置在哪兩個怪物中間
					hero_position = i;
				}
			}
			if (hero_position == -1) 
			{
				player1.OnShow(&map_stg2_4);
			}
			for (unsigned i = 0; i < enemys2_4.size(); i++) 
			{
				enemys2_4[i]->OnShow(&map_stg2_4);
			}
			player1.OnShow(&map_stg2_4);
		}
		if (isAllLevelPass && all_level_pass_count >= 0)
		{
			you_win.SetTopLeft(0, 0);
			you_win.ShowBitmap();
		}
		player_status.showPlayerStatus();
	}
};


