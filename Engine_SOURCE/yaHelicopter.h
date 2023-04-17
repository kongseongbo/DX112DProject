#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Helicopter : public GameObject
	{
	public:
		Helicopter();
		virtual ~Helicopter();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}