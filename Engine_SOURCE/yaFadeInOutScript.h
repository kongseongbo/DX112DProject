#pragma once
#include "yaScript.h"
#include "yaCamera.h"

namespace ya
{
	class FadeInOutScript : public Script
	{
	public:
		FadeInOutScript();
		virtual ~FadeInOutScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void SetCamera(Camera* camera) { mCamera = camera; }

	private:
		Camera* mCamera;
		float mTime;

	};
}