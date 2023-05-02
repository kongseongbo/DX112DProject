#include "yaParachuteScript.h"
#include "yaGameObject.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"
#include "yaHeadScript.h"
#include "yaRigidbody.h"

namespace ya
{
	ParachuteScript::ParachuteScript()
		: mAni(nullptr)
		, mTime(0.0f)
	{
	}
	ParachuteScript::~ParachuteScript()
	{
	}
	void ParachuteScript::Initalize()
	{

		mAni = GetOwner()->AddComponent<Animator>();

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"parachute", L"Character\\Marco\\parachute.png");
		mAni->Create(L"parachute", texture, Vector2(0.0f, 0.0f), Vector2(70.0f, 49.0f), Vector2::Zero, 5, 0.3f);

		mAni->Create(L"deleteparachute", texture, Vector2(0.0f, 49.0f), Vector2(70.0f, 49.0f), Vector2(0.02f,0.01f), 17, 0.1f);

		SpriteRenderer* bulletSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> Mateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		bulletSr->SetMaterial(Mateiral);
		bulletSr->SetMesh(mesh);

		mAni->GetCompleteEvent(L"deleteparachute") = std::bind(&ParachuteScript::End, this);
		
		mAni->Play(L"parachute", true);
	}
	void ParachuteScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Transform* playerTr = mPlayer->GetComponent<Transform>();
		
		Vector3 pos = playerTr->GetPosition();
		pos.y += 1.2f;
		pos.x -= 0.5f;
		tr->SetPosition(pos);

		Rigidbody* playerRigid = mPlayer->GetComponent<Rigidbody>();

		if (playerRigid->GetGround() && mTime == 0)
		{
			mAni->Play(L"deleteparachute", false);
			mTime++;
		}

	}
	void ParachuteScript::FixedUpdate()
	{
	}
	void ParachuteScript::Render()
	{
	}
	void ParachuteScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void ParachuteScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void ParachuteScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void ParachuteScript::End()
	{
		GetOwner()->Death();
	}
}