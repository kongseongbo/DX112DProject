#include "yaEngineEffectScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaCollider2D.h"
#include "yaScene.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"

#include "yaFlamestrikeScript.h"
#include "yaTheKeesiScript.h"

namespace ya
{
	EngineEffectScript::EngineEffectScript()
		: Script()
		, mTr(nullptr)
		, mParentTr(nullptr)
		, RightEffect(nullptr)
		, LeftEffect(nullptr)
		, mbFlame(false)
		, mbPrev(false)
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
		ani->Create(L"CreateFlame", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 170.0f), Vector2::Zero, 25, 0.25f);
		ani->Create(L"AttackFlame", texture, Vector2(0.0f, 170.0f), Vector2(60.0f, 170.0f), Vector2::Zero, 4, 0.2f);
		ani->Play(L"EngineEffect", true);

		ani->GetCompleteEvent(L"CreateFlame") = std::bind(&EngineEffectScript::End, this);
	}
	void EngineEffectScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		if (mbFlame == false)
		{
			if(GetOwner()->GetName() == L"leftengineeffect")
				mTr->SetPosition(Vector3(mParentTr->GetPosition().x - 4.7f, mParentTr->GetPosition().y - 3.1f, mParentTr->GetPosition().z - 1.0f));

			if (GetOwner()->GetName() == L"rightengineeffect")
				mTr->SetPosition(Vector3(mParentTr->GetPosition().x + 4.6f, mParentTr->GetPosition().y - 3.1f, mParentTr->GetPosition().z - 1.0f));
		}

		if (mbPrev == false && mbFlame == true)
		{
			ani->Play(L"CreateFlame", false);
			
		}

		if (mbFlame == true)
		{
			mbPrev = true;
			if (GetOwner()->GetName() == L"leftengineeffect")
			{
				mTr->SetPosition(Vector3(mParentTr->GetPosition().x - 4.6f, mParentTr->GetPosition().y - 6.1f, mParentTr->GetPosition().z - 1.0f));
				mTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

				if (LeftEffect != nullptr)
				{
					Transform* tr = LeftEffect->GetComponent<Transform>();
					tr->SetPosition(Vector3(mTr->GetPosition().x - 0.55f, mTr->GetPosition().y - 4.3f, mTr->GetPosition().z - 1.0f));
					tr->SetScale(Vector3(14.0f, 14.0f, 1.0f));
				}
			}

			if (GetOwner()->GetName() == L"rightengineeffect")
			{
				mTr->SetPosition(Vector3(mParentTr->GetPosition().x + 4.5f, mParentTr->GetPosition().y - 6.1f, mParentTr->GetPosition().z - 1.0f));
				mTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

				

				if (RightEffect != nullptr)
				{
					Transform* tr = RightEffect->GetComponent<Transform>();
					tr->SetPosition(Vector3(mTr->GetPosition().x + 0.3f, mTr->GetPosition().y - 4.3f, mTr->GetPosition().z - 1.0f));
					tr->SetScale(Vector3(14.0f, 14.0f, 1.0f));
				}
			}
		}

		TheKeesiScript* scr = mParentTr->GetOwner()->GetScript<TheKeesiScript>();
			
		if ((UINT)scr->GetBossState() == 6)
		{
			GetOwner()->Death();
		}

	}
	void EngineEffectScript::FixedUpdate()
	{
	}
	void EngineEffectScript::Render()
	{
	}
	void EngineEffectScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void EngineEffectScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void EngineEffectScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void EngineEffectScript::End()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"AttackFlame", true);

		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetType(eColliderType::Rect);
		coll->SetSize(Vector2(0.1f, 0.5f));

		GetOwner()->SetLayerType(eLayerType::Monster);
		CreateGroundEffect();
	}
	void EngineEffectScript::CreateGroundEffect()
	{
		if (GetOwner()->GetName() == L"rightengineeffect")
		{
			FlamestrikeScript* flameScrR = RightEffect->AddComponent<FlamestrikeScript>();
			Transform* tr = RightEffect->GetComponent<Transform>();
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
		}

		if (GetOwner()->GetName() == L"leftengineeffect")
		{
			FlamestrikeScript* flameScrL = LeftEffect->AddComponent<FlamestrikeScript>();
			Transform* tr = LeftEffect->GetComponent<Transform>();
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
		}
	}
}