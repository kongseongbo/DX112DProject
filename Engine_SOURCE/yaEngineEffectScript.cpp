#include "yaEngineEffectScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaCollider2D.h"
#include "yaScene.h"
#include "yaAnimator.h"


namespace ya
{
	EngineEffectScript::EngineEffectScript()
		: Script()
		, mTr(nullptr)
		, mParentTr(nullptr)
	{
	}
	EngineEffectScript::~EngineEffectScript()
	{
	}
	void EngineEffectScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"EngineEffect", L"TheKeesi\\EngineEffect.png");
		ani->Create(L"EngineEffect", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 45.0f), Vector2::Zero, 4, 0.15f);

		texture = Resources::Load<Texture>(L"Flame", L"TheKeesi\\Flame.png");
		ani->Create(L"CreateFlame", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 170.0f), Vector2::Zero, 12, 0.2f);


		ani->Play(L"EngineEffect", true);
	}
	void EngineEffectScript::Update()
	{
		if(GetOwner()->GetName() == L"leftengineeffect")
			mTr->SetPosition(Vector3(mParentTr->GetPosition().x - 4.7f, mParentTr->GetPosition().y - 3.1f, mParentTr->GetPosition().z - 1.0f));

		if (GetOwner()->GetName() == L"rightengineeffect")
			mTr->SetPosition(Vector3(mParentTr->GetPosition().x + 4.6f, mParentTr->GetPosition().y - 3.1f, mParentTr->GetPosition().z - 1.0f));
	}
	void EngineEffectScript::FixedUpdate()
	{
	}
	void EngineEffectScript::Render()
	{
	}
	void EngineEffectScript::OnCollisionEnter(Collider2D* collider)
	{
		Animator* ani =	GetOwner()->GetComponent<Animator>();
		if (GetOwner()->GetName() == L"leftengineeffect")
			ani->Play(L"CreateFlame", false);
		if (GetOwner()->GetName() == L"rightengineeffect")
			ani->Play(L"CreateFlame", false);
	}
	void EngineEffectScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void EngineEffectScript::OnCollisionExit(Collider2D* collider)
	{
	}
}