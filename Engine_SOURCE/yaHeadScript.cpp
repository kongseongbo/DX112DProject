#include "yaHeadScript.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaTransform.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaBodyScript.h"
#include "yaSceneManager.h"
#include "yaBulletScript.h"
#include "yaBombScript.h"
namespace ya
{
	//HeadScript::GunState HeadScript::mGunState = eGunState::GUN;
	HeadScript::HeadState HeadScript::mHeadState = HeadState::IDLE;

	HeadScript::HeadScript()
		: Script()
		, mBullet(nullptr)
		, mBullets{}
		, mTr(nullptr)
		, mHeadAni(nullptr)
		, direction(1)
		, mTime(0.0f)
		, mGunState(eGunState::GUN)
		//, a(nullptr)
	{

	}

	HeadScript::~HeadScript()
	{

	}

	void HeadScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();
		mHeadAni = GetOwner()->GetComponent<Animator>();
		if (mHeadAni != nullptr )
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"headIdle", L"Character\\Marco\\IdleU.png");
			mHeadAni->Create(L"HeadIdle", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 36.0f), Vector2::Zero, 4, 0.3f);

			texture = Resources::Load<Texture>(L"LheadIdle", L"Character\\Marco\\LIdleU.png");
			mHeadAni->Create(L"LHeadIdle", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 36.0f), Vector2::Zero, 4, 0.3f);

			texture = Resources::Load<Texture>(L"MoveLeftU", L"Character\\Marco\\LMoveU.png");
			mHeadAni->Create(L"MoveLeftU", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2(-0.001f, 0.0f), 12, 0.15f);


			texture = Resources::Load<Texture>(L"MoveRightU", L"Character\\Marco\\MoveU.png");
			mHeadAni->Create(L"MoveRightU", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 34.0f), Vector2::Zero, 12, 0.15f);


			texture = Resources::Load<Texture>(L"PistolAttackU", L"Character\\Marco\\PistolAttackU.png");
			mHeadAni->Create(L"PistolAttackU", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2::Zero, 10, 0.05f);
			mHeadAni->Create(L"JumpAttack", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2(0.007f,-0.2f), 10, 0.05f);

			texture = Resources::Load<Texture>(L"LPistolAttackU", L"Character\\Marco\\LPistolAttackU.png");
			mHeadAni->Create(L"LPistolAttackU", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 34.0f), Vector2::Zero, 10, 0.05f);
			mHeadAni->Create(L"LJumpAttack", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 34.0f), Vector2(-0.005f, -0.2f), 10, 0.05f);

			texture = Resources::Load<Texture>(L"LookTop", L"Character\\Marco\\LookTop.png");
			mHeadAni->Create(L"LookTop", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 33.5f), Vector2::Zero, 2, 0.1f);
			mHeadAni->Create(L"LookTop2", texture, Vector2(0.0f, 33.6f), Vector2(50.0f, 33.5f), Vector2::Zero, 4, 0.1f);

			texture = Resources::Load<Texture>(L"LLookTop", L"Character\\Marco\\LLookTop.png");
			mHeadAni->Create(L"LLookTop", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 33.5f), Vector2::Zero, 2, 0.1f);
			mHeadAni->Create(L"LLookTop2", texture, Vector2(0.0f, 33.6f), Vector2(75.0f, 33.5f), Vector2::Zero, 4, 0.1f);

			texture = Resources::Load<Texture>(L"AttackTop", L"Character\\Marco\\AttackTop.png");
			mHeadAni->Create(L"AttackTop", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 140.0f), Vector2::Zero, 10, 0.1f);

			texture = Resources::Load<Texture>(L"LAttackTop", L"Character\\Marco\\LAttackTop.png");
			mHeadAni->Create(L"LAttackTop", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 140.0f), Vector2::Zero, 10, 0.1f);

			texture = Resources::Load<Texture>(L"Down", L"Character\\Marco\\Down.png");
			mHeadAni->Create(L"DownMotion", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 45.0f), Vector2(0.01f, 0.07f), 3, 0.1f);
			mHeadAni->Create(L"DownIdle", texture, Vector2(0.0f, 45.0f), Vector2(50.0f, 45.0f), Vector2(0.01f, 0.07f), 4, 0.3f);
			mHeadAni->Create(L"DownMove", texture, Vector2(0.0f, 90.f), Vector2(50.0f, 45.0f), Vector2(0.01f, 0.07f), 7, 0.07f);

			texture = Resources::Load<Texture>(L"LeftDown", L"Character\\Marco\\LeftDown.png");
			mHeadAni->Create(L"LDownMotion", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 45.0f), Vector2(-0.01f, 0.07f), 3, 0.1f);
			mHeadAni->Create(L"LDownIdle", texture, Vector2(0.0f, 45.0f), Vector2(50.0f, 45.0f), Vector2(-0.01f, 0.07f), 4, 0.3f);
			mHeadAni->Create(L"LDownMove", texture, Vector2(0.0f, 90.f), Vector2(50.0f, 45.0f), Vector2(-0.01f, 0.07f), 7, 0.07f);

			texture = Resources::Load<Texture>(L"StiDownAttack", L"Character\\Marco\\StiDownAttack.png");
			mHeadAni->Create(L"StiDownAttack", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 31.0f), Vector2(0.02f, 0.55f), 10, 0.1f);

			texture = Resources::Load<Texture>(L"LStiDownAttack", L"Character\\Marco\\LStiDownAttack.png");
			mHeadAni->Create(L"LStiDownAttack", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 31.0f), Vector2(-0.04f, 0.55f), 10, 0.1f);

			texture = Resources::Load<Texture>(L"Jump", L"Character\\Marco\\JumpU.png");
			mHeadAni->Create(L"Jump", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 32.0f), Vector2(-0.04f, 0.05f), 6, 0.1f);
			mHeadAni->Create(L"LJump", texture, Vector2(0.0f, 32.0f), Vector2(35.0f, 32.0f), Vector2(-0.04f, 0.05f), 6, 0.1f);

			texture = Resources::Load<Texture>(L"JumpMoveU", L"Character\\Marco\\JumpMoveU.png");
			mHeadAni->Create(L"JumpMoveU", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 40.0f), Vector2(-0.04f, 0.03f), 6, 0.1f);
			mHeadAni->Create(L"LJumpMoveU", texture, Vector2(0.0f, 40.0f), Vector2(35.0f, 40.0f), Vector2(-0.05f, 0.03f), 6, 0.1f);
			
			texture = Resources::Load<Texture>(L"KnifeAttackU", L"Character\\Marco\\KnifeAttackU.png");
			mHeadAni->Create(L"KnifeAttackU", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 58.0f), Vector2(-0.02f, -0.03f), 6, 0.1f);

			texture = Resources::Load<Texture>(L"GrenadeAttackU", L"Character\\Marco\\GrenadeAttackU.png");
			mHeadAni->Create(L"GrenadeAttackU", texture, Vector2(0.0f, 0.0f), Vector2(39.5f, 38.0f), Vector2(-0.005f, 0.1f), 6, 0.1f);

			//MachineGun
			texture = Resources::Load<Texture>(L"MachineIdle", L"Character\\MarcoMachineGun\\Idle.png");
			mHeadAni->Create(L"RightIdle", texture, Vector2(0.0f, 0.0f), Vector2(47.5f, 36.0f), Vector2(0.02, 0.05f), 4, 0.3f);
			mHeadAni->Create(L"LeftIdle", texture, Vector2(0.0f, 36.0f), Vector2(47.5f, 36.0f), Vector2(-0.12, 0.05f), 4, 0.3f);

			texture = Resources::Load<Texture>(L"MachineMove", L"Character\\MarcoMachineGun\\Move.png");
			mHeadAni->Create(L"RightMove", texture, Vector2(0.0f, 0.0f), Vector2(48.33f, 36.0f), Vector2(0.005f, 0.06f), 12, 0.1f);
			mHeadAni->Create(L"LeftMove", texture, Vector2(0.0f, 36.0f), Vector2(48.33f, 36.0f), Vector2(-0.04f, 0.06f), 12, 0.1f);

			texture = Resources::Load<Texture>(L"MachineJump", L"Character\\MarcoMachineGun\\Jump.png");
			mHeadAni->Create(L"RightJump", texture, Vector2(0.0f, 0.0f), Vector2(46.66f, 32.0f), Vector2(0.005f, 0.11f), 6, 0.1f);
			mHeadAni->Create(L"LeftJump", texture, Vector2(0.0f, 32.0f), Vector2(46.66f, 32.0f), Vector2(-0.075f, 0.15f), 6, 0.1f);

			texture = Resources::Load<Texture>(L"MachineMoveJump", L"Character\\MarcoMachineGun\\MoveJump.png");
			mHeadAni->Create(L"RightMoveJump", texture, Vector2(0.0f, 0.0f), Vector2(46.66f, 32.0f), Vector2(0.014f, -0.04f), 6, 0.1f);
			mHeadAni->Create(L"LeftMoveJump", texture, Vector2(0.0f, 32.0f), Vector2(46.66f, 32.0f), Vector2(-0.075f, -0.025f), 6, 0.1f);

			texture = Resources::Load<Texture>(L"MachineLookUp", L"Character\\MarcoMachineGun\\LookUp.png");
			mHeadAni->Create(L"RightLookUp", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 40.0f), Vector2(0.014f, 0.0f), 6, 0.1f);
			mHeadAni->Create(L"LeftLookUp", texture, Vector2(0.0f, 40.0f), Vector2(50.0f, 40.0f), Vector2(-0.08f, 0.0f), 6, 0.1f);

			texture = Resources::Load<Texture>(L"MachineDown", L"Character\\MarcoMachineGun\\Down.png");
			mHeadAni->Create(L"RightDownMotion", texture, Vector2(0.0f, 0.0f), Vector2(51.428f, 41.66f), Vector2(0.014f, 0.04f), 3, 0.1f);
			mHeadAni->Create(L"RightDownIdle", texture, Vector2(0.0f, 41.66f), Vector2(51.428f, 41.66f), Vector2(0.014f, 0.04f), 4, 0.3f);
			mHeadAni->Create(L"RightDownMove", texture, Vector2(0.0f, 83.33f), Vector2(51.428f, 41.66f), Vector2(0.005f, 0.04f), 7, 0.1f);

			mHeadAni->Create(L"LeftDownMotion", texture, Vector2(0.0f, 125.00f), Vector2(51.428f, 41.66f), Vector2(-0.06f, 0.04f), 3, 0.1f);
			mHeadAni->Create(L"LeftDownIdle", texture, Vector2(0.0f, 166.66f), Vector2(51.428f, 41.66f), Vector2(-0.06f, 0.04f), 4, 0.3f);
			mHeadAni->Create(L"LeftDownMove", texture, Vector2(0.0f, 208.32), Vector2(51.428f, 41.66f), Vector2(-0.06f, 0.04f), 7, 0.1f);

			texture = Resources::Load<Texture>(L"MachineAttack", L"Character\\MarcoMachineGun\\Attack.png");
			mHeadAni->Create(L"RightAttack", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 30.0f), Vector2(0.055f, 0.07f), 4, 0.1f);
			mHeadAni->Create(L"LeftAttack", texture, Vector2(0.0f, 30.0f), Vector2(75.0f, 30.0f), Vector2(-0.12f, 0.08f), 4, 0.1f);

			mHeadAni->Create(L"RightJumpAttack", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 30.0f), Vector2(0.07f, -0.06f), 4, 0.1f);
			mHeadAni->Create(L"LeftJumpAttack", texture, Vector2(0.0f, 30.0f), Vector2(75.0f, 30.0f), Vector2(-0.13f, -0.05f), 4, 0.1f);

			texture = Resources::Load<Texture>(L"MachineUpAttack", L"Character\\MarcoMachineGun\\UpAttack.png");
			mHeadAni->Create(L"RightUpAttack", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 80.0f), Vector2(0.0f, -0.15f), 10, 0.1f);
			mHeadAni->Create(L"LeftUpAttack", texture, Vector2(0.0f, 80.0f), Vector2(40.0f, 80.0f), Vector2(-0.05f, -0.15f), 10, 0.1f);

			texture = Resources::Load<Texture>(L"MachineDownAttack", L"Character\\MarcoMachineGun\\DownAttack.png");
			mHeadAni->Create(L"RightDownAttack", texture, Vector2(0.0f, 0.0f), Vector2(77.5f, 30.0f), Vector2(0.05f, 0.27f), 4, 0.1f);
			mHeadAni->Create(L"LeftDownAttack", texture, Vector2(0.0f, 30.0f), Vector2(77.5f, 30.0f), Vector2(-0.11f, 0.27f), 4, 0.1f);

			mHeadAni->Play(L"HeadIdle", true);

			mHeadAni->GetCompleteEvent(L"PistolAttackU") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"GrenadeAttackU") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"LPistolAttackU") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"LookTop") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"LLookTop") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"AttackTop") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"LAttackTop") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"DownMotion") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"LDownMotion") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"StiDownAttack") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"LStiDownAttack") = std::bind(&HeadScript::End, this);

			//MachineGun
			mHeadAni->GetCompleteEvent(L"RightDownMotion") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"LeftDownMotion") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"RightAttack") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"LeftAttack") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"RightUpAttack") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"LeftUpAttack") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"RightDownAttack") = std::bind(&HeadScript::End, this);
			mHeadAni->GetCompleteEvent(L"LeftDownAttack") = std::bind(&HeadScript::End, this);
		}
	}

	void HeadScript::Update()
	{
		//time += 1.0f * Time::DeltaTime();

		mHeadAni = GetOwner()->GetComponent<Animator>();
		switch (mHeadState)
		{
		case ya::HeadScript::HeadState::IDLE:
			Idle();
			break;
		case ya::HeadScript::HeadState::UPIDLE:
			UpIdle();
			break;
		case ya::HeadScript::HeadState::MOVE:
			Move();
			break;
		case ya::HeadScript::HeadState::UPMOVE:
			UpMove();
			break;
		case ya::HeadScript::HeadState::JUMP:
			Jump();
			break;
		case ya::HeadScript::HeadState::HIT:
			Hit();
			break;
		case ya::HeadScript::HeadState::ATTACK:
			Attack();
			break;
		case ya::HeadScript::HeadState::UPATTACK:
			UpAttack();
			break;
		case ya::HeadScript::HeadState::SITDOWN:
			SitDown();
			break;
		case ya::HeadScript::HeadState::SITDOWNMOVE:
			SitDownMove();
			break;
		case ya::HeadScript::HeadState::SITDOWNATTACK:
			SitDownAttack();
			break;
		case ya::HeadScript::HeadState::DEATH:
			Death();
			break;
		default:
			break;
		}

		/*if(time > 5.0f)
			mBullets.deallocate(a);*/
	
	}

	void HeadScript::Render()
	{
	}

	void HeadScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetID() == 0)
		{
			Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();

			velocity.y = 30.0f;
			rigidbody->SetGround(true);
			rigidbody->SetVelocity(velocity);
			if (mHeadState == HeadState::JUMP && direction == 1)
			{
				if (mGunState == eGunState::GUN)
					mHeadAni->Play(L"HeadIdle", true);
				if (mGunState == eGunState::MACHINEGUN)
					mHeadAni->Play(L"RightIdle", true);

				mHeadState = HeadState::IDLE;
			}
			else if (mHeadState == HeadState::JUMP && direction == 0)
			{
				if (mGunState == eGunState::GUN)
					mHeadAni->Play(L"LHeadIdle", true);
				if (mGunState == eGunState::MACHINEGUN)
					mHeadAni->Play(L"LeftIdle", true);

				mHeadState = HeadState::IDLE;
			}
		}

		if (collider->GetOwner()->GetLayerType() == eLayerType::MonsterAttack)
		{
			GetOwner()->Pause();
		}

	}

	void HeadScript::OnCollisionStay(Collider2D* collider)
	{
		if (collider->GetID() == 3)
		{
			if (Input::GetKey(eKeyCode::LCTRL))
				mHeadAni->Play(L"KnifeAttackU", false);
		}
	}

	void HeadScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void HeadScript::Start()
	{
	}

	void HeadScript::Action()
	{
		
	}

	void HeadScript::End()
	{
		if (mHeadState == HeadState::ATTACK && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"HeadIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightIdle", true);

			mHeadState = HeadState::IDLE;
		}
		if (mHeadState == HeadState::ATTACK && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LHeadIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftIdle", true);

			mHeadState = HeadState::IDLE;
		}

		if ((Input::GetKey(eKeyCode::UP) || mHeadState == HeadState::UPATTACK) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LLookTop2", false);

			if (Input::GetKey(eKeyCode::LEFT))
				mHeadState = HeadState::UPMOVE;
			else
				mHeadState = HeadState::UPIDLE;
		}
		 if ((Input::GetKey(eKeyCode::UP) || mHeadState == HeadState::UPATTACK) && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LookTop2", false);

			if (Input::GetKey(eKeyCode::RIGHT))
				mHeadState = HeadState::UPMOVE;
			else
				mHeadState = HeadState::UPIDLE;
		}

		if (mHeadState == HeadState::SITDOWN && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"DownIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightDownIdle", true);
		}
		else if (mHeadState == HeadState::SITDOWN && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LDownIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftDownIdle", true);
		}

		if (mHeadState == HeadState::SITDOWNMOVE && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"DownMove", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightDownMove", true);
		}
		else if (mHeadState == HeadState::SITDOWNMOVE && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LDownMove", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftDownMove", true);
		}

		if (mHeadState == HeadState::SITDOWNATTACK && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"DownIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightDownIdle", true);

			mHeadState = HeadState::SITDOWN;
		}
		if (mHeadState == HeadState::SITDOWNATTACK && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LDownIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftDownIdle", true);

			mHeadState = HeadState::SITDOWN;
		}
	}

	void HeadScript::Idle()
	{
		
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"MoveRightU", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightMove", true);

			direction = 1;
			mHeadState = HeadState::MOVE;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"MoveLeftU", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftMove", true);

			direction = 0;
			mHeadState = HeadState::MOVE;
		}

		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition().x, mTr->GetPosition().y - 0.5f, mTr->GetPosition().z), 0);
				mHeadAni->Play(L"LPistolAttackU", false);
			}
				
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition().x - 1.f, mTr->GetPosition().y - 0.5f, mTr->GetPosition().z), 0);
				mHeadAni->Play(L"LeftAttack", false);
			}
			/*a = mBullets.allocate();
			Scene* playScene = SceneManager::GetActiveScene();
			playScene->AddGameObject(a, eLayerType::Bullet);	
			a->AddComponent<BulletScript>();
			Transform* bulletTr = a->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x, mTr->GetPosition().y - 0.5f, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));*/
		
			mHeadState = HeadState::ATTACK;
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{
			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition().x, mTr->GetPosition().y - 0.5f, mTr->GetPosition().z), 1);
				mHeadAni->Play(L"PistolAttackU", false);
			}
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition().x + 1.f, mTr->GetPosition().y - 0.5f, mTr->GetPosition().z), 1);
				mHeadAni->Play(L"RightAttack", false);
			}

			mHeadState = HeadState::ATTACK;
		}

		if (Input::GetKey(eKeyCode::S) && direction == 1)
		{
			mBomb = new Bomb();
			mBomb->SetName(L"Bomb");
			BombScript* bombScript = mBomb->AddComponent<BombScript>();
			Transform* bombTr = mBomb->GetComponent<Transform>();
			bombTr->SetPosition(Vector3(mTr->GetPosition().x, mTr->GetPosition().y, mTr->GetPosition().z - 1));
			bombTr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
			Rigidbody* bombRigidbody = mBomb->GetComponent<Rigidbody>();
			Vector2 velocity = bombRigidbody->GetVelocity();
			velocity.y = 40.0f;
			bombRigidbody->SetGround(false);
			bombRigidbody->SetVelocity(velocity);

			mHeadAni->Play(L"GrenadeAttackU", false);
			mHeadState = HeadState::ATTACK;
		}

		if (Input::GetKeyDown(eKeyCode::UP) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LLookTop", false);
			if (mGunState == eGunState::MACHINEGUN)
			{
				mHeadAni->Play(L"LeftLookUp", false);
				mHeadState = HeadState::UPIDLE;
			}
		}
		else if (Input::GetKeyDown(eKeyCode::UP) && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LookTop", false);
			if (mGunState == eGunState::MACHINEGUN)
			{
				mHeadAni->Play(L"RightLookUp", false);
				mHeadState = HeadState::UPIDLE;
			}
		}		

		if (Input::GetKey(eKeyCode::DOWN) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LDownMotion", false);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftDownMotion", false);

			mHeadState = HeadState::SITDOWN;
		}
		if (Input::GetKey(eKeyCode::DOWN) && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"DownMotion", false);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightDownMotion", false);

			mHeadState = HeadState::SITDOWN;
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			mTr = GetOwner()->GetComponent<Transform>();
			Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();
			velocity.y = 40.0f;
			rigidbody->SetGround(false);
			rigidbody->SetVelocity(velocity);

			if (direction == 1)
			{
				if (mGunState == eGunState::GUN)
					mHeadAni->Play(L"Jump", false);
				if (mGunState == eGunState::MACHINEGUN)
					mHeadAni->Play(L"RightJump", false);

	
				mHeadState = HeadState::JUMP;
			}
			else if (direction == 0)
			{
				if (mGunState == eGunState::GUN)
					mHeadAni->Play(L"LJump", false);
				if (mGunState == eGunState::MACHINEGUN)
					mHeadAni->Play(L"LeftJump", false);
			
				mHeadState = HeadState::JUMP;
			}
		}
		
	}

	void HeadScript::UpIdle()
	{

		if (Input::GetKey(eKeyCode::RIGHT) )
		{
			direction = 1;
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LookTop2", false);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightLookUp", false);

			mHeadState = HeadState::UPMOVE;
		}
		if (Input::GetKey(eKeyCode::LEFT) )
		{
			direction = 0;
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LLookTop2", false);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftLookUp", false);

			mHeadState = HeadState::UPMOVE;
		}
		
		if (Input::GetKeyUp(eKeyCode::UP) && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"HeadIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightIdle", true);

			mHeadState = HeadState::IDLE;
		}
		if (Input::GetKeyUp(eKeyCode::UP) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LHeadIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftIdle", true);

			mHeadState = HeadState::IDLE;
		}

		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{
			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z), 1, true);
				mHeadAni->Play(L"AttackTop", false);
			}
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition()), 1, true);
				mHeadAni->Play(L"RightUpAttack", false);
			}

			mHeadState = HeadState::UPATTACK;
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z), 0, true);
				mHeadAni->Play(L"LAttackTop", false);
			}
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition()), 0,true);
				mHeadAni->Play(L"LeftUpAttack", false);
			}

			mHeadState = HeadState::UPATTACK;
		}
	}

	void HeadScript::Move()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"HeadIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightIdle", true);

			mHeadState = HeadState::IDLE;
		}
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LHeadIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftIdle", true);

			mHeadState = HeadState::IDLE;
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{
			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition()), 1);
				mHeadAni->Play(L"PistolAttackU", true);
			}
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition().x, mTr->GetPosition().y - 0.7f, mTr->GetPosition().z), 1);
				mHeadAni->Play(L"RightAttack", true);
			}

			mHeadState = HeadState::ATTACK;
		}
		else if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition().x, mTr->GetPosition().y - 0.5f, mTr->GetPosition().z), 0);
				mHeadAni->Play(L"LPistolAttackU", true);
			}
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition().x, mTr->GetPosition().y - 0.7f, mTr->GetPosition().z), 0);
				mHeadAni->Play(L"LeftAttack", true);
			}

			mHeadState = HeadState::ATTACK;
		}

		if (Input::GetKey(eKeyCode::UP) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LLookTop", false);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftLookUp", false);

			mHeadState = HeadState::UPMOVE;
		}
		else if (Input::GetKey(eKeyCode::UP) && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LookTop", false);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightLookUp", false);

			mHeadState = HeadState::UPMOVE;
		}
	
		if (direction == 0)
		{
			Vector3 pos = mTr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
		else if (direction == 1)
		{
			Vector3 pos = mTr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();
			velocity.y = 40.0f;
			rigidbody->SetGround(false);
			rigidbody->SetVelocity(velocity);

			if (direction == 0)
			{
				if (mGunState == eGunState::GUN)
					mHeadAni->Play(L"LJumpMoveU", false);
				if (mGunState == eGunState::MACHINEGUN)
					mHeadAni->Play(L"LeftMoveJump", false);
			}
			else
			{
				if (mGunState == eGunState::GUN)
					mHeadAni->Play(L"JumpMoveU", false);
				if (mGunState == eGunState::MACHINEGUN)
					mHeadAni->Play(L"RightMoveJump", false);
			}
			
			mHeadState = HeadState::JUMP;
		}

		if (Input::GetKey(eKeyCode::DOWN) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LDownMotion", false);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftDownMotion", false);

			mHeadState = HeadState::SITDOWNMOVE;
		}
		else if (Input::GetKey(eKeyCode::DOWN) && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"DownMotion", false);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightDownMotion", false);

			mHeadState = HeadState::SITDOWNMOVE;
		}
	}

	void HeadScript::UpMove()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT) && direction == 1)
			mHeadState = HeadState::UPIDLE;
		else if (Input::GetKeyUp(eKeyCode::LEFT) && direction == 0)
			mHeadState = HeadState::UPIDLE;
		
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z), 0, true);
				mHeadAni->Play(L"LAttackTop", false);
			}
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y + 1.f, mTr->GetPosition().z), 0,true);
				mHeadAni->Play(L"LeftUpAttack", false);
			}

			mHeadState = HeadState::UPATTACK;
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{

			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z), 1, true);
				mHeadAni->Play(L"AttackTop", false);
			}
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition().x + .5f, mTr->GetPosition().y + 1.f, mTr->GetPosition().z), 1, true);
				mHeadAni->Play(L"RightUpAttack", false);
			}
			
			mHeadState = HeadState::UPATTACK;
		}
		if (Input::GetKeyUp(eKeyCode::UP) && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"HeadIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightIdle", true);

			mHeadState = HeadState::IDLE;
		}
		else if (Input::GetKeyUp(eKeyCode::UP) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LHeadIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftIdle", true);

			mHeadState = HeadState::IDLE;
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();

			velocity.y = 30.0f;
			rigidbody->SetGround(false);
			rigidbody->SetVelocity(velocity);
		}

		if (Input::GetKey(eKeyCode::LEFT) && direction == 0)
		{
			Vector3 pos = mTr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::RIGHT) && direction == 1)
		{
			Vector3 pos = mTr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
	}

	void HeadScript::Jump()
	{
		if (Input::GetKey(eKeyCode::LEFT) )
		{
			Vector3 pos = mTr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			Vector3 pos = mTr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}

		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{

			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z), 0);
				mHeadAni->Play(L"LJumpAttack", false);
			}
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y - 0.7f, mTr->GetPosition().z), 0);
				mHeadAni->Play(L"LeftJumpAttack", false);
			}

			//mHeadState = HeadState::ATTACK;
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{

			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z), 1);
				mHeadAni->Play(L"JumpAttack", false);
			}
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition().x + .5f, mTr->GetPosition().y - 0.7f, mTr->GetPosition().z), 1);
				mHeadAni->Play(L"RightJumpAttack", false);
			}

			//mHeadState = HeadState::ATTACK;
		}
	}

	void HeadScript::Attack()
	{
		if (Input::GetKey(eKeyCode::LEFT) && direction == 0)
		{
			Vector3 pos = mTr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT) && direction == 1)
		{
			Vector3 pos = mTr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}

		if (Input::GetKeyDown(eKeyCode::UP))
		{
			if (mGunState == eGunState::MACHINEGUN)
			{
				if (direction == 0)
				{
					NewMachineGunUp(Vector3(mTr->GetPosition().x + .5f, mTr->GetPosition().y - 0.7f, mTr->GetPosition().z), direction);
					mHeadAni->Play(L"LeftLookUp", false);
				}
				if (direction == 1)
				{
					NewMachineGunUp(Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y - 0.7f, mTr->GetPosition().z), direction);
					mHeadAni->Play(L"RightLookUp", false);
				}
				mHeadState = HeadState::UPIDLE;
			}
		}
	}

	void HeadScript::UpAttack()
	{
		if (Input::GetKey(eKeyCode::LEFT) && direction == 0)
		{
			Vector3 pos = mTr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT) && direction == 1)
		{
			Vector3 pos = mTr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}

		if (Input::GetKeyUp(eKeyCode::UP) && direction == 1)
		{
			mHeadAni->Play(L"HeadIdle", true);
			mHeadState = HeadState::IDLE;
		}
		else if (Input::GetKeyUp(eKeyCode::UP) && direction == 0)
		{
			mHeadAni->Play(L"LHeadIdle", true);
			mHeadState = HeadState::IDLE;
		}
	}

	void HeadScript::SitDown()
	{
		if (Input::GetKeyUp(eKeyCode::DOWN) && direction == 1)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"HeadIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightIdle", true);

			mHeadState = HeadState::IDLE;
		}
		else if (Input::GetKeyUp(eKeyCode::DOWN) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LHeadIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftIdle", true);

			mHeadState = HeadState::IDLE;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			direction = 1;
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"DownMove", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightDownMove", true);

			mHeadState = HeadState::SITDOWNMOVE;
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			direction = 0;
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LDownMove", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftDownMove", true);
			
			mHeadState = HeadState::SITDOWNMOVE;
		}

		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{	

			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition().x + 0.1f, mTr->GetPosition().y - 1.f, mTr->GetPosition().z), 1);
				mHeadAni->Play(L"StiDownAttack", false);
			}
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition().x + 1.0f, mTr->GetPosition().y - 1.0f, mTr->GetPosition().z), 1);
				mHeadAni->Play(L"RightDownAttack", false);
			}

			mHeadState = HeadState::SITDOWNATTACK;
		}
		else if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{
			if (mGunState == eGunState::GUN)
			{
				NewBullet(L"bullet", Vector3(mTr->GetPosition().x - 0.1f, mTr->GetPosition().y - 1.f, mTr->GetPosition().z), 0);
				mHeadAni->Play(L"LStiDownAttack", false);
			}
			if (mGunState == eGunState::MACHINEGUN)
			{
				NewMachineGun(Vector3(mTr->GetPosition().x - 1.0f, mTr->GetPosition().y - 1.0f, mTr->GetPosition().z), 0);
				mHeadAni->Play(L"LeftDownAttack", false);
			}

			mHeadState = HeadState::SITDOWNATTACK;
		}

	}

	void HeadScript::SitDownMove()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT) )
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"DownIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"RightDownIdle", true);

			mHeadState = HeadState::SITDOWN;
		}
		else if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			if (mGunState == eGunState::GUN)
				mHeadAni->Play(L"LDownIdle", true);
			if (mGunState == eGunState::MACHINEGUN)
				mHeadAni->Play(L"LeftDownIdle", true);

			mHeadState = HeadState::SITDOWN;
		}

		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			if (direction == 0)
			{
				if (mGunState == eGunState::GUN)
					mHeadAni->Play(L"MoveLeftU", true);
				if (mGunState == eGunState::MACHINEGUN)
					mHeadAni->Play(L"LeftMove", true);
				
			}
			else if (direction == 1)
			{
				if (mGunState == eGunState::GUN)
					mHeadAni->Play(L"MoveRightU", true);
				if (mGunState == eGunState::MACHINEGUN)
					mHeadAni->Play(L"RightMove", true);
			}
				
			mHeadState = HeadState::MOVE;
		}

		if (Input::GetKey(eKeyCode::LEFT))
		{
			direction = 0;
			Vector3 pos = mTr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			direction = 1;
			Vector3 pos = mTr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
	}

	void HeadScript::SitDownAttack()
	{
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			if (direction == 0)
			{
				if (mGunState == eGunState::GUN)
					mHeadAni->Play(L"LHeadIdle", true);
				if (mGunState == eGunState::MACHINEGUN)
					mHeadAni->Play(L"LeftIdle", true);
			}
			else if (direction == 1)
			{
				if (mGunState == eGunState::GUN)
					mHeadAni->Play(L"HeadIdle", true);
				if (mGunState == eGunState::MACHINEGUN)
					mHeadAni->Play(L"RightIdle", true);
			}
				

			mHeadState = HeadState::IDLE;
		}
	}

	void HeadScript::Hit()
	{
	}

	void HeadScript::Death()
	{
	}
	void HeadScript::NewBullet(std::wstring name, Vector3 pos , int direction, bool up)
	{
		mBullet = new Bullet();
		mBullet->SetName(name);
		BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
		Transform* bulletTr = mBullet->GetComponent<Transform>();

		if (up == true)
		{
			
			bulletTr->SetRotation(Vector3(0.0f, 0.0f, 90.0f));
		}
		else
		{
			if (direction == 0)
			{
				bulletTr->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
			}
		}
		

		bulletTr->SetPosition(pos);
		bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		bulletScript->SetDirection(direction);
		bulletScript->SetState(up);
	}
	void HeadScript::NewMachineGun(Vector3 pos, int direction, bool up)
	{


		for (size_t i = 0; i < 5; i++)
		{
			mBullets[i] = new Bullet();
			if (i == 0)
				mBullets[i]->SetName(L"bullet0");
			if (i == 1)
				mBullets[i]->SetName(L"bullet1");
			if (i == 2)
				mBullets[i]->SetName(L"bullet2");
			if (i == 3)
				mBullets[i]->SetName(L"bullet3");
			if (i == 4)
				mBullets[i]->SetName(L"bullet4");

			// 0~0.5 사이의 난수 생성
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_real_distribution<> distr(0, 0.3);


			BulletScript* bulletScript = mBullets[i]->AddComponent<BulletScript>();
			Transform* bulletTr = mBullets[i]->GetComponent<Transform>();
			bulletTr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
			if (up == true)
			{
				bulletTr->SetPosition(Vector3((pos.x - 1.0f) + distr(eng), pos.y , pos.z ));
				bulletTr->SetRotation(Vector3(0.0f, 0.0f, 90.0f));
			}
			else
			{
				if (direction == 0)
				{
					
					/*bulletTr->SetPosition(Vector3(pos.x - 2.0f, pos.y + distr(eng), pos.z));
					bulletTr->SetRotation(Vector3(0.0f, 180.0f, -10.0f * (i + 4)));*/
		
					bulletTr->SetPosition(Vector3(pos.x - 2.0f, pos.y + distr(eng), pos.z));
					bulletTr->SetRotation(Vector3(0.0f, 180.0f, 0.0f  ));

				}
				else
				{
					bulletTr->SetPosition(Vector3(pos.x + 1.0f, pos.y + distr(eng), pos.z));
				}
			}
		
			bulletScript->SetDirection(direction);
			bulletScript->SetState(up);
		}
	}
	void HeadScript::NewMachineGunUp(Vector3 pos, int direction)
	{
		int num_angles = 5; // 출력할 각의 개수
		int interval = 90 / num_angles; // 일정한 간격 계산

		for (size_t i = 0; i < 5; i++)
		{
			mBullets[i] = new Bullet();
			if (i == 0)
				mBullets[i]->SetName(L"bullet0");
			if (i == 1)
				mBullets[i]->SetName(L"bullet1");
			if (i == 2)
				mBullets[i]->SetName(L"bullet2");
			if (i == 3)
				mBullets[i]->SetName(L"bullet3");
			if (i == 4)
				mBullets[i]->SetName(L"bullet4");

			// 0~0.5 사이의 난수 생성
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_real_distribution<> distr(0, 0.3);

			int angle = i * interval;

			BulletScript* bulletScript = mBullets[i]->AddComponent<BulletScript>();
			Transform* bulletTr = mBullets[i]->GetComponent<Transform>();
			bulletTr->SetScale(Vector3(10.0f, 10.0f, 1.0f));

			if (direction == 0)
			{

				bulletTr->SetPosition(Vector3(pos.x - 2.0f, pos.y + distr(eng), pos.z));
				bulletTr->SetRotation(Vector3(0.0f, 180.0f, -1 *angle));
			}
			else
			{
				bulletTr->SetPosition(Vector3(pos.x + 1.0f, pos.y + distr(eng), pos.z));
				bulletTr->SetRotation(Vector3(0.0f, 0.0f, 1.0f * angle));
			}
			
			bulletScript->SetDirection(direction);
		}
	}

}
