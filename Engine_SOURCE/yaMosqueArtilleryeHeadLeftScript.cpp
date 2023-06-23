#include "yaMosqueArtilleryeHeadLeftScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaAnimator.h"
#include "yaMosqueArtilleryBullet.h"
#include "yaMosqueArtilleryBulletScript.h"


namespace ya
{
	MosqueArtilleryeHeadLeftScript::MosqueArtilleryeHeadLeftScript()
		: Script()
		, eState(State::NONE)
		, mPlayer(nullptr)
		, mbStartAni(false)
		, stack(0)
		, mHp(10)
		, mTime(0.0f)
	{

	}
	MosqueArtilleryeHeadLeftScript::~MosqueArtilleryeHeadLeftScript()
	{
	}
	void MosqueArtilleryeHeadLeftScript::Initalize()
	{
		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetType(eColliderType::Rect);
		coll->SetSize(Vector2(0.25f, 0.01f));

		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryeHeadLeft", L"MosqueArtillery\\MosqueArtilleryeHeadLeft.png");
		ani->Create(L"MosqueArtilleryeHeadLeft", texture, Vector2(0.0f, 0.0f), Vector2(89.0f, 138.0f), Vector2(0.0f, 0.0f), 1, 0.2f);

		texture = Resources::Load<Texture>(L"MosqueArtilleryeHeadLeftOpen", L"MosqueArtillery\\MosqueArtilleryeHeadLeftOpen.png");
		ani->Create(L"MosqueArtilleryeHeadLeftOpen", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 16, 0.2f);
		ani->Create(L"LeftCurtain", texture, Vector2(0.0f, 148.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 12, 0.2f);
		ani->Create(L"LeftAttack", texture, Vector2(0.0f, 296.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 5, 0.2f);

		texture = Resources::Load<Texture>(L"MosqueArtilleryDestroy", L"MosqueArtillery\\MosqueArtilleryDestroy.png");
		ani->Create(L"LeftDestroy", texture, Vector2(0.0f, 0.0f), Vector2(148.0f, 114.0f), Vector2(0.1f, 0.0f), 1, 0.2f);

		ani->GetCompleteEvent(L"MosqueArtilleryeHeadLeftOpen") = std::bind(&MosqueArtilleryeHeadLeftScript::NewBoss, this);

		ani->Play(L"MosqueArtilleryeHeadLeft", false);
	}
	void MosqueArtilleryeHeadLeftScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		if (mbStartAni && stack == 0)
		{
			ani->Play(L"MosqueArtilleryeHeadLeftOpen", false);

			stack++;
		}

		switch (eState)
		{
		case ya::MosqueArtilleryeHeadLeftScript::State::IDLE:
			Idle();
			break;
		case ya::MosqueArtilleryeHeadLeftScript::State::ATTCK:
			Attack();
			break;
		case ya::MosqueArtilleryeHeadLeftScript::State::DIE:
			Die();
			break;
		default:
			break;
		}
	}
	void MosqueArtilleryeHeadLeftScript::FixedUpdate()
	{
	}
	void MosqueArtilleryeHeadLeftScript::Render()
	{
	}
	void MosqueArtilleryeHeadLeftScript::OnCollisionEnter(Collider2D* collider)
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		mHp--;
		if (mHp <= 0)
		{
			ani->Play(L"LeftDestroy", false);
			eState = State::DIE;
			GetOwner()->Pause();
		}
	}
	void MosqueArtilleryeHeadLeftScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadLeftScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void MosqueArtilleryeHeadLeftScript::NewBoss()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"LeftCurtain", false);
		eState = State::IDLE;
	}


	void MosqueArtilleryeHeadLeftScript::Idle()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();


		mTime += 1.5f * Time::DeltaTime();
		if (mTime > 3.0f)
		{

			ani->Play(L"LeftAttack", false);
			eState = State::ATTCK;

		}

	}
	void MosqueArtilleryeHeadLeftScript::Attack()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		MosqueArtilleryBullet* bullet = new MosqueArtilleryBullet();
		MosqueArtilleryBulletScript* script = bullet->AddComponent<MosqueArtilleryBulletScript>();
		script->SetTarget(mPlayer->GetComponent<Transform>()->GetPosition());
		Transform* bulletTr = bullet->GetComponent<Transform>();
		bulletTr->SetPosition(Vector3(tr->GetPosition().x, tr->GetPosition().y, tr->GetPosition().z - 1.0f));


		mTime = 0.0f;
		eState = State::IDLE;
	}
	void MosqueArtilleryeHeadLeftScript::Die()
	{
	}
}