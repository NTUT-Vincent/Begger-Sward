#ifndef __ATTACK_H__
#define __ATTACK_H__
#include "Maps.h"
#include "Character.h"
#include "Enemy.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class Attack
	{
	public:
		Attack();
		Attack(int hx, int hy);
		bool HitEnemy(Enemy * enemy);
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void LoadBitmap();				// ���J�ϧ�
		bool isExist();
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetIsExist(bool flag);	// �]�w�O�_���b���U����
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
	protected:
		CMovingBitmap animation;		// ���l���ʵe
		int x, y;					// ���l���W���y��
		bool is_exist;
	private:
		bool HitObject(int tx1, int ty1, int tx2, int ty2);
	};
}
#endif