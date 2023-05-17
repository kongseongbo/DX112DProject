#include "yaCamelArabianScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaDeathScript.h"


namespace ya
{
	CamelArabianScript::CamelArabianScript()
		: Script()
		, eCamelArabianState(CamelArabianState::NEW)
		, obj (nullptr)
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

		texture = Resources::Load<Texture>(L"DownAttack", L"CamelArabian\\DownAttack.png");
		ani->Create(L"DownAttack", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 13, 0.15f);

		texture = Resources::Load<Texture>(L"DeathRun", L"CamelArabian\\DeathRun.png");
		ani->Create(L"DeathRun", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 100.0f), Vector2::Zero, 12, 0.15f);

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
		case ya::CamelArabianScript::CamelArabianState::DIE:
			Die();
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

		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_real_distribution<> distr(0, 4);

		int a = 0;

		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"Idle", true);

		if (mTime > 1.0f)
		{
			direction = distr(eng);
			ani->Play(L"Move", true);
			eCamelArabianState = CamelArabianState::MOVE;
			mTime = 0.0f;
		}

		if (Input::GetKeyDown(eKeyCode::Q))
		{
			ani->Play(L"DeathRun", true);
			eCamelArabianState = CamelArabianState::DIE;
		}

	}
	void CamelArabianScript::Move()
	{
		//mTr->SetPosition(Vector3(mTr->GetPosition().x - Time::DeltaTime(), mTr->GetPosition().y, mTr->GetPosition().z));
		Animator* ani = GetOwner()->GetComponent<Animator>();

			mTime += 2.0f * Time::DeltaTime();
		if (direction == 0 || direction == 1)
		{
			Vector3 pos = mTr->GetPosition();
			if(direction == 0)
				pos.x -= 2.0f * Time::DeltaTime();
			if(direction == 1)
				pos.x += 2.0f * Time::DeltaTime();
			mTr->SetPosition(pos);

			if (mTime > 2.0f)
			{
				ani->Play(L"Idle", true);
				eCamelArabianState = CamelArabianState::IDLE;
				mTime = 0.0f;
			}
		}

		if (direction == 2 )
		{
			ani->Play(L"Attack", false);
			eCamelArabianState = CamelArabianState::ATTACK;
			mTime = 0.0f;
		}

		if (direction == 3)
		{
			ani->Play(L"DownAttack", false);
			eCamelArabianState = CamelArabianState::ATTACK;
			mTime = 0.0f;
		}

	}
	void CamelArabianScript::Attack()
	{
		mTime += 2.0f * Time::DeltaTime();
		Animator* ani = GetOwner()->GetComponent<Animator>();
		if (mTime > 1.0f)
		{
			ani->Play(L"Idle", true);
			eCamelArabianState = CamelArabianState::IDLE;
			mTime = 0.0f;
		}
	}
	void CamelArabianScript::DownAttack()
	{
	}
	void CamelArabianScript::Die()
	{
		if (obj == nullptr)
		{
			obj = new CamelArabianDeathObj();
			DeathScript* scr = obj->AddComponent<DeathScript>();
			Transform* objTr = scr->GetOwner()->GetComponent<Transform>();
			objTr->SetPosition(mTr->GetPosition());
			objTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
		}
		mTr->SetPosition(Vector3(mTr->GetPosition().x - (10.0f * Time::DeltaTime()), mTr->GetPosition().y, mTr->GetPosition().z));
		
	}
}