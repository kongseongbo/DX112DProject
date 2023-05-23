#pragma once
#include "yaScript.h"
#include "yaBradleyBullet.h"
#include "yaPlayer.h"
namespace ya
{
	class BradleyScript : public Script
	{
	public:
		enum class BradleyState
		{
			NONE,
			IDLE,
			MOVE,
			STANCECHANGE,
			ATTACK,
			DOWNATTACK,
			DIE,
		};
		BradleyState eBradleyState;

		enum class StanceState
		{
			HOWITZER,
			NORMAL,
		};
		StanceState eStanceState;

		BradleyScript();
		virtual ~BradleyScript();

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

		void Idle();
		void Move();
		void StanceChange();
		void Attack();
		void DownAttack();
		void Die();

		void End();

		void CreateBullet(float rotation);

		void SetPlayer(Player* player) { mPlayer = player; }
	private:
		Player* mPlayer;
		Transform* playerTr;

		BradleyBullet* mBullet;
		Transform* mTr;
		float mTime;

		int direction;
		int index;

		bool mbBullet;
	};
}