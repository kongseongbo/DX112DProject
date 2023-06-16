#include "yaHelicopterScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaRigidbody.h"


namespace ya
{
	HelicopterScript::HelicopterScript()
		: Script()
		, mPlayer(nullptr)
		, mRot(0.0f)
	{
	}
	HelicopterScript::~HelicopterScript()
	{
	}
	void HelicopterScript::Initalize()
	{
		/*Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::Monster);*/

		Collider2D* heliColl = GetOwner()->AddComponent<Collider2D>();
		heliColl->SetType(eColliderType::Rect);
		heliColl->SetCenter(Vector2(0.0f, 0.0f));
		heliColl->SetSize(Vector2(0.1f, 0.1f));

		//GetOwner()->AddComponent<Rigidbody>();

		Animator* heliAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"LeftIdle", L"Helicopter\\LeftIdle.png");
		heliAni->Create(L"Left0", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 70.0f), Vector2::Zero, 6, 0.1f);

		texture = Resources::Load<Texture>(L"LeftIdle2", L"Helicopter\\LeftIdle2.png");
		heliAni->Create(L"Left02", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 80.0f), Vector2::Zero, 6, 0.1f);

		texture = Resources::Load<Texture>(L"LeftMove", L"Helicopter\\LeftMove.png");
		heliAni->Create(L"LeftMove", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 80.0f), Vector2::Zero, 6, 0.1f);
		heliAni->Create(L"LeftMove2", texture, Vector2(0.0f, 80.0f), Vector2(100.0f, 80.0f), Vector2::Zero, 6, 0.1f);

		texture = Resources::Load<Texture>(L"Rotation", L"Helicopter\\Rotation.png");
		heliAni->Create(L"Left18", texture, Vector2(0.0f, 0.0f), Vector2(80.0f, 90.0f), Vector2(0.01f,0.0f), 6, 0.1f);
		heliAni->Create(L"Left36", texture, Vector2(0.0f, 90.0f), Vector2(80.0f, 90.0f), Vector2(0.01f, 0.0f), 6, 0.1f);
		heliAni->Create(L"Left54", texture, Vector2(0.0f, 180.0f), Vector2(80.0f, 90.0f), Vector2(-0.01f, 0.0f), 6, 0.1f);

		heliAni->Create(L"90", texture, Vector2(0.0f, 270.0f), Vector2(80.0f, 90.0f), Vector2::Zero, 6, 0.1f);

		heliAni->Create(L"Right54", texture, Vector2(0.0f, 360.0f), Vector2(80.0f, 90.0f), Vector2(-0.01f, 0.0f), 6, 0.1f);
		heliAni->Create(L"Right36", texture, Vector2(0.0f, 450.0f), Vector2(80.0f, 90.0f), Vector2(-0.01f, 0.0f), 6, 0.1f);
		heliAni->Create(L"Right18", texture, Vector2(0.0f, 540.0f), Vector2(80.0f, 90.0f), Vector2(0.01f, 0.0f), 6, 0.1f);


		SpriteRenderer* heliSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> heliMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		heliSr->SetMaterial(heliMaterial);
		heliSr->SetMesh(mesh);

		heliAni->Play(L"Left0", true);

		//heliAni->GetCompleteEvent(L"BombEffect") = std::bind(&HelicopterScript::End, this);
	}
	void HelicopterScript::Update()
	{
		Animator* heliAni = GetOwner()->GetComponent<Animator>();

		Vector3 playerPos = mPlayer->GetComponent<Transform>()->GetPosition();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 rot = GetOwner()->GetComponent<Transform>()->GetRotation();

		float aaa = atan2(playerPos.y - pos.y, playerPos.x - pos.x);
		mRot = fmodf((aaa * (180.0f / XM_PI) + 180.0f), 360.0f);

		if (mRot <= 65.0f)
		{
			if(!heliAni->IsAnimationRunning(L"Left18"))
				heliAni->Play(L"Left18", true);
		}

		if (mRot >= 65.0f && mRot <= 75.0f)
		{
			if (!heliAni->IsAnimationRunning(L"Left36"))
				heliAni->Play(L"Left36", true);
		}

		if (mRot >= 75.0f && mRot <= 85.0f)
		{
			if (!heliAni->IsAnimationRunning(L"Left54"))
				heliAni->Play(L"Left54", true);
		}

		if (mRot >= 85.0f && mRot <= 95.0f)
		{
			if (!heliAni->IsAnimationRunning(L"90"))
				heliAni->Play(L"90", true);
		}

		if (mRot >= 95.0f && mRot <= 105.0f)
		{
			if (!heliAni->IsAnimationRunning(L"Right18"))
				heliAni->Play(L"Right18", true);
		}

		if (mRot >= 105.0f && mRot <= 115.0f)
		{
			if (!heliAni->IsAnimationRunning(L"Right36"))
				heliAni->Play(L"Right36", true);
		}

		if (mRot >= 115.0f )
		{
			if (!heliAni->IsAnimationRunning(L"Right54"))
				heliAni->Play(L"Right54", true);
		}

		/*rot.y = mP2Mangle;
		GetOwner()->GetComponent<Transform>()->SetRotation(rot);*/

		/*Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		pos -= pos.Right * 5.0f * Time::DeltaTime();

		tr->SetPosition(pos);*/
	}
	void HelicopterScript::FixedUpdate()
	{
	}
	void HelicopterScript::Render()
	{
	}
	void HelicopterScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void HelicopterScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void HelicopterScript::OnCollisionExit(Collider2D* collider)
	{
	}
}