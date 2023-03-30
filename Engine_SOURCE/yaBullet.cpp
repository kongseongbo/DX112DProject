#include "yaBullet.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"



namespace ya
{
	Bullet::Bullet()
	{


		int a = 0;
	}
	Bullet::~Bullet()
	{
	}
	void Bullet::Initalize()
	{
		/*std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"smile", L"Smile.png");
		Animator* bulletAni = AddComponent<Animator>();
		bulletAni->Create(L"smile", texture, Vector2(0.0f, 0.0f), Vector2(255.0f, 255.0f), Vector2::Zero, 1, 0.3f);

		bulletAni->Play(L"smile", false);*/
		//GameObject::Initalize();
	}
	void Bullet::Update()
	{
		//GameObject::Update();
	}
	void Bullet::FixedUpdate()
	{
		//GameObject::FixedUpdate();
	}
	void Bullet::Render()
	{
		//GameObject::Render();
	}
}

