#pragma once
#include "yaGameObject.h"

namespace ya
{
	class MosqueArtillery : public GameObject
	{
	public:
		MosqueArtillery();
		virtual ~MosqueArtillery();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}