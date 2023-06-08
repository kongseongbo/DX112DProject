#pragma once
#include "yaScript.h"

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

		void End();
		void CreateGroundEffect();

		void SetParent(Transform* tr) { mParentTr = tr; }
		void SetAttack(bool flame) { mbFlame = flame; }

	private:
		Transform* mTr;
		Transform* mParentTr;

		GameObject* RightEffect;
		
		bool mbFlame;
		bool mbPrev;
	};
}