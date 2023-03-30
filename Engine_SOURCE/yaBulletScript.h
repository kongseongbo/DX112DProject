#pragma once
#include "yaScript.h"
#include "yaBullet.h"
namespace ya
{

	class BulletScript : public Script
	{
	public:
		BulletScript();
		virtual ~BulletScript();

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
	
		//Bullet* GetBullet();
		bool GetActive() { return mActive; }
		void SetActive(bool active) { mActive = active; }
		
	private:
		std::vector<Bullet> mBullets;

		bool mActive;
		int mMaxBullets;
	};
}
