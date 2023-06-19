#pragma once
#include "yaScript.h"
#include "yaMosqueArtilleryeHeadCenterScript.h"


namespace ya
{
	class CenterEffectScript : public Script
	{
	public:
		CenterEffectScript();
		virtual ~CenterEffectScript();

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

		void SetScript(MosqueArtilleryeHeadCenterScript* script) { scr = script; }

	private:
		MosqueArtilleryeHeadCenterScript* scr;
		Transform* mTr;
		float mTime;
	};
}