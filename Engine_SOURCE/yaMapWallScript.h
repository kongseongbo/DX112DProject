#pragma once
#include "yaScript.h"
#include "yaPlayer.h"


namespace ya
{
	class MapWallScript : public Script
	{
	public:
		MapWallScript();
		virtual ~MapWallScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);

		virtual void OnTriggerEnter(Collider2D* collider) {};
		virtual void OnTriggerStay(Collider2D* collider) {};
		virtual void OnTriggerExit(Collider2D* collider) {};

		void SetPlayerObj(Player* player) { mPlayer = player; }

		void CreatMonster(Vector3 position);

		void Destroy();

	private:
		Player* mPlayer;
		int mStack;
	};
}