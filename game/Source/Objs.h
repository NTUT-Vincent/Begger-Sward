#ifndef OBJS_H
#define OBJS_H


namespace game_framework {
	enum Direction
	{dirUp, dirDown, dirLeft, dirRight};
	enum ObjsAttribute
	{
		noDirObject,
		noMapCollisionObj,
		noCharacterCollisionObj,
		noAttackCollisionObj,
		altAllignMapObj
	};
	/////////////////////////////////////////////////////////////////////////////
	// 這個class定義了物件的共同介面										   //
	/////////////////////////////////////////////////////////////////////////////
	class Objs
	{
	private:
		int x, y;
		int collisionCount;//碰撞次數，設計給自走的Enemy
		bool isMoving;//在移動(eg.Item不會移動)
		bool isVisible;//是可見的
		bool postToDead;

		Direction dir;
		ObjsAttribute att;
	protected:

	public:
		virtual void OnMove();
		virtual void OnShow();
		
		void RandomDirection();
		void CenterBy();
		
	};
	

	
}

#endif // !OBJS_H