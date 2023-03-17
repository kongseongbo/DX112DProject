#pragma once
#include "yaScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaPlayer.h"


namespace ya
{
	class PlayerScript : public Script
	{
	public:
		enum class State
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
		static State mState;
		

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

		State GetState() { return mState; }
		void SetState(State state) { mState = state; }

		//void SetingState(State newState);

		void SetHeadAnimator(Animator* ani) { headAni = ani; }
		void SetBodyAnimator(Animator* ani) { bodyAni = ani; }

		void SetHeadPlayer(Player* player) { mHeadPlayer = player; }
		void SetBodyPlayer(Player* player) { mBodyPlayer = player; }

		void PositionSetting(Transform* playerA, Transform* playerB);

	private:
		Transform* mTr;
		Animator* headAni;
		Animator* bodyAni;
		Player* mHeadPlayer;
		Player* mBodyPlayer;
		State prevState;
	};
}
