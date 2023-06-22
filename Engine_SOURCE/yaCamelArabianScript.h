#pragma once
#include "yaScript.h"
#include "yaAnimator.h"


namespace ya
{
	class CamelArabianScript : public Script
	{
	public:
		enum class CamelArabianState
		{
			NONE,
			NEW,
			IDLE,
			MOVE,
			ATTACK,
			DOWNATTACK,
			DIE,
		};
		CamelArabianState eCamelArabianState;

		CamelArabianScript();
		virtual ~CamelArabianScript();

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
		void Idle();
		void Move();
		void Attack();
		void DownAttack();
		void Die();

		void CreateBullet();
		void CreateDeathObj();
		void SetIndex(int a) { index = a; }

	private:
		GameObject* mBullet;

		Transform* mTr;
		float mTime;

		int direction;
		int index;
		int mStack;

		bool mbBullet;
	};
}