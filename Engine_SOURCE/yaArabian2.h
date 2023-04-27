#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Arabian2 : public GameObject
	{
	public:
		Arabian2();
		virtual ~Arabian2();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}