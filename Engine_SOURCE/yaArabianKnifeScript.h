#pragma once
#include "yaScript.h"


namespace ya
{
	class ArabianKnifeScript : public Script
	{
	public:
		ArabianKnifeScript();
		virtual ~ArabianKnifeScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);

		virtual void OnTriggerEnter(Collider2D* collider);
		virtual void OnTriggerStay(Collider2D* collider);
		virtual void OnTriggerExit(Collider2D* collider);

		void End();

	private:
		int stack;
		float mTime;
	};
}
