
#pragma once
#include "yaScript.h"

namespace ya
{
	class MosqueArtilleryeHeadCenterScript : public Script
	{
	public:
		enum class State
		{
			NONE,
			IDLE,
			ATTCK,
			DIE,
		};
		State eState;
		
		MosqueArtilleryeHeadCenterScript();
		virtual ~MosqueArtilleryeHeadCenterScript();

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

		void NewBoss();

		void Idle();
		void Attack();
		void Die();

		void SetStartAni(bool start) { mbStartAni = start; }

	private:
		bool mbStartAni;
		int stack;
		float mTime;
	};
}