
#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MosqueArtilleryeHeadCenter : public GameObject
	{
	public:
		MosqueArtilleryeHeadCenter();
		virtual ~MosqueArtilleryeHeadCenter();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}