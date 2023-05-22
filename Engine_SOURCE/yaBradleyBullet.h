#pragma once
#include "yaGameObject.h"

namespace ya
{
	class BradleyBullet : public GameObject
	{
	public:
		BradleyBullet();
		virtual ~BradleyBullet();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}