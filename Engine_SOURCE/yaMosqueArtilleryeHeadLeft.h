#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MosqueArtilleryeHeadLeft : public GameObject
	{
	public:
		MosqueArtilleryeHeadLeft();
		virtual ~MosqueArtilleryeHeadLeft();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}