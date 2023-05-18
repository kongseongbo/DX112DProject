#include "yaCamelArabianBulletScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaAnimator.h"

namespace ya
{
	CamelArabianBulletScript::CamelArabianBulletScript()
		: Script()
		, mTime(0.0f)
	{
	}
	CamelArabianBulletScript::~CamelArabianBulletScript()
	{
	}
	void CamelArabianBulletScript::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::MonsterAttack);

		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"CamelArabianBullet", L"Bullet\\BassBullet.png");
		ani->Create(L"CamelArabianBullet", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 18.0f), Vector2::Zero, 1, 0.3f);

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> matateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(matateiral);
		sr->SetMesh(mesh);

		ani->Play(L"CamelArabianBullet", true);
	}
	void CamelArabianBulletScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetPosition(Vector3(tr->GetPosition().x - (10.0f * Time::DeltaTime()), tr->GetPosition().y, tr->GetPosition().z));

	}
	void CamelArabianBulletScript::FixedUpdate()
	{
	}
	void CamelArabianBulletScript::Render()
	{
	}
	void CamelArabianBulletScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void CamelArabianBulletScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void CamelArabianBulletScript::OnCollisionExit(Collider2D* collider)
	{
	}
}