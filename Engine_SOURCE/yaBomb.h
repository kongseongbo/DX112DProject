#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Bomb : public GameObject
	{
	public:
		Bomb();
		virtual ~Bomb();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}