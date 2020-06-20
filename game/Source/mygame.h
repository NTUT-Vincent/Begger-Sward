#include "ABoss.h"
#include "Maps.h"
#include "Map1_1.h"
#include "Map1_2.h"
#include "Map1_3.h"
#include "Map1_4.h"
#include "Map2_1.h"
#include "Map2_2.h"
#include "Map2_3.h"
#include "Map2_4.h"
#include "Hero.h"
#include "Enemy.h"
#include "Util.h"
#include "Character.h"
#include "Scarecrow.h"
#include "GreenSlime.h"
#include "RedSlime.h"
#include "BlueSlime.h"
#include "RedGoblin.h"
#include "BlueGoblin.h"
#include "GreenGoblin.h"
#include "Box.h"
#include "PlayerStatus.h"

namespace game_framework 
{
	/////////////////////////////////////////////////////////////////////////////
	// mygame.h: ���ɮ��x�C��������class��interface							   //
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateInit : public CGameState
	{
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
		CMovingBitmap selection;
		CMovingBitmap help;
		CMovingBitmap about;
		CMovingBitmap choose;
		int goto_status;								// 0�O�W���� game start, 1�O�U���� story
		bool isHelp;
		bool isAbout;
	};
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateRun : public CGameState 
	{
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void stage_process_move(Maps & stage_map, Hero & player, vector<Enemy*>& enemy_array, STAGE next_stage);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		bool allEnemyDie(vector<Enemy*> enemys);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const int		NUMBALLS;	// �y���`��
		PlayerStatus	player_status;
		Map1_1			map_stg1_1;
		Map1_2			map_stg1_2;
		Map1_3			map_stg1_3;
		Map1_4			map_stg1_4;
		Map2_1			map_stg2_1;
		Map2_2			map_stg2_2;
		Map2_3			map_stg2_3;
		Map2_4			map_stg2_4;
		Hero			player1;
		vector<Enemy*>  enemys1_1;
		vector<Enemy*>  enemys1_2;
		vector<Enemy*>  enemys1_3;
		vector<Enemy*>  enemys1_4;
		vector<Enemy*>  enemys2_1;
		vector<Enemy*>  enemys2_2;
		vector<Enemy*>  enemys2_3;
		vector<Enemy*>  enemys2_4;
		STAGE			current_stage;
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
		CMovingBitmap	corner;		// ������
		CMovingBitmap you_win;
		CInteger		hits_left;	// �ѤU��������
		bool isAllLevelPass;
		int all_level_pass_count;
		int change_song;
	};
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////
	class CGameStateOver : public CGameState
	{
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
		CAnimation gameover;
	};
}