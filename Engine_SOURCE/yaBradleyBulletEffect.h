#pragma once
#include "yaGameObject.h"

namespace ya
{
	class BradleyBulletEffect : public GameObject
	{
	public:
		BradleyBulletEffect();
		virtual ~BradleyBulletEffect();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}