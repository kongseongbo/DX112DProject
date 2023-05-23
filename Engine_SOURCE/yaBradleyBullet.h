#pragma once
#include "yaGameObject.h"
#include "yaBradley.h"
namespace ya
{
	class BradleyBullet : public Bradley
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