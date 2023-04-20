#pragma once
#include "yaScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"


namespace ya
{
	enum class BodyState
	{
		NONE,
		IDLE,
		MOVE,
		JUMP,
		SITDOWN,
		SITDOWNMOVE,
		ATTACK,
		HIT,
		DEATH,
	};
	static BodyState mBodyState;

	class Player;
	class BodyScript : public Script
	{
	public:


		BodyScript();
		~BodyScript();

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
		void SitDownMove();
		void SitDownAttack();
		void Attack();
		void Hit();
		void Death();

		BodyState GetBodyState() { return mBodyState; }
		void SetBodyState(BodyState state) { mBodyState = state; }

		void SetBodyAnimator(Animator* ani) { bodyAni = ani; }

		Player* mHead;

	private:
		Transform* mTr;
		Animator* bodyAni;

		BodyState bodyState;

		int direction;
	};
}
