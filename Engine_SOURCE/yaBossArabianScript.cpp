#include "yaBossArabianScript.h"
#include "yaSceneManager.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"

namespace ya
{
	BossArabianScript::BossArabianScript()
		: Script()
		, mArabianState(BossArabianState::NEW)

	{
	}
	BossArabianScript::~BossArabianScript()
	{
	}
	void BossArabianScript::Initalize()
	{
		mAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"ArabianIdle", L"Arabian\\Idle.png");
		mAni->Create(L"LeftIdle", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 55.0f), Vector2::Zero, 6, 0.25f);

		SpriteRenderer* arabianSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> arabianMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		arabianSr->SetMaterial(arabianMaterial);
		arabianSr->SetMesh(mesh);

		mAni->Play(L"LeftIdle", true);
	}
	void BossArabianScript::Update()
	{
	}
	void BossArabianScript::FixedUpdate()
	{
	}
	void BossArabianScript::Render()
	{
	}
	void BossArabianScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void BossArabianScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BossArabianScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void BossArabianScript::New()
	{
	}
	void BossArabianScript::Idle()
	{
	}
	void BossArabianScript::Move()
	{
	}
	void BossArabianScript::Attack()
	{
	}
	void BossArabianScript::Death()
	{
	}
	void BossArabianScript::AttackKnife()
	{
	}
}