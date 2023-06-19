#pragma once
#include "yaScript.h"
#include "yaMosqueArtilleryeHeadLeftScript.h"

namespace ya
{
	class LeftEffectScript : public Script
	{
	public:
		LeftEffectScript();
		virtual ~LeftEffectScript();

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

		void SetScript(MosqueArtilleryeHeadLeftScript* script) { scr = script; }

	private:
		MosqueArtilleryeHeadLeftScript* scr;
		Transform* mTr;
		float mTime;
	};
}