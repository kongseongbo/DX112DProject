#pragma once
#include "yaScript.h"
#include "yaArabian.h"


namespace ya
{
	class PoroScript : public Script
	{
	public:
		enum class PoroState
		{
			NONE,
			IDLE,
			MOVE,
			ITEM,
			DEATH,
		};
		PoroState mPoroState;

		PoroScript();
		virtual ~PoroScript();

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

		void Idle();
		void Move();
		void Item();
		void Death();

		void End();

	private:
		Transform* mTr;

		float mMoveTime;
		float mtime;
		int mStack;

	};
}