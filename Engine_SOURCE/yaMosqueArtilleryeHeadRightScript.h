#pragma once
#include "yaScript.h"

namespace ya
{
	class MosqueArtilleryeHeadRightScript : public Script
	{
	public:
		MosqueArtilleryeHeadRightScript();
		virtual ~MosqueArtilleryeHeadRightScript();

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

		void SetStartAni(bool start) { mbStartAni = start; }

		void NewBoss();

	private:
		int stack;
		bool mbStartAni;

	};
}