#pragma once
#include "yaGameObject.h"



namespace ya
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		//eGunState GetGunState() { return mGuntype; }
		//void SetGunState(eGunState type) { mGuntype = type; }

	private:
		//eGunState mGuntype;
	};
}
