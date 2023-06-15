#include "yaMosqueArtilleryBulletEffectScript.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaObject.h"

namespace ya
{
	MosqueArtilleryBulletEffectScript::MosqueArtilleryBulletEffectScript()
		: Script()
		, mTime(0.0f)
	{
	}
	MosqueArtilleryBulletEffectScript::~MosqueArtilleryBulletEffectScript()
	{
		int a = 0;
	}
	void MosqueArtilleryBulletEffectScript::Initalize()
	{
		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BulletBomb", L"MosqueArtillery\\BulletBomb.png");
		ani->Create(L"BulletBomb", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 38.0f), Vector2::Zero, 15, 0.1f);

		ani->Play(L"BulletBomb", false);

		ani->GetCompleteEvent(L"BulletBomb") = std::bind(&MosqueArtilleryBulletEffectScript::End, this);
	}
	void MosqueArtilleryBulletEffectScript::Update()
	{
	}
	void MosqueArtilleryBulletEffectScript::FixedUpdate()
	{
	}
	void MosqueArtilleryBulletEffectScript::Render()
	{
	}
	void MosqueArtilleryBulletEffectScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void MosqueArtilleryBulletEffectScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryBulletEffectScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void MosqueArtilleryBulletEffectScript::End()
	{
		GetOwner()->Death();
	}
}