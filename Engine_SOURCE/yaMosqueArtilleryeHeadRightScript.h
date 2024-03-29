#pragma once
#include "yaScript.h"
#include "yaPlayer.h"


namespace ya
{
	class MosqueArtilleryeHeadRightScript : public Script
	{
	public:
		enum class State
		{
			NONE,
			IDLE,
			ATTCK,
			DIE,
		};
		State eState;

		MosqueArtilleryeHeadRightScript();
		virtual ~MosqueArtilleryeHeadRightScript();

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

		void NewBoss();

		void Idle();
		void Attack();
		void Die();

		void SetStartAni(bool start) { mbStartAni = start; }

		void SetTarget(Player* player) { mPlayer = player; }
		State GetState() { return eState; }

	private:
		Player* mPlayer;

		bool mbStartAni;
		int mHp;
		int stack;
		float mTime;
	};
}