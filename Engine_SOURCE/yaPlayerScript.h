#pragma once
#include "yaScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"


namespace ya
{
	class PlayerScript : public Script
	{
	public:
		enum class HeadState
		{
			NONE,
			IDLE,
			MOVE,
			JUMP,
			SITDOWN,
			ATTACK,
			HIT,
			DEATH,
		};
		static HeadState mHeadState;

		enum class BodyState
		{
			NONE,
			IDLE,
			MOVE,
			JUMP,
			SITDOWN,
			ATTACK,
			HIT,
			DEATH,
		};
		static BodyState mBodyState;
	
		PlayerScript();
		~PlayerScript();

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
		void Move();
		void Jump();
		void SitDown();
		void Attack();
		void Hit();
		void Death();

		HeadState GetHeadState() { return mHeadState; }
		void SetHeadState(HeadState state) { mHeadState = state; }

		BodyState GetBodyState() { return mBodyState; }
		void SetBodyState(BodyState state) { mBodyState = state; }

		void SetHeadAnimator(Animator* ani) { headAni = ani; }
		void SetBodyAnimator(Animator* ani) { bodyAni = ani; }

	private:
		Transform* mTr;
		Animator* headAni;
		Animator* bodyAni;

		HeadState headState;
		BodyState bodyState;

		int direction;
	};
}
