#include "yaCompleteScript.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaObject.h"
#include "yaTime.h"

#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaFmod.h"
#include "yaAudioSource.h"

#include "yaTheKeesiScript.h"


namespace ya
{
	CompleteScript::CompleteScript()
		: Script()
		, mTr(nullptr)
		, mAni(nullptr)
		, mKeesiScript(nullptr)
		, mTime(0.0f)
	{
	}
	CompleteScript::~CompleteScript()
	{
	}
	void CompleteScript::Initalize()
	{
		mTr = GetOwner()->GetComponent<Transform>();

		mAni = GetOwner()->AddComponent<Animator>();
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"one", L"Spelling\\one.png");
		mAni->Create(L"one", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"C", L"Spelling\\C.png");
		mAni->Create(L"C", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);
		mAni->Create(L"CC", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"E", L"Spelling\\E.png");
		mAni->Create(L"E", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);
		mAni->Create(L"EE", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"I", L"Spelling\\I.png");
		mAni->Create(L"I", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);
		mAni->Create(L"II", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"L", L"Spelling\\L.png");
		mAni->Create(L"L", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"M", L"Spelling\\M.png");
		mAni->Create(L"M", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);
		mAni->Create(L"MM", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"N", L"Spelling\\N.png");
		mAni->Create(L"N", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"O", L"Spelling\\O.png");
		mAni->Create(L"O", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);
		mAni->Create(L"OO", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"P", L"Spelling\\P.png");
		mAni->Create(L"P", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"S", L"Spelling\\S.png");
		mAni->Create(L"S", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);
		mAni->Create(L"SS", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"T", L"Spelling\\T.png");
		mAni->Create(L"T", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		texture = Resources::Load<Texture>(L"WOW", L"Spelling\\WOW.png");
		mAni->Create(L"WOW", texture, Vector2(0.0f, 0.0f), Vector2(30.0f, 30.0f), Vector2::Zero, 1, 0.1f);

		SpriteRenderer* sr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(material);
		sr->SetMesh(mesh);

		AudioSource* aaa = GetOwner()->AddComponent<AudioSource>();
		std::shared_ptr<AudioClip> myAudioClip = Resources::Load<AudioClip>(L"missioncomplete", L"Sound\\missioncomplete.mp3");
		aaa->SetClip(myAudioClip);
		aaa->SetLoop(false);
	}
	void CompleteScript::Update()
	{		
		if (mKeesiScript->GetComplete())
		{
			Complete(GetOwner()->GetName(), 0.0f);
		}
	}
	void CompleteScript::FixedUpdate()
	{
	}
	void CompleteScript::Render()
	{
	}
	void CompleteScript::Complete(std::wstring aniname, float time)
	{
		mAni->Play(aniname, false);

		float x = mTr->GetPosition().x;
		float distance = 0.0f;

		if (aniname == L"M")
			distance = 158.0f;
		if (aniname == L"I")
			distance = 160.0f;
		if (aniname == L"S")
			distance = 162.0f;
		if (aniname == L"SS")
			distance = 164.0f;
		if (aniname == L"II")
			distance = 166.0f;
		if (aniname == L"O")
			distance = 168.0f;
		if (aniname == L"N")
			distance = 170.0f;
		if (aniname == L"one")
			distance = 172.0f;

		if (aniname == L"C")
			distance = 157.0f;
		if (aniname == L"OO")
			distance = 159.0f;
		if (aniname == L"MM")
			distance = 161.0f;
		if (aniname == L"P")
			distance = 163.0f;
		if (aniname == L"L")
			distance = 165.0f;
		if (aniname == L"E")
			distance = 167.0f;
		if (aniname == L"T")
			distance = 169.0f;
		if (aniname == L"EE")
			distance = 171.0f;
		if (aniname == L"WOW")
			distance = 173.0f;

		if (x < distance)
		{
			x += 10.0f * Time::DeltaTime();
			AudioSource* aaa = GetOwner()->GetComponent<AudioSource>();
			aaa->Play();
		}
		mTr->SetPosition(Vector3(x, mTr->GetPosition().y, mTr->GetPosition().z));
		
	}
}