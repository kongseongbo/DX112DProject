#pragma once
#include "yaScript.h"
#include "yaAnimator.h"

namespace ya
{
	class CompleteScript : public Script
	{
	public:
		CompleteScript();
		virtual ~CompleteScript();

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

	private:
		Transform* mTr;
		Animator* mAni;
	};
}
