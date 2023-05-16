#include "yaCamelArabianScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaInput.h"


namespace ya
{
	CamelArabianScript::CamelArabianScript()
		: Script()
		, eCamelArabianState(CamelArabianState::NEW)
		, mTr(nullptr)
		, mTime(0.0f)
		, direction(0)
		, index(0)
	{
	}
	CamelArabianScript::~CamelArabianScript()
	{
	}
	void CamelArabianScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		Collider2D* arabianColl = GetOwner()->AddComponent<Collider2D>();
		arabianColl->SetType(eColliderType::Rect);
		arabianColl->SetCenter(Vector2(0.0f, 0.0f));
		arabianColl->SetSize(Vector2(0.2f, 0.2f));

		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"CamelArabian", L"CamelArabian\\New.png");
		ani->Create(L"New", texture, Vector2(0.0f, 0.0f), Vector2(83.33f, 100.0f), Vector2::Zero, 12, 0.2f);

		texture = Resources::Load<Texture>(L"Idle", L"CamelArabian\\Idle.png");
		ani->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 3, 0.2f);

		texture = Resources::Load<Texture>(L"Move", L"CamelArabian\\Move.png");
		ani->Create(L"Move", texture, Vector2(0.0f, 0.0f), Vector2(83.33f, 100.0f), Vector2::Zero, 12, 0.1f);

		texture = Resources::Load<Texture>(L"Attack", L"CamelArabian\\Attack.png");
		ani->Create(L"Attack", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 10, 0.1f);

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(material);
		sr->SetMesh(mesh);


		ani->GetCompleteEvent(L"New") = std::bind(&CamelArabianScript::Idle, this);

		ani->Play(L"New", false);
	}
	void CamelArabianScript::Update()
	{
		switch (eCamelArabianState)
		{
		case ya::CamelArabianScript::CamelArabianState::NEW:
			New();
			break;
		case ya::CamelArabianScript::CamelArabianState::IDLE:
			Idle();
			break;
		case ya::CamelArabianScript::CamelArabianState::MOVE:
			Move();
			break;
		case ya::CamelArabianScript::CamelArabianState::ATTACK:
			Attack();
			break;
		case ya::CamelArabianScript::CamelArabianState::DOWNATTACK:
			DownAttack();
			break;
		case ya::CamelArabianScript::CamelArabianState::DEATH:
			Death();
			break;
		default:
			break;
		}

	}
	void CamelArabianScript::FixedUpdate()
	{
	}
	void CamelArabianScript::Render()
	{
	}
	void CamelArabianScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void CamelArabianScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void CamelArabianScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void CamelArabianScript::New()
	{
		mTr->SetPosition(Vector3(mTr->GetPosition().x - Time::DeltaTime(), mTr->GetPosition().y, mTr->GetPosition().z));

	}
	void CamelArabianScript::Idle()
	{
		eCamelArabianState = CamelArabianState::IDLE;
		mTime += 2.0f * Time::DeltaTime();

		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"Idle", true);

		if (mTime > 3.0f)
		{
			ani->Play(L"Move", true);
			eCamelArabianState = CamelArabianState::MOVE;
			mTime = 0.0f;
		}

	}
	void CamelArabianScript::Move()
	{
		mTr->SetPosition(Vector3(mTr->GetPosition().x - Time::DeltaTime(), mTr->GetPosition().y, mTr->GetPosition().z));

		mTime += 2.0f * Time::DeltaTime();
		Animator* ani = GetOwner()->GetComponent<Animator>();
		if (mTime > 3.0f)
		{
			ani->Play(L"Attack", true);
			eCamelArabianState = CamelArabianState::ATTACK;
			mTime = 0.0f;
		}
	}
	void CamelArabianScript::Attack()
	{
	}
	void CamelArabianScript::DownAttack()
	{
	}
	void CamelArabianScript::Death()
	{
	}
}