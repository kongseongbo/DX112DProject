#include "yaPlayerScript.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaTransform.h"
#include "yaResources.h"
#include "yaPlayer.h"


namespace ya
{
	PlayerScript::HeadState PlayerScript::mHeadState = HeadState::IDLE;
	PlayerScript::BodyState PlayerScript::mBodyState = BodyState::IDLE;

	PlayerScript::PlayerScript()
		: Script()
		, mTr(nullptr)
		, headAni(nullptr)
		, bodyAni(nullptr)
		, direction(0)
	{
		
	}

	PlayerScript::~PlayerScript()
	{
	
	}

	void PlayerScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		if (headAni != nullptr && bodyAni != nullptr)
		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"bodyidle", L"Character\\Marco\\IdleD.png");
			bodyAni->Create(L"BodyIdle", texture, Vector2(0.0f, 0.0f), Vector2(33.0f, 28.0f), Vector2::Zero, 1, 0.3f);

			texture = Resources::Load<Texture>(L"headIdle", L"Character\\Marco\\IdleU.png");
			headAni->Create(L"HeadIdle", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 36.0f), Vector2::Zero, 4, 0.3f);

			texture = Resources::Load<Texture>(L"Lbodyidle", L"Character\\Marco\\LIdleD.png");
			bodyAni->Create(L"LBodyIdle", texture, Vector2(0.0f, 0.0f), Vector2(33.0f, 28.0f), Vector2::Zero, 1, 0.3f);

			texture = Resources::Load<Texture>(L"LheadIdle", L"Character\\Marco\\LIdleU.png");
			headAni->Create(L"LHeadIdle", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 36.0f), Vector2::Zero, 4, 0.3f);

			texture = Resources::Load<Texture>(L"MoveLeftU", L"Character\\Marco\\LMoveU.png");
			headAni->Create(L"MoveLeftU", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 34.0f), Vector2::Zero, 12, 0.15f);

			texture = Resources::Load<Texture>(L"MoveLeftD", L"Character\\Marco\\LMoveD.png");
			bodyAni->Create(L"MoveLeftD", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 28.0f), Vector2::Zero, 12, 0.15f);

			texture = Resources::Load<Texture>(L"MoveRightU", L"Character\\Marco\\MoveU.png");
			headAni->Create(L"MoveRightU", texture, Vector2(0.0f, 0.0f), Vector2(40.0f, 34.0f), Vector2::Zero, 12, 0.15f);

			texture = Resources::Load<Texture>(L"MoveRightD", L"Character\\Marco\\MoveD.png");
			bodyAni->Create(L"MoveRightD", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 28.0f), Vector2::Zero, 12, 0.15f);

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
			headAni->Create(L"DownMotion", texture, Vector2(0.0f, 0.0f), Vector2(50.0f, 45.0f), Vector2(0.01f,0.07f), 3, 0.1f);
			headAni->Create(L"DownIdle", texture, Vector2(0.0f, 45.0f), Vector2(50.0f, 45.0f), Vector2(0.01f, 0.07f), 4, 0.3f);
			headAni->Create(L"DownMove", texture, Vector2(0.0f, 90.f), Vector2(50.0f, 45.0f), Vector2::Zero, 7, 0.1f);

			texture = Resources::Load<Texture>(L"def", L"Character\\Marco\\def.png");
			bodyAni->Create(L"def", texture, Vector2(0.0f, 50.f), Vector2(50.0f, 50.0f), Vector2::Zero, 1, 0.1f);
			
			headAni->GetCompleteEvent(L"PistolAttackU") = std::bind(&PlayerScript::End, this);
			headAni->GetCompleteEvent(L"LPistolAttackU") = std::bind(&PlayerScript::End, this);
			headAni->GetCompleteEvent(L"LookTop") = std::bind(&PlayerScript::End, this);
			headAni->GetCompleteEvent(L"LLookTop") = std::bind(&PlayerScript::End, this);
			headAni->GetCompleteEvent(L"DownMotion") = std::bind(&PlayerScript::End, this);
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

	void PlayerScript::Update()
	{
		
		/*if (GetOwner()->GetName() == L"Head")
			headAni->GetOwner()->GetComponent<Animator>();
		else if (GetOwner()->GetName() == L"Body")
			bodyAni->GetOwner()->GetComponent<Animator>();*/

		
		switch (mHeadState)
		{
		case ya::PlayerScript::HeadState::IDLE:
			Idle();
			break;
		case ya::PlayerScript::HeadState::MOVE:
			Move();
			break;
		case ya::PlayerScript::HeadState::HIT:
			Hit();
			break;
		case ya::PlayerScript::HeadState::ATTACK:
			Attack();
			break;
		case ya::PlayerScript::HeadState::SITDOWN:
			SitDown();
			break;
		case ya::PlayerScript::HeadState::SITDOWNMOVE:
			SitDownMove();
			break;
		case ya::PlayerScript::HeadState::SITDOWNATTACK:
			SitDownAttack();
			break;
		case ya::PlayerScript::HeadState::DEATH:
			Death();
			break;
		default:
			break;
		}

		headState = mHeadState;
		bodyState = mBodyState;

		//Transform* mTr = GetOwner()->GetComponent<Transform>();
		////Vector3 rot = tr->GetRotation();
		////rot.z += 10.0f * Time::DeltaTime();
		////tr->SetRotation(rot);
		//if (Input::GetKeyState(eKeyCode::R) == eKeyState::PRESSED)
		//{
		//	Vector3 rot = mTr->GetRotation();
		//	rot.z += 10.0f * Time::DeltaTime();
		//	mTr->SetRotation(rot);
		//	Vector3 pos = mTr->GetPosition();
		//	pos.x += 10.0f * Time::DeltaTime();
		//	mTr->SetPosition(pos);
		//}
		//Animator* animator = GetOwner()->GetComponent<Animator>();
		//if (Input::GetKey(eKeyCode::N_1))
		//{
		//	animator->Play(L"MoveDown");
		//}
	}

	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void PlayerScript::Start()
	{
	}

	void PlayerScript::Action()
	{
	}

	void PlayerScript::End()
	{
		if (mBodyState == BodyState::IDLE)
		{
			if(direction == 1)
				headAni->Play(L"LHeadIdle", true);
			else
				headAni->Play(L"HeadIdle", true);
			mHeadState = HeadState::IDLE;
		}
		if (mBodyState == BodyState::MOVE)
		{
			bodyAni->Play(L"MoveRightD", true);
			mHeadState = HeadState::MOVE;
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			if (direction == 1)
			{
				if (headAni != nullptr)
				{
					headAni->Play(L"LLookTop2", false);
				}
			}
			else
			{
				if (headAni != nullptr)
				{
					headAni->Play(L"LookTop2", false);
				}
			}
		}
		if (mHeadState == HeadState::SITDOWN && mBodyState == BodyState::SITDOWN)
		{
			headAni->Play(L"DownIdle", true);
		}

	}

	void PlayerScript::Idle()
	{

		if (Input::GetKey(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::LEFT))
		{
			mHeadState = HeadState::MOVE;
			mBodyState = BodyState::MOVE;
		}
		if (Input::GetKeyDown(eKeyCode::UP))
		{
			if (direction == 1)
			{
				if (headAni != nullptr)
					headAni->Play(L"LLookTop", false);
			}
			else
			{
				if (headAni != nullptr)
					headAni->Play(L"LookTop", false);
			}
		}
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			mHeadState = HeadState::SITDOWN;
			mBodyState = BodyState::SITDOWN;
			
		}
		if (Input::GetKey(eKeyCode::SPACE))
		{
			
		}
		if (Input::GetKeyDown(eKeyCode::LCTRL))
		{

			mHeadState = HeadState::ATTACK;
		}

		if (headState == mHeadState && bodyState == mBodyState)
			return;

		if (bodyAni != nullptr && headAni != nullptr)
		{
			if (direction == 1)
			{
				bodyAni->Play(L"LBodyIdle", true);
				headAni->Play(L"LHeadIdle", true);
			}
			else
			{
				bodyAni->Play(L"BodyIdle", true);
				headAni->Play(L"HeadIdle", true);
			}
		}
	}

	void PlayerScript::Move()
	{
		if (Input::GetKeyUp(eKeyCode::LEFT) || Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mHeadState = HeadState::IDLE;
			mBodyState = BodyState::IDLE;
			return;
		}
		mHeadState = HeadState::MOVE;
		mBodyState = BodyState::MOVE;

		if (Input::GetKeyDown(eKeyCode::LCTRL))
		{
			if (Input::GetKey(eKeyCode::LEFT))
				direction = 1;

			mHeadState = HeadState::ATTACK;
		}

		Vector3 pos = mTr->GetPosition();
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);

			direction = 1;

			if (headState == mHeadState)
				return;

			if (headAni != nullptr && bodyAni != nullptr)
			{

				headAni->Play(L"MoveLeftU", true);
				bodyAni->Play(L"MoveLeftD", true);

				
			}
		}
		
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
				
			direction = 0;
			if (headState == mHeadState)
				return;

			if (headAni != nullptr && bodyAni != nullptr && (mHeadState == HeadState::MOVE))
			{
				headAni->Play(L"MoveRightU", true);
				bodyAni->Play(L"MoveRightD", true);
			}
		}
	}

	void PlayerScript::Jump()
	{
	}

	void PlayerScript::SitDown()
	{

		if (Input::GetKey(eKeyCode::RIGHT) || Input::GetKey(eKeyCode::LEFT))
		{
			mHeadState = HeadState::SITDOWNMOVE;
			//mBodyState = BodyState::SITDOWNMOVE;
		}

		if (headState == mHeadState && bodyState == mBodyState)
			return;
		if (bodyAni != nullptr && headAni != nullptr)
		{
			if (mHeadState == HeadState::SITDOWN)
			{
				bodyAni->Play(L"def", false);
				headAni->Play(L"DownMotion", false);
			}
		}
	}

	void PlayerScript::SitDownMove()
	{
		if (Input::GetKeyUp(eKeyCode::LEFT) || Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mHeadState = HeadState::SITDOWN;
			mBodyState = BodyState::SITDOWN;
			return;
		}
		//mHeadState = HeadState::SITDOWNMOVE;
		//mBodyState = BodyState::MOVE;

		if (Input::GetKeyDown(eKeyCode::LCTRL))
		{
			if (Input::GetKey(eKeyCode::LEFT))
				direction = 1;

			mHeadState = HeadState::ATTACK;
		}

		Vector3 pos = mTr->GetPosition();
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);

			direction = 1;

			if (headState == mHeadState)
				return;

			if (headAni != nullptr && bodyAni != nullptr)
			{
				headAni->Play(L"DownMove", true);

			}
		}

		//if (Input::GetKey(eKeyCode::RIGHT))
		//{
		//	pos.x += 6.0f * Time::DeltaTime();
		//	mTr->SetPosition(pos);

		//	direction = 0;
		//	if (headState == mHeadState)
		//		return;

		//	if (headAni != nullptr && bodyAni != nullptr && (mHeadState == HeadState::MOVE))
		//	{
		//		headAni->Play(L"MoveRightU", true);
		//		bodyAni->Play(L"MoveRightD", true);
		//	}
		//}
	}

	void PlayerScript::SitDownAttack()
	{
	}

	void PlayerScript::Attack()
	{
		Vector3 pos = mTr->GetPosition();
		
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
			
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 6.0f * Time::DeltaTime();
			mTr->SetPosition(pos);
		}
		

		if (headState == mHeadState )
		{
			//mHeadState = HeadState::IDLE;
			return;
		}

		if (headAni != nullptr && bodyAni != nullptr)
		{
			if (direction == 1)
			{
				if (Input::GetKey(eKeyCode::UP))
					headAni->Play(L"LAttackTop", false);
				else
					headAni->Play(L"LPistolAttackU", false);
			}
			else
			{
				if (Input::GetKey(eKeyCode::UP))
					headAni->Play(L"AttackTop", false);
				
				else
					headAni->Play(L"PistolAttackU", false);

			}

			if (mBodyState == BodyState::IDLE)
			{
				if(direction == 1)
					bodyAni->Play(L"LBodyIdle", true);
				else
					bodyAni->Play(L"BodyIdle", true);
				mHeadState = HeadState::IDLE;
			}

			if (mBodyState == BodyState::MOVE)
			{
				if (direction == 1)
					bodyAni->Play(L"MoveLeftD", true);
				else
					bodyAni->Play(L"MoveRightD", true);
			}
		}
		
	}

	void PlayerScript::Hit()
	{
	}

	void PlayerScript::Death()
	{
	}
}