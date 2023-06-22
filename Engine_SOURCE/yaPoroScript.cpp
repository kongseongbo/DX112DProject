#include "yaPoroScript.h"
#include "yaAnimator.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaObject.h"
#include "yaTime.h"

#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaFmod.h"
#include "yaAudioSource.h"

#include "yaMachineGun.h"
#include "yaMachineGunScript.h"


namespace ya
{
	PoroScript::PoroScript()
		: Script()
		, mPoroState(PoroState::IDLE)
		, mTr(nullptr)
		, mMoveTime(0.0f)
		, mStack(0)
		, mtime(0.0f)
	{
	}
	PoroScript::~PoroScript()
	{
	}
	void PoroScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"PoroIdle", L"Poro\\Idle.png");
		ani->Create(L"PoroIdle", texture, Vector2(0.0f, 0.0f), Vector2(44.0f, 54.0f), Vector2::Zero, 9, 0.2f);

		texture = Resources::Load<Texture>(L"PoroRescue", L"Poro\\Rescue.png");
		ani->Create(L"PoroRescue", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 56.0f), Vector2::Zero, 10, 0.1f);

		texture = Resources::Load<Texture>(L"PoroMove", L"Poro\\Move.png");
		ani->Create(L"PoroMoveLeft", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 45.0f), Vector2::Zero, 12, 0.2f);
		ani->Create(L"PoroMoveRight", texture, Vector2(0.0f, 45.0f), Vector2(40.0f, 45.0f), Vector2::Zero, 12, 0.2f);

		texture = Resources::Load<Texture>(L"Motion", L"Poro\\Motion.png");
		ani->Create(L"CreateItem", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 49.33f), Vector2::Zero, 11, 0.2f);
		ani->Create(L"salute", texture, Vector2(0.0f, 49.33f), Vector2(60.0f, 49.33f), Vector2::Zero, 14, 0.15f);
		ani->Create(L"Run", texture, Vector2(0.0f, 98.66f), Vector2(60.0f, 49.33f), Vector2::Zero, 8, 0.1f);

		SpriteRenderer* arabianSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> arabianMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		arabianSr->SetMaterial(arabianMaterial);
		arabianSr->SetMesh(mesh);

		ani->GetCompleteEvent(L"PoroRescue") = std::bind(&PoroScript::End, this);
		ani->GetCompleteEvent(L"CreateItem") = std::bind(&PoroScript::Item, this);
		ani->GetCompleteEvent(L"salute") = std::bind(&PoroScript::Death, this);

		ani->Play(L"PoroIdle", true);

		AudioSource* aaa = GetOwner()->AddComponent<AudioSource>();
		std::shared_ptr<AudioClip> myAudioClip = Resources::Load<AudioClip>(L"thankyou", L"Sound\\thankyou.mp3");
		aaa->SetClip(myAudioClip);
		aaa->SetLoop(false);
	}
	void PoroScript::Update()
	{
		switch (mPoroState)
		{
		case ya::PoroScript::PoroState::IDLE:
			Idle();
			break;
		case ya::PoroScript::PoroState::MOVE:
			Move();
			break;
		case ya::PoroScript::PoroState::ITEM:
			Item();
			break;
		case ya::PoroScript::PoroState::DEATH:
			Death();
			break;
		default:
			break;
		}
	}
	void PoroScript::FixedUpdate()
	{
	}
	void PoroScript::Render()
	{
	}
	void PoroScript::OnCollisionEnter(Collider2D* collider)
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		AudioSource* aaa = GetOwner()->GetComponent<AudioSource>();
		
		if ((collider->GetOwner()->GetLayerType() == eLayerType::Player || collider->GetOwner()->GetName() == L"Head") && mStack == 1)
		{
			mStack++;
			aaa->Play();
			ani->Play(L"CreateItem", false);
			mPoroState = PoroState::IDLE;
		}
		else
		{
			if (mStack == 0)
			{
				ani->Play(L"PoroRescue", false);
				mStack++;
			}
		}
	}
	void PoroScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void PoroScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void PoroScript::Idle()
	{
	}
	void PoroScript::Move()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();


		Vector3 pos = mTr->GetPosition();
		mMoveTime += 2.0f * Time::DeltaTime();
		if (mMoveTime < 2.0f)
		{
			if (!ani->IsAnimationRunning(L"PoroMoveLeft"))
				ani->Play(L"PoroMoveLeft", true);

			pos.x -= 2.0f * Time::DeltaTime();
			mTr->SetPosition(pos);

		}
		if (mMoveTime < 4.0f && mMoveTime > 2.0f)
		{
			if(!ani->IsAnimationRunning(L"PoroMoveRight"))
				ani->Play(L"PoroMoveRight", true);

			pos.x += 2.0f * Time::DeltaTime();
			mTr->SetPosition(pos);

		}

		if (mMoveTime >= 4.0f)
		{
			mMoveTime = 0.0f;
		}

	}
	void PoroScript::Item()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"salute", false);

		mPoroState = PoroState::DEATH;

		MachineGun* machineGun = object::Instantiate<MachineGun>(eLayerType::MachineGunItem);
		machineGun->SetName(L"machineGun");
		Transform* machineGunTr = machineGun->GetComponent<Transform>();
		machineGunTr->SetPosition(Vector3(mTr->GetPosition().x - 0.5f, mTr->GetPosition().y - 1.0f, 2.0f));
		machineGunTr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
		MachineGunScript* machineGunScript = machineGun->AddComponent<MachineGunScript>();

		Collider2D* machineGunCollider = machineGun->AddComponent<Collider2D>();
		machineGunCollider->SetType(eColliderType::Rect);
		machineGunCollider->SetSize(Vector2(0.1f, 0.1f));

		Animator* machineGunAni = machineGun->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MachineGunItem", L"Bullet\\MachineGunItem.png");
		machineGunAni->Create(L"MachineGunItem", texture, Vector2(0.0f, 0.0f), Vector2(24.0f, 22.0f), Vector2::Zero, 2, 0.3f);

		SpriteRenderer* machineGunSr = machineGun->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> machineGunMateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		machineGunSr->SetMaterial(machineGunMateiral);
		machineGunSr->SetMesh(mesh);
		machineGunAni->Play(L"MachineGunItem", true);
	}
	void PoroScript::Death()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		if (!ani->IsAnimationRunning(L"Run"))
			ani->Play(L"Run", true);

		Vector3 pos = mTr->GetPosition();
		pos.x -= 10.0f * Time::DeltaTime();
		mTr->SetPosition(pos);
	}
	void PoroScript::End()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();
		ani->Play(L"PoroMoveLeft", true);

		mPoroState = PoroState::MOVE;
	}
}