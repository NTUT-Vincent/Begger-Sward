namespace game_framework {

	class Map1_1 : public Map
	{
	public:
		Map1_1();
		bool isEmpty(int x, int y) const;
		void OnMove();
		void LoadBitmap();
		void OnShow();
		void addSX(int n) override;
		void addSY(int n) override;

	private:
		CMovingBitmap firstmap;
		int map[12][12];
		int sx, sy;							//�a�ϳ̥��W�����y��
		int stage_left, stage_top;
	};
}