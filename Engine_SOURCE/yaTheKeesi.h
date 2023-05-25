#pragma once
#include "yaGameObject.h"

namespace ya
{
	class TheKeesi : public GameObject
	{
	public:
		TheKeesi();
		virtual ~TheKeesi();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}