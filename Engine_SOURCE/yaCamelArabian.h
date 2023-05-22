#pragma once
#include "yaGameObject.h"

namespace ya
{
	class CamelArabian : public GameObject
	{
	public:
		CamelArabian();
		virtual ~CamelArabian();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}