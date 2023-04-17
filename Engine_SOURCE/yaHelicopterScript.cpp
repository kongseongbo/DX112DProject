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
		heliAni->Create(L"LeftIdle", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 70.0f), Vector2::Zero, 6, 0.1f);

		texture = Resources::Load<Texture>(L"LeftIdle2", L"Helicopter\\LeftIdle2.png");
		heliAni->Create(L"LeftIdle2", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 80.0f), Vector2::Zero, 6, 0.1f);

		texture = Resources::Load<Texture>(L"LeftMove", L"Helicopter\\LeftMove.png");
		heliAni->Create(L"LeftMove", texture, Vector2(0.0f, 0.0f), Vector2(100.0f, 80.0f), Vector2::Zero, 6, 0.1f);
		heliAni->Create(L"LeftMove2", texture, Vector2(0.0f, 80.0f), Vector2(100.0f, 80.0f), Vector2::Zero, 6, 0.1f);

		SpriteRenderer* heliSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> heliMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		heliSr->SetMaterial(heliMaterial);
		heliSr->SetMesh(mesh);

		heliAni->Play(L"LeftMove2", true);

		//heliAni->GetCompleteEvent(L"BombEffect") = std::bind(&HelicopterScript::End, this);
	}
	void HelicopterScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		pos -= pos.Right * 5.0f * Time::DeltaTime();

		tr->SetPosition(pos);
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
	void HelicopterScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void HelicopterScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void HelicopterScript::OnTriggerExit(Collider2D* collider)
	{
	}
}