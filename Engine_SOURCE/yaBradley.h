#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Bradley : public GameObject
	{
	public:
		Bradley();
		virtual ~Bradley();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}