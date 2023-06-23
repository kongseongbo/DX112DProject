#include "yaMosqueArtilleryeHeadRightScript.h"
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
	MosqueArtilleryeHeadRightScript::MosqueArtilleryeHeadRightScript()
		: Script()
		, eState(State::NONE)
		, mPlayer(nullptr)
		, mbStartAni(false)
		, mHp(10)
		, stack(0)
		, mTime(0.0f)
	{
	}
	MosqueArtilleryeHeadRightScript::~MosqueArtilleryeHeadRightScript()
	{
	}
	void MosqueArtilleryeHeadRightScript::Initalize()
	{
		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetType(eColliderType::Rect);
		coll->SetSize(Vector2(0.25f, 0.01f));

		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryHeadRight", L"MosqueArtillery\\MosqueArtilleryeHeadRight.png");
		ani->Create(L"MosqueArtilleryHeadRight", texture, Vector2(0.0f, 0.0f), Vector2(88.0f, 139.0f), Vector2(0.0f, 0.0f), 1, 0.2f);

		texture = Resources::Load<Texture>(L"MosqueArtilleryeHeadRightOpen", L"MosqueArtillery\\MosqueArtilleryeHeadRightOpen.png");
		ani->Create(L"MosqueArtilleryHeadRightOpen", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 16, 0.2f);
		ani->Create(L"RightCurtain", texture, Vector2(0.0f, 148.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 12, 0.2f);
		ani->Create(L"RightAttack", texture, Vector2(0.0f, 296.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 5, 0.2f);

		texture = Resources::Load<Texture>(L"MosqueArtilleryDestroy", L"MosqueArtillery\\MosqueArtilleryDestroy.png");
		ani->Create(L"RightDestroy", texture, Vector2(0.0f, 224.0f), Vector2(148.0f, 112.0f), Vector2(-0.075f, 0.0f), 1, 0.2f);

		ani->GetCompleteEvent(L"MosqueArtilleryHeadRightOpen") = std::bind(&MosqueArtilleryeHeadRightScript::NewBoss, this);

		ani->Play(L"MosqueArtilleryHeadRight", false);
	}
	void MosqueArtilleryeHeadRightScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		if (mbStartAni && stack == 0)
		{
			ani->Play(L"MosqueArtilleryHeadRightOpen", false);

			stack++;
		}

		switch (eState)
		{
		case ya::MosqueArtilleryeHeadRightScript::State::IDLE:
			Idle();
			break;
		case ya::MosqueArtilleryeHeadRightScript::State::ATTCK:
			Attack();
			break;
		case ya::MosqueArtilleryeHeadRightScript::State::DIE:
			Die();
			break;
		default:
			break;
		}
	}
	void MosqueArtilleryeHeadRightScript::FixedUpdate()
	{
	}
	void MosqueArtilleryeHeadRightScript::Render()
	{
	}
	void MosqueArtilleryeHeadRightScript::OnCollisionEnter(Collider2D* collider)
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		mHp--;
		if (mHp <= 0)
		{
			ani->Play(L"RightDestroy", false);
			eState = State::DIE;
			GetOwner()->Pause();
		}
	}
	void MosqueArtilleryeHeadRightScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadRightScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void MosqueArtilleryeHeadRightScript::NewBoss()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"RightCurtain", false);
		eState = State::IDLE;
		
	}
	void MosqueArtilleryeHeadRightScript::Idle()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();


		mTime += 1.5f * Time::DeltaTime();
		if (mTime > 3.5f)
		{

			ani->Play(L"RightAttack", false);
			eState = State::ATTCK;

		}
	}
	void MosqueArtilleryeHeadRightScript::Attack()
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
	void MosqueArtilleryeHeadRightScript::Die()
	{
	}
}