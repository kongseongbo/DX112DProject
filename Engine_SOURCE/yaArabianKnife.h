#pragma once
#include "yaGameObject.h"

namespace ya
{
	class ArabianKnife : public GameObject
	{
	public:
		ArabianKnife();
		virtual ~ArabianKnife();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}