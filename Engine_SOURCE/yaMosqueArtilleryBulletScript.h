#pragma once
#include "yaScript.h"



namespace ya
{
	class MosqueArtilleryBulletScript : public Script
	{
	public:
		MosqueArtilleryBulletScript();
		virtual ~MosqueArtilleryBulletScript();

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

		void SetDirection(int direction) { mDirection = direction; }
		void SetState(bool state) { mStateUp = state; }

		void SetSpeed(float speed) { mSpeed = speed; }

		void Attack(Vector3 pos);

		void SetTarget(Vector3 pos) { mTargetPos = pos; }

	private:
		int mDirection;
		bool mStateUp;
		float mSpeed;
		float mTime;

		Vector3 mTargetPos;

	};
}
