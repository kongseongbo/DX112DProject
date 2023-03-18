#pragma once
#include "yaAnimator.h"
#include "yaScript.h"
#include "yaPlayerScript.h"
#include "yaBodyAnimator.h"

namespace ya
{
	class PlayerBodyAni : public Script
	{
	public:
		PlayerBodyAni();
		~PlayerBodyAni();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		void SetPlayerScript(PlayerScript* script) { mPlayerScript = script; }

	private:
		Transform* mTr;
		BodyAnimator* bodyAni;
		PlayerScript* mPlayerScript;

	};
}
