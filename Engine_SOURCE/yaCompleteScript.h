#pragma once
#include "yaScript.h"
#include "yaComponent.h"
#include "yaAnimator.h"
#include "yaTheKeesiScript.h"
#include "yaHeadScript.h"

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

		virtual void OnCollisionEnter(Collider2D* collider) {};
		virtual void OnCollisionStay(Collider2D* collider) {};
		virtual void OnCollisionExit(Collider2D* collider) {};

		virtual void OnTriggerEnter(Collider2D* collider) {};
		virtual void OnTriggerStay(Collider2D* collider) {};
		virtual void OnTriggerExit(Collider2D* collider) {};

		void Complete(std::wstring aniname, float time);

		void SetKeesiScript(TheKeesiScript* scr) { mKeesiScript = scr; }

	private:
		Transform* mTr;
		Animator* mAni;

		TheKeesiScript* mKeesiScript;

		float mTime;
	};
}
