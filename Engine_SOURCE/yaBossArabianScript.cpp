#include "yaBossArabianScript.h"
#include "yaSceneManager.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"

namespace ya
{
	BossArabianScript::BossArabianScript()
		: Script()
		, mBossArabianState(BossArabianState::NEW)
		, mAni(nullptr)
		, mTr(nullptr)
		, mTime(0.0f)
		, index(0)
		, direction(0)

	{
	}
	BossArabianScript::~BossArabianScript()
	{
	}
	void BossArabianScript::Initalize()
	{
		mAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"ArabianIdle", L"Arabian\\Idle.png");
		mAni->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 55.0f), Vector2::Zero, 6, 0.25f);

		texture = Resources::Load<Texture>(L"ArabianMove", L"Arabian\\Move.png");
		mAni->Create(L"LeftMove", texture, Vector2(0.0f, 0.0f), Vector2(54.0f, 52.0f), Vector2(0.05f, 0.0f), 12, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianMove", L"Arabian\\Move.png");
		mAni->Create(L"RightMove", texture, Vector2(0.0f, 52.0f), Vector2(54.0f, 52.0f), Vector2(0.05f, 0.0f), 12, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianAttack", L"Arabian\\Attack.png");
		mAni->Create(L"Attack", texture, Vector2(0.0f, 0.0f), Vector2(90.0f, 65.0f), Vector2::Zero, 8, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianDeath", L"Arabian\\Death.png");
		mAni->Create(L"Death", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 50.0f), Vector2::Zero, 11, 0.1f);

		texture = Resources::Load<Texture>(L"BombDeath", L"Arabian\\BombDeath.png");
		mAni->Create(L"BombDeath", texture, Vector2(0.0f, 0.0f), Vector2(80.0f, 60.0f), Vector2::Zero, 13, 0.1f);

		texture = Resources::Load<Texture>(L"ArabianAttack2", L"Arabian\\Attack2.png");
		mAni->Create(L"KnifeAttack2", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 60.0f), Vector2(0.0f, -0.05), 19, 0.1f);

		texture = Resources::Load<Texture>(L"S", L"Arabian\\S.png");
		mAni->Create(L"S", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 55.0f), Vector2(0.01f, 0.0f), 4, 0.3f);

		SpriteRenderer* arabianSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> arabianMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		arabianSr->SetMaterial(arabianMaterial);
		arabianSr->SetMesh(mesh);

		mAni->Play(L"RightMove", true);
	}
	void BossArabianScript::Update()
	{
		switch (mBossArabianState)
		{
		case ya::BossArabianScript::BossArabianState::NEW:
			New();
			break;
		case ya::BossArabianScript::BossArabianState::IDLE:
			Idle();
			break;
		case ya::BossArabianScript::BossArabianState::MOVE:
			Move();
			break;
		case ya::BossArabianScript::BossArabianState::ATTACK:
			Attack();
			break;
		case ya::BossArabianScript::BossArabianState::DEATH:
			Death();
			break;
		default:
			break;
		}
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