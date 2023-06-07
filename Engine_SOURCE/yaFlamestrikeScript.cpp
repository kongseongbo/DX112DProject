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

	/*	Animator* ani = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Flame", L"TheKeesi\\Flame.png");
		ani->Create(L"CreateFlame", texture, Vector2(0.0f, 0.0f), Vector2(60.0f, 170.0f), Vector2::Zero, 12, 0.2f);

		texture = Resources::Load<Texture>(L"Flame2", L"TheKeesi\\Flame2.png");

		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetType(eColliderType::Rect);
		coll->SetSize(Vector2(0.1f, 0.2f));

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> matateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(matateiral);
		sr->SetMesh(mesh);

		ani->Play(L"CreateFlame", false);*/
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