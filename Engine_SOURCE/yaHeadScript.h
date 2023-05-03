#pragma once
#include "yaScript.h"
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaBullet.h"
#include "yaBomb.h"
#include "yaObjectPool.h"
#include "yaBody.h"

namespace ya
{
	enum class HeadState
	{
		NONE,
		IDLE,
		UPIDLE,
		MOVE,
		UPMOVE,
		JUMP,
		JUMPMOVE,
		SITDOWN,
		SITDOWNMOVE,
		SITDOWNATTACK,
		ATTACK,
		UPATTACK,
		HIT,
		DEATH,
	};
	static HeadState mHeadState;

	class HeadScript : public Script
	{
	public:

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
		void UpMove();
		void Jump();
		void JumpMove();
		void Attack();
		void UpAttack();
		void SitDown();
		void SitDownMove();
		void SitDownAttack();
		void Hit();
		void Death();

		void NewBullet(std::wstring name, Vector3 pos, int direction, bool Up = false);
		void NewMachineGun(Vector3 pos, int direction, bool Up = false);
		void NewMachineGunUp(Vector3 pos, int direction);
		void NewBomb(Vector3 pos, float speed, int direction);

		void SetBody(Body* body) { mBody = body; }

		HeadState GetHeadState() { return mHeadState; }
		void SetHeadState(HeadState state) { mHeadState = state; }

		eGunState GetGunState() { return mGunState; }
		void SetGunState(eGunState state) { mGunState = state; }

		void SetStop(int i) { mStop = i; }

	private:
		Bullet* mBullet;
		Bullet* mBullets[5];
		Bomb* mBomb;

		Body* mBody;

		Transform* mTr;
		Animator* mHeadAni;

		eGunState mGunState;

		int direction;
		float mTime;

		float mDiagonal;
		bool mbLine;

		int mStop;

		/*ObjectPool< Bullet, 50 > mBullets;
		Bullet* a;*/
	};
}
