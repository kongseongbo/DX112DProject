#include "yaDoorScript.h"
#include "yaObject.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaTime.h"
namespace ya
{
	DoorScript::DoorScript()
		: Script()
		, mTime(0.0f)
		, mNext(false)
		, mLeft(nullptr)
		, mCenter(nullptr)
		, mRight(nullptr)
		, mBaseScript(nullptr)
		, mCameraScript(nullptr)
		, ox(false)
	{

	}
	DoorScript::~DoorScript()
	{

	}
	void DoorScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();
	
		Animator* ani = GetOwner()->GetComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Door", L"MosqueArtillery\\Door.png");
		ani->Create(L"Door", texture, Vector2(0.0f, 0.0f), Vector2(58.0f, 58.0f), Vector2(0.0f, 0.0f), 1, 0.2f);

		texture = Resources::Load<Texture>(L"DoorDestroy", L"MosqueArtillery\\DoorDestroy.png");
		ani->Create(L"DoorDestroy", texture, Vector2(0.0f, 0.0f), Vector2(180.0f, 145.0f), Vector2(0.0f, 0.0f), 14, 0.1f);

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(mateiral);
		sr->SetMesh(mesh);

		ani->Play(L"Door", false);
	}
	void DoorScript::Update()
	{
		Animator* ani = GetOwner()->GetComponent<Animator>();

		int left = (UINT)mLeft->GetState();
		int center = (UINT)mCenter->GetState();
		int right = (UINT)mRight->GetState();

		if (left == 3 && center == 3 && right == 3)
		{
			if(!ani->IsAnimationRunning(L"DoorDestroy"))
				ani->Play(L"DoorDestroy", true);

			mBaseScript->SetSpriteChange(true);

			if (!ox)
			{
				Transform* cameraTr = mCameraScript->GetOwner()->GetComponent<Transform>();
				Vector3 pos = cameraTr->GetPosition();
				pos.x -= 5.0f;
				cameraTr->SetPosition(pos);
				ox = true;
			}
			
			mCameraScript->strongEffectOn();

			mTime += 1.0f * Time::DeltaTime();
			Vector3 scale = mTr->GetScale();
			scale.x += 0.5f * Time::DeltaTime();
			scale.y += 0.5f * Time::DeltaTime();
			mTr->SetScale(scale);

			if (mTime > 2.0f)
			{
				mNext = true;
				GetOwner()->Death();
			}
		}

	}
	void DoorScript::FixedUpdate()
	{
	}
	void DoorScript::Render()
	{
	}
}