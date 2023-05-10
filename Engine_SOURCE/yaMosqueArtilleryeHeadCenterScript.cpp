#include "yaMosqueArtilleryeHeadCenterScript.h"
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
	MosqueArtilleryeHeadCenterScript::MosqueArtilleryeHeadCenterScript()
		: Script()
		, mbStartAni(false)
		, stack(0)
		, eState(State::NONE)
		, mTime(0.0f)
	{
	}
	MosqueArtilleryeHeadCenterScript::~MosqueArtilleryeHeadCenterScript()
	{
	}
	void MosqueArtilleryeHeadCenterScript::Initalize()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MosqueArtilleryeHeadCenter", L"MosqueArtillery\\MosqueArtilleryeHeadCenter.png");
		ani->Create(L"MosqueArtilleryeHeadCenter", texture, Vector2(0.0f, 0.0f), Vector2(90.0f, 138.0f), Vector2(0.0f, 0.0f), 1, 0.2f);

		texture = Resources::Load<Texture>(L"MosqueArtilleryMoon", L"MosqueArtillery\\MosqueArtilleryeHeadCenterOpen.png");
		ani->Create(L"MosqueArtilleryeHeadCenterOpen", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 148.0f), Vector2(0.0f,-0.02f), 16, 0.2f);

		texture = Resources::Load<Texture>(L"CenterCurtain", L"MosqueArtillery\\MosqueArtilleryeHeadCenterOpen.png");
		ani->Create(L"CenterCurtain", texture, Vector2(0.0f, 148.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 12, 0.2f);

		texture = Resources::Load<Texture>(L"CenterAttack", L"MosqueArtillery\\MosqueArtilleryeHeadCenterOpen.png");
		ani->Create(L"CenterAttack", texture, Vector2(0.0f, 296.0f), Vector2(100.0f, 148.0f), Vector2(0.0f, -0.02f), 5, 0.2f);

		ani->Play(L"MosqueArtilleryeHeadCenter", false);


		ani->GetCompleteEvent(L"MosqueArtilleryeHeadCenterOpen") = std::bind(&MosqueArtilleryeHeadCenterScript::NewBoss, this);
	}
	void MosqueArtilleryeHeadCenterScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		if (mbStartAni && stack == 0)
		{
			ani->Play(L"MosqueArtilleryeHeadCenterOpen", false);
			
			stack++;
		}

		switch (eState)
		{
		case ya::MosqueArtilleryeHeadCenterScript::State::IDLE:
			Idle();
			break;
		case ya::MosqueArtilleryeHeadCenterScript::State::ATTCK:
			Attack();
			break;
		case ya::MosqueArtilleryeHeadCenterScript::State::DIE:
			Die();
			break;
		default:
			break;
		}

	}
	void MosqueArtilleryeHeadCenterScript::FixedUpdate()
	{
	}
	void MosqueArtilleryeHeadCenterScript::Render()
	{
	}
	void MosqueArtilleryeHeadCenterScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadCenterScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MosqueArtilleryeHeadCenterScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void MosqueArtilleryeHeadCenterScript::NewBoss()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"CenterCurtain", false);
		eState = State::IDLE;
	}
	void MosqueArtilleryeHeadCenterScript::Idle()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		

		mTime += 1.5f * Time::DeltaTime();
		if (mTime > 4.0f)
		{
			
			ani->Play(L"CenterAttack", false);
			eState = State::ATTCK;

		}

	}
	void MosqueArtilleryeHeadCenterScript::Attack()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		MosqueArtilleryBullet* bullet = new MosqueArtilleryBullet();
		MosqueArtilleryBulletScript* script = bullet->AddComponent<MosqueArtilleryBulletScript>();
		script->SetTarget(mPlayer->GetComponent<Transform>()->GetPosition());
		Transform* bulletTr = bullet->GetComponent<Transform>();
		bulletTr->SetPosition(Vector3(tr->GetPosition().x, tr->GetPosition().y ,tr->GetPosition().z - 1.0f));
		

		mTime = 0.0f;
		eState = State::IDLE;
	}
	void MosqueArtilleryeHeadCenterScript::Die()
	{
	}
}