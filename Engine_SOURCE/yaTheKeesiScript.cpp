#include "yaTheKeesiScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaCollider2D.h"
#include "yaAnimator.h"

#include "yaFlamestrikeScript.h"
#include "yaBossArabianScript.h"
#include "yaCompleteScript.h"


namespace ya
{
	TheKeesiScript::TheKeesiScript()
		: Script()
		, mTheKeesiState(TheKeesiState::IDLE)
		, mPlayer(nullptr)
		, playerTr(nullptr)
		, mTr(nullptr)
		, mTime(0.0f)
		, mbMove(false)
		, mRightEf(nullptr)
		, mLeftEf(nullptr)
		, mRightScript(nullptr)
		, mLeftScript(nullptr)
		, mIndex(0)
		, mStack(0)
	{
	}
	TheKeesiScript::~TheKeesiScript()
	{
	}
	void TheKeesiScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetName(L"TheKeesi");
		coll->SetType(eColliderType::Rect);
		coll->SetSize(Vector2(1.0f, 0.3f));

		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"TheKeesi", L"TheKeesi\\TheKeesi.png");
		ani->Create(L"TheKeesiIdle", texture, Vector2(0.0f, 0.0f), Vector2(202.0f, 93.0f), Vector2::Zero, 4, 0.1f);


		texture = Resources::Load<Texture>(L"TheKeesi2", L"TheKeesi\\TheKeesi2.png");
		ani->Create(L"TheKeesi2Idle", texture, Vector2(0.0f, 0.0f), Vector2(202.0f, 93.0f), Vector2::Zero, 4, 0.1f);

		texture = Resources::Load<Texture>(L"TheKeesi3", L"TheKeesi\\TheKeesi3.png");
		ani->Create(L"TheKeesi3Idle", texture, Vector2(0.0f, 0.0f), Vector2(202.0f, 93.0f), Vector2::Zero, 6, 0.1f);
		
		texture = Resources::Load<Texture>(L"TheKeesiDie", L"TheKeesi\\TheKeesiDie.png");
		ani->Create(L"TheKeesiDie", texture, Vector2(0.0f, 0.0f), Vector2(202.0f, 93.0f), Vector2::Zero, 1, 0.1f);
	
		ani->Play(L"TheKeesiIdle", true);
	}
	void TheKeesiScript::Update()
	{
		switch (mTheKeesiState)
		{
		case ya::TheKeesiScript::TheKeesiState::IDLE:
			Idle();
			break;
		case ya::TheKeesiScript::TheKeesiState::MOVE:
			Move();
			break;
		case ya::TheKeesiScript::TheKeesiState::MOVE2:
			Move2();
			break;
		case ya::TheKeesiScript::TheKeesiState::ATTACK:
			Attack();
			break;
		case ya::TheKeesiScript::TheKeesiState::DIE:
			Die();
			break;
		default:
			break;
		}

	}
	void TheKeesiScript::FixedUpdate()
	{
	}
	void TheKeesiScript::Render()
	{
	}
	void TheKeesiScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetName() == L"Tent")
			return;

		mStack++;
		if (mStack > 30)
		{
			mLeftScript->SetAttack(true);
			mRightScript->SetAttack(true);
			mbMove = false;
			Animator* ani = GetOwner()->GetComponent<Animator>();
			ani->Play(L"TheKeesi2Idle", true);
			mTheKeesiState = TheKeesiState::MOVE;
		}
	}
	void TheKeesiScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void TheKeesiScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void TheKeesiScript::Idle()
	{
		float y = mTr->GetPosition().y;

		if (y >= 4.0f)
		{
			mbMove = true;

		}
		if (y <= 3.5f)
		{
			mbMove = false;
		}
		if (!mbMove)
			y += 0.5f * Time::DeltaTime();
		if (mbMove)
			y -= 0.5f * Time::DeltaTime();

		mTr->SetPosition(Vector3(mTr->GetPosition().x, y, mTr->GetPosition().z));

		mTime += 2.0f * Time::DeltaTime();
		if (mTime > 30.0f)
		{
			mTheKeesiState = TheKeesiState::ATTACK;
		}
	}
	void TheKeesiScript::Move()
	{
		if (mStack > 50)
		{
			Animator* ani = GetOwner()->GetComponent<Animator>();
			ani->Play(L"TheKeesi3Idle", true);
			mTheKeesiState = TheKeesiState::MOVE2;
		}

		float x = mTr->GetPosition().x;

		if (x >= 165.0f)
		{
			mbMove = true;

		}
		if (x <= 163.0f)
		{
			mbMove = false;
		}
		if (!mbMove)
			x += 2.0f * Time::DeltaTime();
		if (mbMove)
			x -= 2.0f * Time::DeltaTime();

		mTr->SetPosition(Vector3(x, mTr->GetPosition().y, mTr->GetPosition().z));
		
	}
	void TheKeesiScript::Move2()
	{
		if (mStack > 70)
		{
			mTheKeesiState = TheKeesiState::DIE;
		}

		float x = mTr->GetPosition().x;

		if (x >= 165.0f)
		{
			mbMove = true;

		}
		if (x <= 163.0f)
		{
			mbMove = false;
		}
		if (!mbMove)
			x += 2.0f * Time::DeltaTime();
		if (mbMove)
			x -= 2.0f * Time::DeltaTime();

		mTr->SetPosition(Vector3(x, mTr->GetPosition().y, mTr->GetPosition().z));
	}
	void TheKeesiScript::Attack()
	{
		CreatMonster(mTr->GetPosition());
		mTime = 0.0f;
		mTheKeesiState = TheKeesiState::IDLE;
	}
	void TheKeesiScript::Attack2()
	{

	}
	void TheKeesiScript::Die()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		mLeftScript->SetAttack(false);
		mRightScript->SetAttack(false);

		float y = mTr->GetPosition().y;

		if (y <= -1.0f)
		{
			mbMove = true;
			ani->Play(L"TheKeesiDie", false);
			mTime += 2.0f * Time::DeltaTime();
			mCameraScript->strongEffectOn();

			if (mTime > 5.0f)
			{
				mCameraScript->strongEffectOff();
				CreateMissionClear();
			}
		}
		
	
		if (!mbMove)
			y -= 0.5f * Time::DeltaTime();

		mTr->SetPosition(Vector3(mTr->GetPosition().x, y, mTr->GetPosition().z));


	}
	void TheKeesiScript::End()
	{

	}

	void TheKeesiScript::CreateMissionClear()
	{
		GameObject* obj = object::Instantiate<GameObject>(eLayerType::UI);
		obj->SetName(L"M");
		Transform* tr = obj->GetComponent<Transform>();
		tr->SetPosition(Vector3(160.0f, 3.0f, 0.0f));
		tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

		obj->AddComponent<CompleteScript>();
	}

	void TheKeesiScript::CreatMonster(Vector3 position)
	{
		Arabian* arabian = object::CreateGameObject<Arabian>(eLayerType::Monster);
		Transform* arabianTr = arabian->GetComponent<Transform>();
		arabianTr->SetPosition(Vector3(position.x, 5.8f, 4.0f));
		arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

		BossArabianScript* script = arabian->AddComponent<BossArabianScript>();
	}
}