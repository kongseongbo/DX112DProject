#include "yaMachineGunScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaSceneManager.h"
#include "yaHeadScript.h"
#include "yaInput.h"


namespace ya
{
	MachineGunScript::MachineGunScript()
	{
	}
	MachineGunScript::~MachineGunScript()
	{
	}
	void MachineGunScript::Initalize()
	{
		/*Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::Bullet);

		Collider2D* bulletColl = GetOwner()->AddComponent<Collider2D>();
		bulletColl->SetType(eColliderType::Rect);
		bulletColl->SetCenter(Vector2(0.0f, 0.0f));
		bulletColl->SetSize(Vector2(0.1f, 0.1f));

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"BassBullet", L"Bullet\\BassBullet.png");
		Animator* bulletAni = GetOwner()->AddComponent<Animator>();
		bulletAni->Create(L"BassBullet", texture, Vector2(0.0f, 0.0f), Vector2(18.0f, 18.0f), Vector2::Zero, 1, 0.3f);

		SpriteRenderer* bulletSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bulletSr->SetMaterial(bodyMateiral);
		bulletSr->SetMesh(mesh);

		bulletAni->Play(L"BassBullet", true);*/

	}
	void MachineGunScript::Update()
	{
	}
	void MachineGunScript::FixedUpdate()
	{
	}
	void MachineGunScript::Render()
	{
	}
	void MachineGunScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void MachineGunScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MachineGunScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void MachineGunScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void MachineGunScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void MachineGunScript::OnTriggerExit(Collider2D* collider)
	{
	}
}