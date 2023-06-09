#pragma once
#include "yaScript.h"



namespace ya
{
	class BulletScript : public Script
	{
	public:
		BulletScript();
		virtual ~BulletScript();

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

		void SetDirection(int direction) { mDirection = direction; }
		void SetState(bool state) { mStateUp = state;}

		void SetSpeed(float speed) { mSpeed = speed; }

		void Attack(float time, float attacktime);

	private:
		int mDirection;
		bool mStateUp;
		float mSpeed;
		float mTime;
		bool mbCrash;
	};
}
