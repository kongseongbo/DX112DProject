#pragma once
#include "yaScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"

namespace ya
{
	class PlayerScript : public Script
	{
	public:
		enum class State
		{
			IDLE,
			LEFTMOVE,
			RIGHTMOVE,
			JUMP,
			SITDOWN,
			ATTACK,
			HIT,
			DEATH,
		};
		

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
		void LeftMove();
		void RightMove();
		void Jump();
		void SitDown();
		void Attack();
		void Hit();
		void Death();

		State GetState() { return mState; }
		void SetState(State state) { mState = state; }

		static State mState;
	private:
		Transform* mTr;
		
	};
}
