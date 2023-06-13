#pragma once
#include "yaScript.h"
#include "yaBradleyBullet.h"
#include "yaPlayer.h"
#include "yaEngineEffectScript.h"
#include "yaArabian.h"


namespace ya
{
	class TheKeesiScript : public Script
	{
	public:
		enum class TheKeesiState
		{
			NONE,
			IDLE,
			MOVE,
			ATTACK,
			ATTACK2,
			DIE,
		};
		TheKeesiState eTheKeesiState;

		TheKeesiScript();
		virtual ~TheKeesiScript();

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

		void Idle();
		void Move();
		void Attack();
		void Attack2();
		void Die();

		void End();

		void CreatMonster(Vector3 position);

		void SetPlayer(Player* player) { mPlayer = player; }

		void SetRightEffect(EngineEffectScript* obj) { mRightScript = obj; }
		void SetLeftEffect(EngineEffectScript* obj) { mLeftScript = obj; }
	private:
		Transform* mTr;
		
		Player* mPlayer;
		Transform* playerTr;

		GameObject* mRightEf;
		GameObject* mLeftEf;

		EngineEffectScript* mRightScript;
		EngineEffectScript* mLeftScript;

		bool mbMove;
		int mIndex;
		float mTime;
	};
}