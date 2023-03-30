#include "yaBullet.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"

namespace ya
{
	Bullet::Bullet()
	{
		SetName(L"Bullet");
		/*Collider2D* bodyCollider = AddComponent<Collider2D>();
		bodyCollider->SetType(eColliderType::Rect);
		bodyCollider->SetCenter(Vector2(-0.5f, -1.0f));
		bodyCollider->SetSize(Vector2(0.1f, 0.05f));*/

		SpriteRenderer* bodyMr = AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bodyMr->SetMaterial(bodyMateiral);
		bodyMr->SetMesh(mesh);

		int a = 0;
	}
	Bullet::~Bullet()
	{
		int a = 0;
	}
	void Bullet::Initalize()
	{
		GameObject::Initalize();
	}
	void Bullet::Update()
	{
		GameObject::Update();
	}
	void Bullet::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Bullet::Render()
	{
		GameObject::Render();
	}
	void Bullet::Attack()
	{
		Transform* tr = GetComponent<Transform>();
		Transform* playerTr = mPlayer->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		float mtime;
		mtime *= Time::DeltaTime();
		//pos.x += 10.0f* Time::DeltaTime();

		tr->SetPosition(Vector3(pos.x += 10.0f * Time::DeltaTime(), playerTr->GetPosition().y, playerTr->GetPosition().z ));

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"smile", L"Smile.png");
		Animator* bulletAni = AddComponent<Animator>();
		bulletAni->Create(L"smile", texture, Vector2(0.0f, 0.0f), Vector2(255.0f, 255.0f), Vector2::Zero, 1, 0.3f);

		bulletAni->Play(L"smile", true);
	}
}

