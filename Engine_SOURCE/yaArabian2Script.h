#pragma once
#include "yaScript.h"
#include "yaAnimator.h"
#include "yaArabian.h"
namespace ya
{
	class Arabian2Script : public Script
	{
	public:
		enum class Arabian2State
		{
			NONE,
			NEW,
			IDLE,
			MOVE,
			ATTACK,
			UPATTACK,
			DEATH,
		};
		Arabian2State mArabian2State;

		Arabian2Script();
		virtual ~Arabian2Script();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);

		virtual void OnTriggerEnter(Collider2D* collider);
		virtual void OnTriggerStay(Collider2D* collider);
		virtual void OnTriggerExit(Collider2D* collider);

		void New();
		void Idle();
		void Move();
		void Attack();
		void Death();

		void AttackKnife();

	private:
		Animator* mArabianAni;
		Transform* mTr;
		float mTime;

		int direction;
	};
}