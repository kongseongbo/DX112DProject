#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MosqueArtilleryeHeadRight : public GameObject
	{
	public:
		MosqueArtilleryeHeadRight();
		virtual ~MosqueArtilleryeHeadRight();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}