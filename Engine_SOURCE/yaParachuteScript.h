#pragma once
#include "yaScript.h"
#include "yaAnimator.h"
#include "yaPlayer.h"


namespace ya
{
	class ParachuteScript : public Script
	{
	public:
		ParachuteScript();
		virtual ~ParachuteScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) ;
		virtual void OnCollisionStay(Collider2D* collider) ;
		virtual void OnCollisionExit(Collider2D* collider) ;

		virtual void OnTriggerEnter(Collider2D* collider) {};
		virtual void OnTriggerStay(Collider2D* collider) {};
		virtual void OnTriggerExit(Collider2D* collider) {};

		void SetPlayer(Player* player) { mPlayer = player; }

		void End();

	private:
		Animator* mAni;
		Player* mPlayer;
		float mTime;
	};
}
