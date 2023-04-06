#pragma once
#include "yaGameObject.h"
#include "yaAnimator.h"




namespace ya
{
	class MachineGun : public GameObject
	{
	public:
		MachineGun();
		virtual ~MachineGun();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}
