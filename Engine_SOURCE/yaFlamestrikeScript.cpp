#include "yaFlamestrikeScript.h"
#include "yaGameObject.h"
#include "yaCollider2D.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"

namespace ya
{
	FlamestrikeScript::FlamestrikeScript()
		:Script()
		, mTr(nullptr)
		, mTime(0.0f)
	{
	}
	FlamestrikeScript::~FlamestrikeScript()
	{
	}
	void FlamestrikeScript::Initalize()
	{
		Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"groundeffect", L"TheKeesi\\groundeffect.png");
		ani->Create(L"groundeffect", texture, Vector2(910.0f, 0.0f), Vector2(70.0f, 36.0f), Vector2::Zero, 7, 0.2f);

		texture = Resources::Load<Texture>(L"DeathEffect", L"Helicopter\\DeathEffect.png");
		ani->Create(L"DeathEffect", texture, Vector2(0.0f, 0.0f), Vector2(90.0f, 56.0f), Vector2(0.01f, 0.0f), 6, 0.2f);
		

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> matateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(matateiral);
		sr->SetMesh(mesh);

		ani->Play(L"groundeffect", true);
	}
	void FlamestrikeScript::Update()
	{

	}
	void FlamestrikeScript::FixedUpdate()
	{
	}
	void FlamestrikeScript::Render()
	{
	}
	void FlamestrikeScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void FlamestrikeScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void FlamestrikeScript::OnCollisionExit(Collider2D* collider)
	{
	}
}