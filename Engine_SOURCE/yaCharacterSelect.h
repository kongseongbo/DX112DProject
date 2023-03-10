#pragma once
#include "yaScript.h"

namespace ya
{
	class CharacterSelect : public Script
	{

	public:
		CharacterSelect();
		~CharacterSelect();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;


	private:
		float mTime;
	};
}