#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Arabian : public GameObject
	{
	public:
		Arabian();
		virtual ~Arabian();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}