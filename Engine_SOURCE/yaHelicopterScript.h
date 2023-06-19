#pragma once
#include "yaScript.h"
#include "yaPlayer.h"
namespace ya
{
	class HelicopterScript : public Script
	{
	public:
		enum class HeliState
		{
			NONE,
			MOVE,
			DIE,
		};
		HeliState mHeliState;


		HelicopterScript();
		virtual ~HelicopterScript();

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

		void Move();
		void Die();
		void End();
	
		void SetPlayer(Player* player) { mPlayer = player; }
		void SetTime(float time) { mTime = time; }
		void SetDirection(bool direction) { ox = direction; }
	private:
		Transform* mTr;

		Player* mPlayer;
		float mRot;
		float mTime;
		float mMoveTime;
		int mStack;

		bool ox;
	};
}