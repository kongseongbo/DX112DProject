#pragma once
#include "yaScript.h"
#include "yaBradleyBullet.h"
#include "yaPlayer.h"
#include "yaEngineEffectScript.h"
#include "yaArabian.h"
#include "yaCameraScript.h"


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
			MOVE2,
			ATTACK,
			ATTACK2,
			DIE,
		};
		TheKeesiState mTheKeesiState;

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
		void Move2();
		void Attack();
		void Attack2();
		void Die();

		void End();

		void CreatMonster(Vector3 position);
		void CreateMissionClear();

		TheKeesiState GetBossState() { return mTheKeesiState; }

		void SetPlayer(Player* player) { mPlayer = player; }

		void SetRightEffect(EngineEffectScript* obj) { mRightScript = obj; }
		void SetLeftEffect(EngineEffectScript* obj) { mLeftScript = obj; }

		void SetCameraScript(CameraScript* script) { mCameraScript = script; }

		bool GetComplete() { return mbComplete; }
	private:
		Transform* mTr;
		
		Player* mPlayer;
		Transform* playerTr;

		GameObject* mRightEf;
		GameObject* mLeftEf;

		EngineEffectScript* mRightScript;
		EngineEffectScript* mLeftScript;

		CameraScript* mCameraScript;

		GameObject* obj;
		GameObject* obj2;
		GameObject* obj3;
		GameObject* obj4;

		bool mbComplete;
		bool mbMove;
		int mIndex;
		int mStack;
		float mTime;
		float mEffectTime;
	};
}