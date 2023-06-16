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
#include "yaAnimator.h"
#include "yaBradleyBulletScript.h"
#include "yaBradleyBulletEffectScript.h"
#include "yaBradleyBulletEffect.h"
#include "yaRigidbody.h"

namespace ya
{
	BradleyScript::BradleyScript()
		: Script()
		, eBradleyState(BradleyState::IDLE)
		, eStanceState(StanceState::HOWITZER)
		, mTr(nullptr)
		, mBullet(nullptr)
		, mTime(0.0f)
		, direction(0)
		, index(0)
		, mStack(0)
		, mbBullet(false)
	{
	}
	BradleyScript::~BradleyScript()
	{
	}
	void BradleyScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetName(L"Rect");
		coll->SetType(eColliderType::Rect);
		coll->SetSize(Vector2(0.3f, 0.3f));
		
		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Bradley", L"Bradley\\Bradley.png");
		ani->Create(L"BradleyIdle", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 8, 0.2f);
		ani->Create(L"BradleyIdle2", texture, Vector2(0.0f, 90.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 8, 0.2f);

		ani->Create(L"BradleyStance", texture, Vector2(0.0f, 180.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 9, 0.2f);
		ani->Create(L"BradleyStance2", texture, Vector2(0.0f, 270.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 9, 0.2f);

		ani->Create(L"BradleyAttack", texture, Vector2(0.0f, 360.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 7, 0.1f);
		ani->Create(L"BradleyAttack2", texture, Vector2(0.0f, 450.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 7, 0.1f);

		ani->Create(L"BradleyDeath", texture, Vector2(0.0f, 540.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 8, 0.1f);
		ani->Create(L"BradleyDeath2", texture, Vector2(0.0f, 630.0f), Vector2(100.0f, 90.0f), Vector2::Zero, 8, 0.1f);

		//ani->GetEvent(L"Attack", 2) = std::bind(&BradleyScript::CreateBullet, this);
		//ani->GetEvent(L"CamelArabianDownAttack", 9) = std::bind(&BradleyScript::CreateBullet, this);
		ani->GetCompleteEvent(L"BradleyDeath") = std::bind(&BradleyScript::End, this);
		ani->GetCompleteEvent(L"BradleyDeath2") = std::bind(&BradleyScript::End, this);

		ani->Play(L"BradleyIdle", true);
	}
	void BradleyScript::Update()
	{
		playerTr = mPlayer->GetComponent<Transform>();
		direction = mTr->GetPosition().x - playerTr->GetPosition().x;

		switch (eBradleyState)
		{
		case ya::BradleyScript::BradleyState::IDLE:
			Idle();
			break;
		case ya::BradleyScript::BradleyState::MOVE:
			Move();
			break;
		case ya::BradleyScript::BradleyState::STANCECHANGE:
			StanceChange();
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
		Animator* ani = GetOwner()->GetComponent<Animator>();
	
		mStack++;
		if (mStack == 47)
		{
			if (eStanceState == StanceState::HOWITZER)
				ani->Play(L"BradleyDeath", false);
			if (eStanceState == StanceState::NORMAL)
				ani->Play(L"BradleyDeath2", false);
			eBradleyState = BradleyState::DIE;
		}
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
		Animator* ani = GetOwner()->GetComponent<Animator>();

		//std::random_device rd;
		//std::mt19937 eng(rd());
		//std::uniform_real_distribution<> distr(0, 4);
		//direction = distr(eng);

		if (direction < 10.0f && eStanceState == StanceState::HOWITZER)
		{
			ani->Play(L"BradleyStance", false);
			eBradleyState = BradleyState::STANCECHANGE;
			eStanceState = StanceState::NORMAL;
		}
		if (direction >= 10.0f && eStanceState == StanceState::NORMAL)
		{
			ani->Play(L"BradleyStance2", false);
			eBradleyState = BradleyState::STANCECHANGE;
			eStanceState = StanceState::HOWITZER;
		}

		if (index == 4 && eStanceState == StanceState::HOWITZER)
		{
			ani->Play(L"BradleyIdle", true);
			if (mTime > 5.0f)
				index = 0;
		}
		if (index == 4 && eStanceState == StanceState::NORMAL)
		{
			ani->Play(L"BradleyIdle2", true);
			if (mTime > 5.0f)
				index = 0;
		}

		if (mTime > 3.0f && index < 4)
		{
			mTime = 0.0f;
			eBradleyState = BradleyState::ATTACK;
		}
	}
	void BradleyScript::Move()
	{
	}
	void BradleyScript::StanceChange()
	{
		eBradleyState = BradleyState::IDLE;
	}
	void BradleyScript::Attack()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		if (eStanceState == StanceState::HOWITZER)
		{
			ani->Play(L"BradleyAttack", false);
			mbBullet = false;
			CreateBullet(-70.0f);
			index++;
			mTime = 0.0f;
		}
		if (eStanceState == StanceState::NORMAL)
		{
			ani->Play(L"BradleyAttack2", false);
			mbBullet = false;
			CreateBullet(0.0f);
			index++;
			mTime = 0.0f;
		}

		eBradleyState = BradleyState::IDLE;
	}
	void BradleyScript::DownAttack()
	{
	}
	void BradleyScript::Die()
	{
		
	}
	void BradleyScript::End()
	{
		GetOwner()->Death();
	}
	void BradleyScript::CreateBullet(float rotation)
	{
		if (!mbBullet)
		{
			
			mBullet = new BradleyBullet();
			BradleyBulletScript* script = mBullet->AddComponent<BradleyBulletScript>();
			script->SetRot(rotation);
			Transform* tr = mBullet->GetComponent<Transform>();
			tr->SetPosition(mTr->GetPosition());
			tr->SetRotation(Vector3(tr->GetRotation().x, tr->GetRotation().y, rotation));
			tr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
			
			BradleyBulletEffect* effect = new BradleyBulletEffect();
			effect->AddComponent<BradleyBulletEffectScript>();
			Transform* effectTr = effect->GetComponent<Transform>();
			if(eStanceState == StanceState::HOWITZER)
				effectTr->SetPosition(Vector3(tr->GetPosition().x + 3.5f, tr->GetPosition().y - 2.3f, tr->GetPosition().z));
			if (eStanceState == StanceState::NORMAL)
			{
				effectTr->SetPosition(Vector3(tr->GetPosition().x + 4.f, tr->GetPosition().y , tr->GetPosition().z));
				effectTr->SetRotation(Vector3(effectTr->GetRotation().x, effectTr->GetRotation().y, 42.0f));

			}
			effectTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			mbBullet = true;
		
		}
	}
}