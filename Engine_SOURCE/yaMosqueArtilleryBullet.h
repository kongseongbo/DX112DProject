#pragma once
#include "yaGameObject.h"



namespace ya
{
	class MosqueArtilleryBullet : public GameObject
	{
	public:
		MosqueArtilleryBullet();
		virtual ~MosqueArtilleryBullet();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:

	};
}