#include "yaBradleyScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaCollider2D.h"
#include "yaScene.h"
#include "yaBradleyBulletScript.h"
#include "yaBradleyBulletEffectScript.h"
#include "yaAnimator.h"
#include "yaBradleyBulletEffect.h"
#include "yaRigidbody.h"

namespace ya
{
	BradleyScript::BradleyScript()
		: Script()
		, eBradleyState(BradleyState::IDLE)
		, mTr(nullptr)
		, mBullet(nullptr)
		, mTime(0.0f)
		, direction(0)
		, index(0)
		, mbBullet(false)
	{
	}
	BradleyScript::~BradleyScript()
	{
	}
	void BradleyScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		Collider2D* coll = GetOwner()->GetComponent<Collider2D>();
		coll->SetType(eColliderType::Rect);
		coll->SetCenter(Vector2(0.0f, 0.0f));
		coll->SetSize(Vector2(0.2f, 0.2f));
		
		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Bradley", L"Bradley\\Bradley.png");
		ani->Create(L"BradleyIdle", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 8, 0.2f);
		ani->Create(L"BradleyIdle2", texture, Vector2(0.0f, 90.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 8, 0.2f);

		ani->Create(L"BradleyStance", texture, Vector2(0.0f, 180.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 9, 0.2f);
		ani->Create(L"BradleyStance2", texture, Vector2(0.0f, 270.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 9, 0.2f);

		ani->Create(L"BradleyAttack", texture, Vector2(0.0f, 360.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 7, 0.1f);
		ani->Create(L"BradleyAttack2", texture, Vector2(0.0f, 440.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 7, 0.1f);

		ani->Create(L"BradleyDeath", texture, Vector2(0.0f, 540.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 8, 0.1f);
		ani->Create(L"BradleyDeath2", texture, Vector2(0.0f, 630.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 8, 0.1f);

		//ani->GetEvent(L"Attack", 2) = std::bind(&BradleyScript::CreateBullet, this);
		//ani->GetEvent(L"CamelArabianDownAttack", 9) = std::bind(&BradleyScript::CreateBullet, this);
		//ani->GetCompleteEvent(L"New") = std::bind(&BradleyScript::Idle, this);

		ani->Play(L"BradleyIdle", true);
	}
	void BradleyScript::Update()
	{
		switch (eBradleyState)
		{
		case ya::BradleyScript::BradleyState::IDLE:
			Idle();
			break;
		case ya::BradleyScript::BradleyState::MOVE:
			Move();
			break;
		case ya::BradleyScript::BradleyState::ATTACK:
			Attack();
			break;
		case ya::BradleyScript::BradleyState::DOWNATTACK:
			DownAttack();
			break;
		case ya::BradleyScript::BradleyState::DIE:
			Die();
			break;
		default:
			break;
		}
	}
	void BradleyScript::FixedUpdate()
	{
	}
	void BradleyScript::Render()
	{
	}
	void BradleyScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void BradleyScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BradleyScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void BradleyScript::Idle()
	{
		mTime += 2.0f * Time::DeltaTime();
		mbBullet = false;

		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_real_distribution<> distr(0, 4);

		direction = distr(eng);
		Animator* ani = GetOwner()->GetComponent<Animator>();

		if (index == 4)
		{
			ani->Play(L"BradleyIdle", true);
			if (mTime > 5.0f)
				index = 0;

		}
		if (mTime > 2.0f && index < 4)
		{
			mTime = 0.0f;
			eBradleyState = BradleyState::ATTACK;
		}
	}
	void BradleyScript::Move()
	{
	}
	void BradleyScript::Attack()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"BradleyAttack", false);
		mbBullet = false;
		CreateBullet();
		index++;
		mTime = 0.0f;
		eBradleyState = BradleyState::IDLE;
	}
	void BradleyScript::DownAttack()
	{
	}
	void BradleyScript::Die()
	{
	}
	void BradleyScript::CreateBullet()
	{
		if (!mbBullet)
		{
			mBullet = new BradleyBullet();
			mBullet->AddComponent<BradleyBulletScript>();
			Transform* tr = mBullet->GetComponent<Transform>();
			tr->SetPosition(mTr->GetPosition());
			tr->SetRotation(Vector3(tr->GetRotation().x, tr->GetRotation().y, -70.0f));
			tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			BradleyBulletEffect* effect = new BradleyBulletEffect();
			effect->AddComponent<BradleyBulletEffectScript>();
			Transform* effectTr = effect->GetComponent<Transform>();
			effectTr->SetPosition(Vector3(tr->GetPosition().x + 0.5f, tr->GetPosition().y + 0.5f, tr->GetPosition().z));
			//effectTr->SetRotation(Vector3(effectTr->GetRotation().x, effectTr->GetRotation().y, -70.0f));
			effectTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			mbBullet = true;
		
		}
	}
}