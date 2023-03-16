#pragma once
#include "yaComponent.h"
#include "yaAnimator.h"
#include "yaPlayerScript.h"

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

		//void AniPlay(std::wstring name, bool loop);

	private:
		Animator* mAnimator;
	};

}