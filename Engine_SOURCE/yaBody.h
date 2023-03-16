#pragma once
#include "yaComponent.h"
#include "yaAnimator.h"


namespace ya
{
	
	class Body : public Component
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