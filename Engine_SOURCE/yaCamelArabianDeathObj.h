#pragma once
#include "yaGameObject.h"

namespace ya
{
	class CamelArabianDeathObj : public GameObject
	{
	public:
		CamelArabianDeathObj();
		virtual ~CamelArabianDeathObj();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}