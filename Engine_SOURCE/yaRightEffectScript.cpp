#include "yaRightEffectScript.h"
#include "yaAnimator.h"
#include "yaResources.h"

namespace ya
{
	RightEffectScript::RightEffectScript()
		:Script()
	{
	}
	RightEffectScript::~RightEffectScript()
	{
	}
	void RightEffectScript::Initalize()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryAttackEffect", L"MosqueArtillery\\Effect.png");
		ani->Create(L"CenterAttackEffect", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 52.0f), Vector2(0.0f, 0.0f), 32, 0.2f);


	}
	void RightEffectScript::Update()
	{
		if (scr->eState == MosqueArtilleryeHeadRightScript::State::ATTCK)
		{
			Animator* ani = GetOwner()->GetComponent<Animator>();
			ani->Play(L"CenterAttackEffect", false);
		}
	}
	void RightEffectScript::FixedUpdate()
	{
	}
	void RightEffectScript::Render()
	{
	}
}