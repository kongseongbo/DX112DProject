#pragma once
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaHead.h"
#include "yaBody.h"



namespace ya
{
	class Head;
	class Body;
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		

	private:
	};
}
