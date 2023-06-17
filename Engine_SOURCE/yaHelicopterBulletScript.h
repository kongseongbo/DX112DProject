#pragma once
#include "yaScript.h"
#include "yaPlayer.h"
namespace ya
{
	class HelicopterBulletScript : public Script
	{
	public:
		HelicopterBulletScript();
		virtual ~HelicopterBulletScript();

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

		void SetPlayerPos(Vector3 position) { mPlayerTr = position; }
		void SetRot(float rot) { mRot = rot; }
	private:
		Transform* mTr;
		Vector3 pos;

		Vector3 mPlayerTr;
		float mTime;
		float mRot;
	};
}