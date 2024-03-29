#pragma once
#include "yaScript.h"
#include "yaAnimator.h"

namespace ya
{
	class BossArabianScript : public Script
	{
	public:
		enum class BossArabianState
		{
			NONE,
			NEW,
			JUMP,
			IDLE,
			MOVE,
			ATTACK,
			UPATTACK,
			DEATH,
		};
		BossArabianState mBossArabianState;

		BossArabianScript();
		virtual ~BossArabianScript();

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

		void New();
		void Jump();
		void Idle();
		void Move();
		void Attack();
		void Death();

		void AttackKnife();

		void SetIndex(int a) { index = a; }

	private:
		Animator* mAni;
		Transform* mTr;
		float mTime;

		int direction;
		int index;

		bool ox;
	};
}