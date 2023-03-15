#pragma once
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaPlayerScript.h"

namespace ya
{

	class Head : public PlayerScript
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