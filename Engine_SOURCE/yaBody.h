#pragma once
#include "yaGameObject.h"
#include "yaAnimator.h"




namespace ya
{
	class Body : public GameObject
	{
	public:
		Body();
		virtual ~Body();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();



	private:
	};
}
