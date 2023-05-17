#include "yaDeathScript.h"
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
	DeathScript::DeathScript()
		: Script()
	{
	}
	DeathScript::~DeathScript()
	{
	}
	void DeathScript::Initalize()
	{
		Scene* playScene = SceneManager::GetActiveScene();
		playScene->AddGameObject(GetOwner(), eLayerType::Monster);

		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"CamelArabianDeath", L"CamelArabian\\Death.png");
		ani->Create(L"CamelArabianDeath", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 50.0f), Vector2::Zero, 11, 0.1f);

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> matateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(matateiral);
		sr->SetMesh(mesh);

		ani->Play(L"CamelArabianDeath", true); 
	}
	void DeathScript::Update()
	{
	}
	void DeathScript::FixedUpdate()
	{
	}
	void DeathScript::Render()
	{
	}
}