#pragma once
#include "yaScript.h"
#include "yaMosqueArtilleryeHeadRightScript.h"


namespace ya
{
	class RightEffectScript : public Script
	{
	public:
		RightEffectScript();
		virtual ~RightEffectScript();

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

		void SetScript(MosqueArtilleryeHeadRightScript* script) { scr = script; }

	private:
		MosqueArtilleryeHeadRightScript* scr;
		Transform* mTr;
		float mTime;
	};
}