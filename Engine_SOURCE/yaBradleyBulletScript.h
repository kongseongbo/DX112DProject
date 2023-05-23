#pragma once
#include "yaScript.h"


namespace ya
{
	class BradleyBulletScript : public Script
	{
	public:
		BradleyBulletScript();
		virtual ~BradleyBulletScript();

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

		void HowitzerAttack(Vector3 position, float time, float attackTime);
		void NormalAttack(Vector3 position, float time, float attackTime);
			

		void SetRot(float rot) { mInitRot = rot; }
	private:
		float mTime;
		float mRot;
		float mInitRot;

	};
}
