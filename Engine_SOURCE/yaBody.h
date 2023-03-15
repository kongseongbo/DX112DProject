#pragma once
#include "yaGameObject.h"
#include "yaAnimator.h"
#include "yaPlayerScript.h"

namespace ya
{
	
	class Body : public PlayerScript
	{
	public:
		Body();
		virtual ~Body();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		Animator* mAnimator;
	};

}