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

namespace ya
{
	TheKeesiScript::TheKeesiScript()
		: Script()
		, eTheKeesiState(TheKeesiState::IDLE)
		, mPlayer(nullptr)
		, playerTr(nullptr)
		, mTr(nullptr)
		, mTime(0.0f)
		, mbMove(false)
		, mRightEf(nullptr)
		, mLeftEf(nullptr)
		, mRightScript(nullptr)
		, mLeftScript(nullptr)
		, mArabian(nullptr)
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
		coll->SetSize(Vector2(1.0f, 0.5f));

		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"TheKeesi", L"TheKeesi\\TheKeesi.png");
		ani->Create(L"TheKeesiIdle", texture, Vector2(0.0f, 0.0f), Vector2(202.0f, 93.0f), Vector2::Zero, 4, 0.1f);
		ani->Play(L"TheKeesiIdle", true);
	}
	void TheKeesiScript::Update()
	{

		float y = mTr->GetPosition().y;

		if (y >= 5.0f)
		{
			mbMove = true;

		}
		if(y <= 4.0f)
		{
			mbMove = false;
		}
		if(!mbMove)
			y += 0.5f * Time::DeltaTime();
		if(mbMove)
			y -= 0.5f * Time::DeltaTime();

		mTr->SetPosition(Vector3(mTr->GetPosition().x, y, mTr->GetPosition().z));

		mTime += 2.0f * Time::DeltaTime(); 
		if (mTime > 5.0f)
		{
			CreatMonster(mTr->GetPosition());
			mTime = 0.0f;
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
		mLeftScript->SetAttack(true);
		mRightScript->SetAttack(true);
	}
	void TheKeesiScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void TheKeesiScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void TheKeesiScript::Idle()
	{
	}
	void TheKeesiScript::Move()
	{
	}
	void TheKeesiScript::Attack()
	{

	}
	void TheKeesiScript::Attack2()
	{

	}
	void TheKeesiScript::Die()
	{
	}
	void TheKeesiScript::End()
	{
	}

	void TheKeesiScript::CreatMonster(Vector3 position)
	{
		{
			GameObject* arabian = object::Instantiate<GameObject>(eLayerType::Monster);
			Transform* arabianTr = arabian->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x , -3.0f, 4.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			BossArabianScript* script = arabian->AddComponent<BossArabianScript>();
		}
	}
}