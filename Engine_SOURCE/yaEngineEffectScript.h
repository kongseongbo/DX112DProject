#pragma once
#include "yaScript.h"
//#include "yaTheKeesi.h"

namespace ya
{
	class EngineEffectScript : public Script
	{
	public:
		EngineEffectScript();
		virtual ~EngineEffectScript();

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

		void SetParent(Transform* tr) { mParentTr = tr; }

	private:
		Transform* mTr;
		Transform* mParentTr;
		
		//float mTime;

		//int direction;
		//int index;
	};
}