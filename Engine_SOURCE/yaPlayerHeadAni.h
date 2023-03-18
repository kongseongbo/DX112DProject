#pragma once
#include "yaAnimator.h"
#include "yaScript.h"
#include "yaPlayerScript.h"


namespace ya
{
	class PlayerHeadAni : public Script
	{
	public:
		PlayerHeadAni();
		~PlayerHeadAni();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		void SetPlayerScript(PlayerScript* script) { mPlayerScript = script; }

	private:
		Transform* mTr;
		Animator* headAni;
		PlayerScript* mPlayerScript;
	};
}
