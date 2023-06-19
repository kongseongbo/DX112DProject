#include "yaLeftEffectScript.h"
#include "yaResources.h"
#include "yaAnimator.h"

namespace ya
{
	LeftEffectScript::LeftEffectScript()
		:Script()
	{
	}
	LeftEffectScript::~LeftEffectScript()
	{
	}
	void LeftEffectScript::Initalize()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryAttackEffect", L"MosqueArtillery\\Effect.png");
		ani->Create(L"CenterAttackEffect", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 52.0f), Vector2(0.0f, 0.0f), 32, 0.2f);

		
	}
	void LeftEffectScript::Update()
	{
		if (scr->eState == MosqueArtilleryeHeadLeftScript::State::ATTCK)
		{
			Animator* ani = GetOwner()->GetComponent<Animator>();
			ani->Play(L"CenterAttackEffect", false);
		}
	}
	void LeftEffectScript::FixedUpdate()
	{
	}
	void LeftEffectScript::Render()
	{
	}
}