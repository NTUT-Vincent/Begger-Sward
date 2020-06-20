#include "Enemy.h"

namespace game_framework {

	class Map1_1 : public Maps
	{
	public:
		Map1_1();
		~Map1_1();
		void Initialize();
		void setPos(int x, int y, int n);			//�N�a�Ϯy�Ъ��}�C�]���ǤJ���Ʀr
		void setClear(bool b);
		bool isEmpty(int x, int y) const;			//�ˬd�O�_���i�H�����a��
		bool inFinishArea(int x, int y) override;	//�O�_�b�i�H�e���U�@�����a��
		bool isOnIce(int x, int y);					//�O�_�b�B�W��
		void OnMove();
		void LoadBitmap();
		void OnShow();
		void getHeroX(int x) override;
		void getHeroY(int y) override;
		int screenX(int x) override;				//�⵴��y�д����ù�������
		int screenY(int y) override;
		void setIceWallPos(int x, int y, int n);	//�]�wicewall
	private:
		CMovingBitmap firstmap;
		CAnimation gate;
		bool all_enemy_clear;
		int map[12][12];
		int hx, hy;
		int stage_left, stage_top;
	};
}