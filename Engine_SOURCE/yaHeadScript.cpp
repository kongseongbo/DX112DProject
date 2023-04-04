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


namespace ya
{
	HeadScript::HeadState HeadScript::mHeadState = HeadState::IDLE;


	HeadScript::HeadScript()
		: Script()
		, mTr(nullptr)
		, headAni(nullptr)
		, bodyAni(nullptr)
		, direction(1)
		, time(0.0f)
		//, a(nullptr)
	{

	}

	HeadScript::~HeadScript()
	{

	}

	void HeadScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();
		headAni = GetOwner()->GetComponent<Animator>();
		if (headAni != nullptr )
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"headIdle", L"Character\\Marco\\IdleU.png");
			headAni->Create(L"HeadIdle", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 36.0f), Vector2::Zero, 4, 0.3f);

			texture = Resources::Load<Texture>(L"LheadIdle", L"Character\\Marco\\LIdleU.png");
			headAni->Create(L"LHeadIdle", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 36.0f), Vector2::Zero, 4, 0.3f);

			texture = Resources::Load<Texture>(L"MoveLeftU", L"Character\\Marco\\LMoveU.png");
			headAni->Create(L"MoveLeftU", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2(-0.001f, 0.0f), 12, 0.15f);


			texture = Resources::Load<Texture>(L"MoveRightU", L"Character\\Marco\\MoveU.png");
			headAni->Create(L"MoveRightU", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 34.0f), Vector2::Zero, 12, 0.15f);


			texture = Resources::Load<Texture>(L"PistolAttackU", L"Character\\Marco\\PistolAttackU.png");
			headAni->Create(L"PistolAttackU", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2::Zero, 10, 0.05f);

			texture = Resources::Load<Texture>(L"LPistolAttackU", L"Character\\Marco\\LPistolAttackU.png");
			headAni->Create(L"LPistolAttackU", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 34.0f), Vector2::Zero, 10, 0.05f);

			texture = Resources::Load<Texture>(L"LookTop", L"Character\\Marco\\LookTop.png");
			headAni->Create(L"LookTop", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 33.5f), Vector2::Zero, 2, 0.1f);
			headAni->Create(L"LookTop2", texture, Vector2(0.0f, 33.6f), Vector2(50.0f, 33.5f), Vector2::Zero, 4, 0.1f);

			texture = Resources::Load<Texture>(L"LLookTop", L"Character\\Marco\\LLookTop.png");
			headAni->Create(L"LLookTop", texture, Vector2(0.0f, 0.0f), Vector2(75.0f, 33.5f), Vector2::Zero, 2, 0.1f);
			headAni->Create(L"LLookTop2", texture, Vector2(0.0f, 33.6f), Vector2(75.0f, 33.5f), Vector2::Zero, 4, 0.1f);

			texture = Resources::Load<Texture>(L"AttackTop", L"Character\\Marco\\AttackTop.png");
			headAni->Create(L"AttackTop", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 140.0f), Vector2::Zero, 10, 0.1f);

			texture = Resources::Load<Texture>(L"LAttackTop", L"Character\\Marco\\LAttackTop.png");
			headAni->Create(L"LAttackTop", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 140.0f), Vector2::Zero, 10, 0.1f);

			texture = Resources::Load<Texture>(L"Down", L"Character\\Marco\\Down.png");
			headAni->Create(L"DownMotion", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 45.0f), Vector2(0.01f, 0.07f), 3, 0.1f);
			headAni->Create(L"DownIdle", texture, Vector2(0.0f, 45.0f), Vector2(50.0f, 45.0f), Vector2(0.01f, 0.07f), 4, 0.3f);
			headAni->Create(L"DownMove", texture, Vector2(0.0f, 90.f), Vector2(50.0f, 45.0f), Vector2(0.01f, 0.07f), 7, 0.07f);

			texture = Resources::Load<Texture>(L"LeftDown", L"Character\\Marco\\LeftDown.png");
			headAni->Create(L"LDownMotion", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 45.0f), Vector2(-0.01f, 0.07f), 3, 0.1f);
			headAni->Create(L"LDownIdle", texture, Vector2(0.0f, 45.0f), Vector2(50.0f, 45.0f), Vector2(-0.01f, 0.07f), 4, 0.3f);
			headAni->Create(L"LDownMove", texture, Vector2(0.0f, 90.f), Vector2(50.0f, 45.0f), Vector2(-0.01f, 0.07f), 7, 0.07f);

			texture = Resources::Load<Texture>(L"StiDownAttack", L"Character\\Marco\\StiDownAttack.png");
			headAni->Create(L"StiDownAttack", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 31.0f), Vector2(0.02f, 0.55f), 10, 0.1f);

			texture = Resources::Load<Texture>(L"LStiDownAttack", L"Character\\Marco\\LStiDownAttack.png");
			headAni->Create(L"LStiDownAttack", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 31.0f), Vector2(-0.04f, 0.55f), 10, 0.1f);

			texture = Resources::Load<Texture>(L"Jump", L"Character\\Marco\\JumpU.png");
			headAni->Create(L"Jump", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 32.0f), Vector2(-0.04f, 0.05f), 6, 0.1f);
			headAni->Create(L"LJump", texture, Vector2(0.0f, 32.0f), Vector2(35.0f, 32.0f), Vector2(-0.04f, 0.05f), 6, 0.1f);

			texture = Resources::Load<Texture>(L"JumpMoveU", L"Character\\Marco\\JumpMoveU.png");
			headAni->Create(L"JumpMoveU", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 40.0f), Vector2(-0.04f, 0.03f), 6, 0.1f);
			headAni->Create(L"LJumpMoveU", texture, Vector2(0.0f, 40.0f), Vector2(35.0f, 40.0f), Vector2(-0.05f, 0.03f), 6, 0.1f);
			
			texture = Resources::Load<Texture>(L"KnifeAttackU", L"Character\\Marco\\KnifeAttackU.png");
			headAni->Create(L"KnifeAttackU", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 58.0f), Vector2(-0.02f, -0.03f), 6, 0.1f);

			headAni->Play(L"HeadIdle", true);

			headAni->GetCompleteEvent(L"PistolAttackU") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"LPistolAttackU") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"LookTop") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"LLookTop") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"AttackTop") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"LAttackTop") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"DownMotion") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"LDownMotion") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"StiDownAttack") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"LStiDownAttack") = std::bind(&HeadScript::End, this);
		}
	}

	void HeadScript::Update()
	{
		time += 1.0f * Time::DeltaTime();

		headAni = GetOwner()->GetComponent<Animator>();
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
				headAni->Play(L"HeadIdle", true);
				mHeadState = HeadState::IDLE;
			}
			else if (mHeadState == HeadState::JUMP && direction == 0)
			{
				headAni->Play(L"LHeadIdle", true);
				mHeadState = HeadState::IDLE;
			}
		}

		
	}

	void HeadScript::OnCollisionStay(Collider2D* collider)
	{
		if (collider->GetID() == 3)
		{
			if (Input::GetKey(eKeyCode::LCTRL))
				headAni->Play(L"KnifeAttackU", false);
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
			headAni->Play(L"HeadIdle", true);
			mHeadState = HeadState::IDLE;
		}
		if (mHeadState == HeadState::ATTACK && direction == 0)
		{
			headAni->Play(L"LHeadIdle", true);
			mHeadState = HeadState::IDLE;
		}

		if ((Input::GetKey(eKeyCode::UP) || mHeadState == HeadState::UPATTACK) && direction == 0)
		{
			headAni->Play(L"LLookTop2", false);
			if (Input::GetKey(eKeyCode::LEFT))
				mHeadState = HeadState::UPMOVE;
			else
				mHeadState = HeadState::UPIDLE;
		}
		 if ((Input::GetKey(eKeyCode::UP) || mHeadState == HeadState::UPATTACK) && direction == 1)
		{
			headAni->Play(L"LookTop2", false);
			if (Input::GetKey(eKeyCode::RIGHT))
				mHeadState = HeadState::UPMOVE;
			else
				mHeadState = HeadState::UPIDLE;
		}

		if (mHeadState == HeadState::SITDOWN && direction == 1)
		{
			headAni->Play(L"DownIdle", true);
		}
		else if (mHeadState == HeadState::SITDOWN && direction == 0)
		{
			headAni->Play(L"LDownIdle", true);
		}

		if (mHeadState == HeadState::SITDOWNMOVE && direction == 1)
		{
			headAni->Play(L"DownMove", true);
		}
		else if (mHeadState == HeadState::SITDOWNMOVE && direction == 0)
		{
			headAni->Play(L"LDownMove", true);
		}

		if (mHeadState == HeadState::SITDOWNATTACK && direction == 1)
		{
			headAni->Play(L"DownIdle", true);
			mHeadState = HeadState::SITDOWN;
		}
		if (mHeadState == HeadState::SITDOWNATTACK && direction == 0)
		{
			headAni->Play(L"LDownIdle", true);
			mHeadState = HeadState::SITDOWN;
		}
	}

	void HeadScript::Idle()
	{
		
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			headAni->Play(L"MoveRightU", true);
			direction = 1;
			mHeadState = HeadState::MOVE;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			headAni->Play(L"MoveLeftU", true);
			direction = 0;
			mHeadState = HeadState::MOVE;
		}

		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{
			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x, mTr->GetPosition().y - 0.5f, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(0);
			
			/*a = mBullets.allocate();
			Scene* playScene = SceneManager::GetActiveScene();
			playScene->AddGameObject(a, eLayerType::Bullet);	
			a->AddComponent<BulletScript>();
			Transform* bulletTr = a->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x, mTr->GetPosition().y - 0.5f, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));*/
		
			
			headAni->Play(L"LPistolAttackU", false);
			mHeadState = HeadState::ATTACK;
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{
			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x, mTr->GetPosition().y - 0.5f, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(1);

			headAni->Play(L"PistolAttackU", false);
			mHeadState = HeadState::ATTACK;
		}

		if (Input::GetKeyDown(eKeyCode::UP) && direction == 0)
		{
			headAni->Play(L"LLookTop", false);
		}
		else if (Input::GetKeyDown(eKeyCode::UP) && direction == 1)
		{
			headAni->Play(L"LookTop", false);
		}		

		if (Input::GetKey(eKeyCode::DOWN) && direction == 0)
		{
			headAni->Play(L"LDownMotion", false);
			mHeadState = HeadState::SITDOWN;
		}
		if (Input::GetKey(eKeyCode::DOWN) && direction == 1)
		{
			headAni->Play(L"DownMotion", false);
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
				headAni->Play(L"Jump", false);
				mHeadState = HeadState::JUMP;
			}
			else if (direction == 0)
			{
				headAni->Play(L"LJump", false);
				mHeadState = HeadState::JUMP;
			}
		}
		
	}

	void HeadScript::UpIdle()
	{

		if (Input::GetKey(eKeyCode::RIGHT) && direction == 1)
		{
			mHeadState = HeadState::UPMOVE;
		}
		if (Input::GetKey(eKeyCode::LEFT) && direction == 0)
		{
			mHeadState = HeadState::UPMOVE;
		}
		
		
		if (Input::GetKeyUp(eKeyCode::UP) && direction == 1)
		{
			headAni->Play(L"HeadIdle", true);
			mHeadState = HeadState::IDLE;
		}
		if (Input::GetKeyUp(eKeyCode::UP) && direction == 0)
		{
			headAni->Play(L"LHeadIdle", true);
			mHeadState = HeadState::IDLE;
		}

		

		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{
			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(1);
			bulletScript->SetState(true);
			headAni->Play(L"AttackTop", false);
			mHeadState = HeadState::UPATTACK;
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{
			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(0);
			bulletScript->SetState(true);
			headAni->Play(L"LAttackTop", false);
			mHeadState = HeadState::UPATTACK;
		}
	}

	void HeadScript::Move()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			headAni->Play(L"HeadIdle", true);
			mHeadState = HeadState::IDLE;
		}
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			headAni->Play(L"LHeadIdle", true);
			mHeadState = HeadState::IDLE;
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{
			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x, mTr->GetPosition().y - 0.5f, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(1);

			headAni->Play(L"PistolAttackU", true);
			mHeadState = HeadState::ATTACK;
		}
		else if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{
			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x, mTr->GetPosition().y - 0.5f, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(0);

			headAni->Play(L"LPistolAttackU", true);
			mHeadState = HeadState::ATTACK;
		}

		if (Input::GetKey(eKeyCode::UP) && direction == 0)
		{
			headAni->Play(L"LLookTop", false);
			mHeadState = HeadState::UPMOVE;
		}
		else if (Input::GetKey(eKeyCode::UP) && direction == 1)
		{
			headAni->Play(L"LookTop", false);
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

			if(direction == 0)
				headAni->Play(L"LJumpMoveU", false);
			else
				headAni->Play(L"JumpMoveU", false);
			
			mHeadState = HeadState::JUMP;
		}

		if (Input::GetKey(eKeyCode::DOWN) && direction == 0)
		{
			headAni->Play(L"LDownMotion", false);
			mHeadState = HeadState::SITDOWNMOVE;
		}
		else if (Input::GetKey(eKeyCode::DOWN) && direction == 1)
		{
			headAni->Play(L"DownMotion", false);
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
			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(0);
			bulletScript->SetState(true);
			headAni->Play(L"LAttackTop", false);
			mHeadState = HeadState::UPATTACK;
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{
			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(1);
			bulletScript->SetState(true);
			headAni->Play(L"AttackTop", false);
			mHeadState = HeadState::UPATTACK;
		}
		if (Input::GetKeyUp(eKeyCode::UP) && direction == 1)
		{
			headAni->Play(L"HeadIdle", true);
			mHeadState = HeadState::IDLE;
		}
		else if (Input::GetKeyUp(eKeyCode::UP) && direction == 0)
		{
			headAni->Play(L"LHeadIdle", true);
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

		if (direction == 0)
		{
			Vector3 pos = mTr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
		if (direction == 1)
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
			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(0);

			headAni->Play(L"LPistolAttackU", false);
			mHeadState = HeadState::ATTACK;
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{

			mTr->SetPosition(Vector3(mTr->GetPosition().x, mTr->GetPosition().y , mTr->GetPosition().z));

			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x - .5f, mTr->GetPosition().y, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(1);

			
			headAni->Play(L"PistolAttackU", false);
			mHeadState = HeadState::ATTACK;
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
			headAni->Play(L"HeadIdle", true);
			mHeadState = HeadState::IDLE;
		}
		else if (Input::GetKeyUp(eKeyCode::UP) && direction == 0)
		{
			headAni->Play(L"LHeadIdle", true);
			mHeadState = HeadState::IDLE;
		}
	}

	void HeadScript::SitDown()
	{
		if (Input::GetKeyUp(eKeyCode::DOWN) && direction == 1)
		{
			headAni->Play(L"HeadIdle", true);
			mHeadState = HeadState::IDLE;
		}
		else if (Input::GetKeyUp(eKeyCode::DOWN) && direction == 0)
		{
			headAni->Play(L"LHeadIdle", true);
			mHeadState = HeadState::IDLE;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			direction = 1;
			headAni->Play(L"DownMove", true);
			mHeadState = HeadState::SITDOWNMOVE;
		}
		else if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			direction = 0;
			headAni->Play(L"LDownMove", true);
			mHeadState = HeadState::SITDOWNMOVE;
		}

		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{	
			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x + 0.1f, mTr->GetPosition().y - 1.f, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(1);

			headAni->Play(L"StiDownAttack", false);
			mHeadState = HeadState::SITDOWNATTACK;
		}
		else if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{
			mBullet = new Bullet();
			BulletScript* bulletScript = mBullet->AddComponent<BulletScript>();
			Transform* bulletTr = mBullet->GetComponent<Transform>();
			bulletTr->SetPosition(Vector3(mTr->GetPosition().x - 0.1f, mTr->GetPosition().y - 1.f, mTr->GetPosition().z));
			bulletTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			bulletScript->SetDirection(0);

			headAni->Play(L"LStiDownAttack", false);
			mHeadState = HeadState::SITDOWNATTACK;
		}

	}

	void HeadScript::SitDownMove()
	{
		if (Input::GetKeyUp(eKeyCode::RIGHT) )
		{
			headAni->Play(L"DownIdle", true);
			mHeadState = HeadState::SITDOWN;
		}
		else if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			headAni->Play(L"LDownIdle", true);
			mHeadState = HeadState::SITDOWN;
		}

		if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			if (direction == 0)
				headAni->Play(L"MoveLeftU", true);
			else if (direction == 1)
				headAni->Play(L"MoveRightU", true);
				
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
				headAni->Play(L"LHeadIdle", true);
			else if (direction == 1)
				headAni->Play(L"HeadIdle", true);

			mHeadState = HeadState::IDLE;
		}
	}



	void HeadScript::Hit()
	{
	}

	void HeadScript::Death()
	{
	}
}
