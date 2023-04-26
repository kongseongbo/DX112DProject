#pragma once
#include "yaScript.h"
#include "yaAnimator.h"
#include "yaArabian.h"
namespace ya
{
	class ArabianScript : public Script
	{
	public:
		enum class ArabianState
		{
			NONE,
			NEW,
			IDLE,
			MOVE,
			ATTACK,
			UPATTACK,
			DEATH,
		};
		static ArabianState mArabianState;

		ArabianScript();
		virtual ~ArabianScript();

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

		void SetIndex(int a) { index = a; }

	private:
		//std::vector<Arabian*> mArabian;

		Animator* mArabianAni;
		Transform* mTr;
		float mTime;

		int direction;
		int index;
	};
}