namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供繞圈圈的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Map
	{
	public:
		virtual bool isEmpty(int x, int y) const = 0;
		virtual void addSX(int n) {};
		virtual void addSY(int n) {};
	};
}