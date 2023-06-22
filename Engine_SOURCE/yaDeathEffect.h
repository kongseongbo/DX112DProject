#pragma once
#include "yaScript.h"
#include "yaTheKeesiScript.h"


namespace ya
{

	class DeathEffect : public Script
	{
	public:
		DeathEffect();
		virtual ~DeathEffect();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) {};
		virtual void OnCollisionStay(Collider2D* collider) {};
		virtual void OnCollisionExit(Collider2D* collider) {};

		virtual void OnTriggerEnter(Collider2D* collider) {};
		virtual void OnTriggerStay(Collider2D* collider) {};
		virtual void OnTriggerExit(Collider2D* collider) {};

		void End();

		TheKeesiScript* keesiScript;
		Transform* tr;
	private:
		Transform* mTr;

		float mTime;
		bool ox;
	};
}