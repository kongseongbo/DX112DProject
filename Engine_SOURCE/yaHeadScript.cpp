#include "yaHeadScript.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaTransform.h"
#include "yaResources.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaBodyScript.h"


namespace ya
{
	HeadScript::HeadState HeadScript::mHeadState = HeadState::IDLE;


	HeadScript::HeadScript()
		: Script()
		, mTr(nullptr)
		, headAni(nullptr)
		, bodyAni(nullptr)
		, direction(1)
	{

	}

	HeadScript::~HeadScript()
	{

	}

	void HeadScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

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

			headAni->Play(L"HeadIdle", true);

			headAni->GetCompleteEvent(L"PistolAttackU") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"LPistolAttackU") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"LookTop") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"LLookTop") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"AttackTop") = std::bind(&HeadScript::End, this);
			headAni->GetCompleteEvent(L"DownMotion") = std::bind(&HeadScript::End, this);
		}

		/*if (animator->GetName() == L"HeadIdle")
		{
			animator->GetCompleteEvent(L"HeadIdle") = std::bind(&PlayerScript::Action, this);
			animator->GetEndEvent(L"HeadIdle") = std::bind(&PlayerScript::End, this);
			animator->GetEvent(L"HeadIdle", 1) = std::bind(&PlayerScript::End, this);
		}

		if (animator->GetName() == L"BodyIdle")
		{
			animator->GetCompleteEvent(L"BodyIdle") = std::bind(&PlayerScript::Action, this);
			animator->GetEndEvent(L"BodyIdle") = std::bind(&PlayerScript::End, this);
			animator->GetEvent(L"BodyIdle", 1) = std::bind(&PlayerScript::End, this);
		}*/
	}

	void HeadScript::Update()
	{
		
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
		case ya::HeadScript::HeadState::JUMP:
			Jump();
			break;
		case ya::HeadScript::HeadState::HIT:
			Hit();
			break;
		case ya::HeadScript::HeadState::ATTACK:
			Attack();
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


		headState = mHeadState;

	}

	void HeadScript::Render()
	{
	}

	void HeadScript::OnCollisionEnter(Collider2D* collider)
	{
		Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
		Vector2 velocity = rigidbody->GetVelocity();

		//velocity.y = 30.0f;
		rigidbody->SetGround(true);
		//rigidbody->SetVelocity(velocity);
	}

	void HeadScript::OnCollisionStay(Collider2D* collider)
	{
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

		if (Input::GetKey(eKeyCode::UP) && direction == 0)
		{
			headAni->Play(L"LLookTop2", false);
			mHeadState = HeadState::UPIDLE;
		}
		else if (Input::GetKey(eKeyCode::UP) && direction == 1)
		{
			headAni->Play(L"LookTop2", false);
			mHeadState = HeadState::UPIDLE;
		}

		//if (mHeadState == HeadState::ATTACK && direction == 1)
		//{
		//	headAni->Play(L"HeadIdle", true);
		//	mHeadState = HeadState::IDLE;
		//}

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
			headAni->Play(L"LPistolAttackU", false);
			mHeadState = HeadState::ATTACK;
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{
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
	}

	void HeadScript::UpIdle()
	{
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

		if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 1)
		{
			headAni->Play(L"AttackTop", false);
			mHeadState = HeadState::ATTACK;
		}
		else if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{
			headAni->Play(L"LAttackTop", false);
			mHeadState = HeadState::ATTACK;
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
			headAni->Play(L"PistolAttackU", true);
			mHeadState = HeadState::ATTACK;
		}
		else if (Input::GetKeyDown(eKeyCode::LCTRL) && direction == 0)
		{
			headAni->Play(L"LPistolAttackU", true);
			mHeadState = HeadState::ATTACK;
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
		

	}

	void HeadScript::Jump()
	{



	}

	void HeadScript::SitDown()
	{


	}

	void HeadScript::SitDownMove()
	{

	}

	void HeadScript::SitDownAttack()
	{

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

	void HeadScript::Hit()
	{
	}

	void HeadScript::Death()
	{
	}
}
