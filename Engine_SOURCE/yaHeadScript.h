#pragma once
#include "yaScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"


namespace ya
{
	class HeadScript : public Script
	{
	public:
		enum class HeadState
		{
			NONE,
			IDLE,
			UPIDLE,
			MOVE,
			JUMP,
			SITDOWN,
			SITDOWNMOVE,
			SITDOWNATTACK,
			ATTACK,
			HIT,
			DEATH,
		};
		static HeadState mHeadState;

		HeadScript();
		~HeadScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		void Start();
		void Action();
		void End();

		void Idle();
		void UpIdle();
		void Move();
		void Jump();
		void SitDown();
		void SitDownMove();
		void SitDownAttack();
		void Attack();
		void Hit();
		void Death();

		HeadState GetHeadState() { return mHeadState; }
		void SetHeadState(HeadState state) { mHeadState = state; }


		void SetHeadAnimator(Animator* ani) { headAni = ani; }
		void SetBodyAnimator(Animator* ani) { bodyAni = ani; }

	private:
		Transform* mTr;
		Animator* headAni;
		Animator* bodyAni;

		HeadState headState;

		int direction;
	};
}