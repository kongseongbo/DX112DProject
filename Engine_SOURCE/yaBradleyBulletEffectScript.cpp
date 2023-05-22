#include "yaBradleyBulletEffectScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaAnimator.h"


namespace ya
{
	BradleyBulletEffectScript::BradleyBulletEffectScript()
		: Script()
		, mTime(0.0f)
	{
	}
	BradleyBulletEffectScript::~BradleyBulletEffectScript()
	{
	}
	void BradleyBulletEffectScript::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::Effect);

		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MissileEffect", L"Bradley\\MissileEffect.png");
		ani->Create(L"MissileEffect", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 58.0f), Vector2::Zero, 15, 0.2f);

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> matateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(matateiral);
		sr->SetMesh(mesh);

		ani->GetCompleteEvent(L"MissileEffect") = std::bind(&BradleyBulletEffectScript::End, this);

		ani->Play(L"MissileEffect", false);

	}
	void BradleyBulletEffectScript::Update()
	{
	}
	void BradleyBulletEffectScript::FixedUpdate()
	{
	}
	void BradleyBulletEffectScript::Render()
	{
	}
	void BradleyBulletEffectScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void BradleyBulletEffectScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BradleyBulletEffectScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void BradleyBulletEffectScript::End()
	{
		GetOwner()->Death();
	}
}