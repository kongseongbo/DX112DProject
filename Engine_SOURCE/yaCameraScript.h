#pragma once
#include "yaScript.h"

namespace ya
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;


		Vector3 CameraWeakShakeeffect(Vector3 pos);
		Vector3 CameraStrongShakeeffect(Vector3 pos);

		Vector3 weakShake(Vector3 pos);
		Vector3 strongShake(Vector3 pos);

		void weakEffectOn() { weakOn = true; }

		void strongEffectOn() { strongOn = true; }
		void strongEffectOff() { strongOn = false; }

		float RandomRange(float min, float max)
		{
			return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
		}

	private:
		bool weakOn;
		bool strongOn;

		float shaketime;
	};
}
