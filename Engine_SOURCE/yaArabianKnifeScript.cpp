#include "yaArabianKnifeScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaHeadScript.h"
#include "yaInput.h"
#include "yaRigidbody.h"

namespace ya
{
	ArabianKnifeScript::ArabianKnifeScript()
		: Script()
		, mTime(0.0f)
	{
	}
	ArabianKnifeScript::~ArabianKnifeScript()
	{
	}
	void ArabianKnifeScript::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::MonsterAttack);

		Collider2D* knifeColl = GetOwner()->AddComponent<Collider2D>();
		knifeColl->SetType(eColliderType::Rect);
		knifeColl->SetCenter(Vector2(0.0f, 0.0f));
		knifeColl->SetSize(Vector2(0.2f, 0.2f));

		GetOwner()->AddComponent<Rigidbody>();

		Animator* knifeAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"knife", L"Arabian\\Attack2Knife.png");
		knifeAni->Create(L"knife", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 38.0f), Vector2::Zero, 12, 0.1f);

		SpriteRenderer* knifeSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		knifeSr->SetMaterial(material);
		knifeSr->SetMesh(mesh);

		knifeAni->Play(L"knife", true);

		//knifeAni->GetCompleteEvent(L"BombEffect") = std::bind(&ArabianKnifeScript::End, this);
	}
	void ArabianKnifeScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x -= 5.0f * Time::DeltaTime();
		tr->SetPosition(pos);
	}
	void ArabianKnifeScript::FixedUpdate()
	{
	}
	void ArabianKnifeScript::Render()
	{
	}
	void ArabianKnifeScript::OnCollisionEnter(Collider2D* collider)
	{
		GetOwner()->Death();
	}
	void ArabianKnifeScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void ArabianKnifeScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void ArabianKnifeScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void ArabianKnifeScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void ArabianKnifeScript::OnTriggerExit(Collider2D* collider)
	{
	}
	void ArabianKnifeScript::End()
	{
	}
}