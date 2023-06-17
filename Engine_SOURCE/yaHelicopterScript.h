#pragma once
#include "yaScript.h"
#include "yaPlayer.h"
namespace ya
{
	class HelicopterScript : public Script
	{
	public:
		HelicopterScript();
		virtual ~HelicopterScript();

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
	
		void SetPlayer(Player* player) { mPlayer = player; }
	private:
		Transform* mTr;

		Player* mPlayer;
		float mRot;
		float mTime;
	};
}