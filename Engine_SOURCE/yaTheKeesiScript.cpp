#include "yaTheKeesiScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaCollider2D.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"

#include "yaFlamestrikeScript.h"
#include "yaBossArabianScript.h"
#include "yaDeathEffect.h"



namespace ya
{
	TheKeesiScript::TheKeesiScript()
		: Script()
		, mTheKeesiState(TheKeesiState::IDLE)
		, mPlayer(nullptr)
		, playerTr(nullptr)
		, mTr(nullptr)
		, mTime(0.0f)
		, mRightEf(nullptr)
		, mLeftEf(nullptr)
		, mRightScript(nullptr)
		, mLeftScript(nullptr)
		, mCameraScript(nullptr)
		, mbMove(false)
		, mbComplete(false)
		, mIndex(0)
		, mStack(0)
		, obj(nullptr)
		, obj2(nullptr)
		, obj3(nullptr)
		, obj4(nullptr)
		, mEffectTime(0.0f)
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
			//mbMove = false;
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
		if (mTime > 5.0f)
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
			mTime = 0.0f;
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
		if (!mbMove || mbMove)
		{
			if (y <= -1.0f)
			{
				ani->Play(L"TheKeesiDie", false);
				mCameraScript->strongEffectOn();
				mTime += 2.0f * Time::DeltaTime();
				if (mTime > 3.0f)
				{
					obj->Death();
					obj2->Death();
					obj3->Death();
					obj4->Death();
					CreateMissionClear();
				}
			}
			else
			{
				mEffectTime += 0.5 * Time::DeltaTime();
				
				if(obj == nullptr)
				{
					obj = object::Instantiate<GameObject>(eLayerType::Monster);
					Transform* tr = obj->GetComponent<Transform>();
					tr->SetPosition(Vector3(mTr->GetPosition().x - 1.0f, mTr->GetPosition().y - 1.5f, mTr->GetPosition().z - 1.0f));
					tr->SetScale(Vector3(12.0f, 12.0f, 12.0f));
					Animator* ani = obj->AddComponent<Animator>();
					DeathEffect* effect = obj->AddComponent<DeathEffect>();

					SpriteRenderer* sr = obj->AddComponent<SpriteRenderer>();
					std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
					std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
					sr->SetMaterial(material);
					sr->SetMesh(mesh);
				}
				if (mEffectTime > 1.8f)
				{
					if (obj2 == nullptr)
					{
						obj2 = object::Instantiate<GameObject>(eLayerType::Monster);
						Transform* tr = obj2->GetComponent<Transform>();
						tr->SetPosition(Vector3(mTr->GetPosition().x - 2.0f, mTr->GetPosition().y - 1.2f, mTr->GetPosition().z - 1.0f));
						tr->SetScale(Vector3(12.0f, 12.0f, 12.0f));
						Animator* ani = obj2->AddComponent<Animator>();
						DeathEffect* effect = obj2->AddComponent<DeathEffect>();

						SpriteRenderer* sr = obj2->AddComponent<SpriteRenderer>();
						std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
						std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
						sr->SetMaterial(material);
						sr->SetMesh(mesh);
					}
				}
				if (mEffectTime > 0.4f)
				{
					if (obj3 == nullptr)
					{
						obj3 = object::Instantiate<GameObject>(eLayerType::Monster);
						Transform* tr = obj3->GetComponent<Transform>();
						tr->SetPosition(Vector3(mTr->GetPosition().x + 2.0f, mTr->GetPosition().y - 1.8f, mTr->GetPosition().z - 1.0f));
						tr->SetScale(Vector3(12.0f, 12.0f, 12.0f));
						Animator* ani = obj3->AddComponent<Animator>();
						DeathEffect* effect = obj3->AddComponent<DeathEffect>();
						SpriteRenderer* sr = obj3->AddComponent<SpriteRenderer>();
						std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
						std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
						sr->SetMaterial(material);
						sr->SetMesh(mesh);
					}
				}
				if (mEffectTime > 1.3f)
				{
					if (obj4 == nullptr)
					{
						obj4 = object::Instantiate<GameObject>(eLayerType::Monster);
						Transform* tr = obj4->GetComponent<Transform>();
						tr->SetPosition(Vector3(mTr->GetPosition().x + 3.0f, mTr->GetPosition().y + 2.0f, mTr->GetPosition().z - 1.0f));
						tr->SetScale(Vector3(12.0f, 12.0f, 12.0f));
						Animator* ani = obj4->AddComponent<Animator>();
						DeathEffect* effect = obj4->AddComponent<DeathEffect>();
						SpriteRenderer* sr = obj4->AddComponent<SpriteRenderer>();
						std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
						std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
						sr->SetMaterial(material);
						sr->SetMesh(mesh);
					}
				}
				y -= 0.5f * Time::DeltaTime();

			}
		}

		mTr->SetPosition(Vector3(mTr->GetPosition().x, y, mTr->GetPosition().z));


	}
	void TheKeesiScript::End()
	{

	}

	void TheKeesiScript::CreateMissionClear()
	{
		mbComplete = true;
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