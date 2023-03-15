#pragma once
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaComponent.h"

namespace ya
{

	class Head : public Component
	{
	public:
		Head();
		virtual ~Head();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Animator* mAnimator;
	};

}