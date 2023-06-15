#include "yaCompleteScript.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaTime.h"
namespace ya
{
	CompleteScript::CompleteScript()
		: Script()
		, mTr(nullptr)
		, mAni(nullptr)
	{
	}
	CompleteScript::~CompleteScript()
	{
	}
	void CompleteScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		mAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"1", L"Spelling\\1.png");
		mAni->Create(L"1", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"C", L"Spelling\\C.png");
		mAni->Create(L"C", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"E", L"Spelling\\E.png");
		mAni->Create(L"E", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"I", L"Spelling\\I.png");
		mAni->Create(L"I", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"L", L"Spelling\\L.png");
		mAni->Create(L"L", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"M", L"Spelling\\M.png");
		mAni->Create(L"M", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"N", L"Spelling\\N.png");
		mAni->Create(L"N", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"O", L"Spelling\\O.png");
		mAni->Create(L"O", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"P", L"Spelling\\P.png");
		mAni->Create(L"P", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"S", L"Spelling\\S.png");
		mAni->Create(L"S", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"T", L"Spelling\\T.png");
		mAni->Create(L"T", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"WOW", L"Spelling\\WOW.png");
		mAni->Create(L"WOW", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		SpriteRenderer* arabianSr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> arabianMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		arabianSr->SetMaterial(arabianMaterial);
		arabianSr->SetMesh(mesh);

	
	}
	void CompleteScript::Update()
	{
		if (GetOwner()->GetName() == L"M")
		{
			mAni->Play(L"M", false);
			float x = mTr->GetPosition().x;
			if(x < 165.0f)
				x += 2.0f * Time::DeltaTime();
			mTr->SetPosition(Vector3(x, mTr->GetPosition().y, mTr->GetPosition().z));
		}
	}
	void CompleteScript::FixedUpdate()
	{
	}
	void CompleteScript::Render()
	{
	}
	void CompleteScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void CompleteScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void CompleteScript::OnCollisionExit(Collider2D* collider)
	{
	}
}