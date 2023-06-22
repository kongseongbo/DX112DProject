#include "yaMapScript.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaStage1Scene.h"
#include "yaObject.h"
#include "yaSpriteRenderer.h"
#include "yaResources.h"
#include "yaTime.h"

#include "yaHeadScript.h"

#include "yaArabian.h"
#include "yaArabianScript.h"

#include "yaCamelArabian.h"
#include "yaCamelArabianScript.h"

#include "yaHelicopter.h"
#include "yaHelicopterScript.h"

#include "yaTheKeesi.h"
#include "yaEngineEffectScript.h"

#include "yaCompleteScript.h"

#include "yaPoroScript.h"

namespace ya
{
	MapScript::MapScript()
		: Script()
		, mTr(nullptr)
		, mPlayer(nullptr)
		, mThekeesiScript(nullptr)
		, mbPlayerCamera(true)
		, mTime(0.0f)
	{
	}
	MapScript::~MapScript()
	{
	}
	void MapScript::Initalize()
	{
	}
	void MapScript::Update()
	{
		
	}
	void MapScript::FixedUpdate()
	{
	}
	void MapScript::Render()
	{
	}
	void MapScript::OnCollisionEnter(Collider2D* collider)
	{
		mTime += Time::DeltaTime();

		// Arabian Object 持失
		if (GetOwner()->GetName() == L"CreateArabian")
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			CreateArabian(pos);
		}
		if (GetOwner()->GetName() == L"CreateArabian1")
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			CreateArabian1(pos);
		}
		if (GetOwner()->GetName() == L"CreateArabian2")
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			CreateArabian2(pos);
		}
		if (GetOwner()->GetName() == L"CreateArabian3")
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			CreateArabian3(pos);
		}

		// CamelArabian Object 持失
		if (GetOwner()->GetName() == L"CreateCamelArabian")
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			CreateCamelArabian(pos);
		}

		// Helicopter Object 持失
		if (GetOwner()->GetName() == L"CreateHelicopter")
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			CreateHelicopter(pos);
		}

		if (GetOwner()->GetName() == L"CreateThekeesi")
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			CreateThekeesi(pos);
		}

		if (collider->GetOwner()->GetName() == L"Head" && GetOwner()->GetName() == L"MapLeft")
		{
			HeadScript* headScr = collider->GetOwner()->GetScript<HeadScript>();
			headScr->SetStop(-1);
		}

		if (collider->GetOwner()->GetName() == L"Head" && GetOwner()->GetName() == L"MapRight")
		{
			HeadScript* headScr = collider->GetOwner()->GetScript<HeadScript>();
			headScr->SetStop(1);
		}

	}
	void MapScript::OnCollisionStay(Collider2D* collider)
	{
		if (collider->GetOwner()->GetName() == L"Head" && GetOwner()->GetName() == L"CollMap")
		{
			mbPlayerCamera = true;
			if(Input::GetKey(eKeyCode::RIGHT))
			{ 
				Transform* playerTr = collider->GetOwner()->GetComponent<Transform>();
				Transform* tr = GetOwner()->GetComponent<Transform>();
				tr->SetPosition(Vector3(playerTr->GetPosition().x, tr->GetPosition().y, tr->GetPosition().z));
			}
		}
	}
	void MapScript::OnCollisionExit(Collider2D* collider)
	{
		if (collider->GetOwner()->GetName() == L"Head" && GetOwner()->GetName() == L"MapLeft" || collider->GetOwner()->GetName() == L"Head" && GetOwner()->GetName() == L"MapRight")
		{
			HeadScript* headScr = collider->GetOwner()->GetScript<HeadScript>();
			headScr->SetStop(0);
		}
	}

	void MapScript::CreateArabian(Vector3 position)
	{
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 10.0f, -3.5f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 15.0f, -3.5f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		// poro
		{
			GameObject* obj = new GameObject();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(obj, eLayerType::Obj);
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(position.x + 18.0f, -3.5f, 5.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			obj->AddComponent<Animator>();
			Collider2D* coll = obj->AddComponent<Collider2D>();
			coll->SetType(eColliderType::Rect);
			coll->SetSize(Vector2(0.1f, 0.1f));

			PoroScript* script = obj->AddComponent<PoroScript>();
		}

	}
	void MapScript::CreateArabian1(Vector3 position)
	{
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 10.0f, -3.5f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 15.0f, -3.5f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
	}
	void MapScript::CreateArabian2(Vector3 position)
	{
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 13.0f, -3.5f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 16.0f, -3.5f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 17.0f, 2.5f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 12.0f, 5.8f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 13.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 19.0f, 5.8f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 13.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
	}

	void MapScript::CreateArabian3(Vector3 position)
	{
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 9.0f, -3.5f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 13.0f, -3.5f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 18.0f, -3.5f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 13.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 22.0f, -3.5f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 13.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 12.0f, 3.2f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 16.0f, 3.2f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 13.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 21.0f, 3.2f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 13.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}

	}

	void MapScript::CreateCamelArabian(Vector3 position)
	{
		{
			CamelArabian* camelArabian = object::Instantiate<CamelArabian>(eLayerType::Monster);
			camelArabian->SetName(L"CamelArabian");
			Transform* tr = camelArabian->GetComponent<Transform>();
			tr->SetPosition(Vector3(-15.0f, -2.0f, 5.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			camelArabian->AddComponent<Animator>();
			camelArabian->AddComponent<Collider2D>();
			camelArabian->AddComponent<CamelArabianScript>();

			SpriteRenderer* sr = camelArabian->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> matateiral = Resources::Find<Material>(L"SpriteMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMaterial(matateiral);
			sr->SetMesh(mesh);
		}
		{
			GameObject* obj = new GameObject();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(obj, eLayerType::Obj);
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(position.x + 18.0f, -3.5f, 5.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			obj->AddComponent<Animator>();
			Collider2D* coll = obj->AddComponent<Collider2D>();
			coll->SetType(eColliderType::Rect);
			coll->SetSize(Vector2(0.1f, 0.1f));

			PoroScript* script = obj->AddComponent<PoroScript>();
		}
	}

	void MapScript::CreateHelicopter(Vector3 position)
	{
		{
			Helicopter* heliObj = object::Instantiate<Helicopter>(eLayerType::Monster);
			heliObj->SetName(L"Helicopter");
			Transform* heliTr = heliObj->GetComponent<Transform>();
			heliTr->SetPosition(Vector3(135.0f, 5.0f, 5.0f));
			heliTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			HelicopterScript* scr = heliObj->AddComponent<HelicopterScript>();
			scr->SetPlayer(mPlayer);
		}

		{
			Helicopter* heliObj = object::Instantiate<Helicopter>(eLayerType::Monster);
			heliObj->SetName(L"Helicopter");
			Transform* heliTr = heliObj->GetComponent<Transform>();
			heliTr->SetPosition(Vector3(140.0f, 5.0f, 5.0f));
			heliTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			HelicopterScript* scr = heliObj->AddComponent<HelicopterScript>();
			scr->SetPlayer(mPlayer);
			scr->SetTime(1.3f);
			scr->SetDirection(true);
		}
	}
	void MapScript::CreateThekeesi(Vector3 position)
	{
		TheKeesi* thekeesi = object::Instantiate<TheKeesi>(eLayerType::Monster);
		thekeesi->SetName(L"TheKeesi");
		Transform* tr = thekeesi->GetComponent<Transform>();
		tr->SetPosition(Vector3(164.0f, 4.0f, 5.0f));
		tr->SetScale(Vector3(15.0f, 15.0f, 1.0f));

		mThekeesiScript = thekeesi->AddComponent<TheKeesiScript>();
		mThekeesiScript->SetPlayer(mPlayer);
		mThekeesiScript->SetCameraScript(cameraScript);
		SpriteRenderer* sr = thekeesi->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> matateiral = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		sr->SetMaterial(matateiral);
		sr->SetMesh(mesh);

		GameObject* leftgroundeffect = object::Instantiate<GameObject>(eLayerType::Effect);
		//
		GameObject* lefteffect = object::Instantiate<GameObject>(eLayerType::Monster);
		lefteffect->SetName(L"leftengineeffect");
		Transform* leftTr = lefteffect->GetComponent<Transform>();
		leftTr->SetScale(Vector3(10.0f, 10.0f, 4.9f));

		EngineEffectScript* lefteffectScript = lefteffect->AddComponent<EngineEffectScript>();
		lefteffectScript->SetParent(tr);
		lefteffectScript->SetLeftGroundEffect(leftgroundeffect);

		SpriteRenderer* leftSr = lefteffect->AddComponent<SpriteRenderer>();
		leftSr->SetMaterial(matateiral);
		leftSr->SetMesh(mesh);


		GameObject* rightgroundeffect = object::Instantiate<GameObject>(eLayerType::Effect);
		
		//
		GameObject* righteffect = object::Instantiate<GameObject>(eLayerType::Monster);
		righteffect->SetName(L"rightengineeffect");

		Transform* rightTr = righteffect->GetComponent<Transform>();
		rightTr->SetScale(Vector3(10.0f, 10.0f, 4.9f));
		rightTr->SetRotation(Vector3(1.0f, 180.0f, 1.0f));

		EngineEffectScript* righteffectScript = righteffect->AddComponent<EngineEffectScript>();
		righteffectScript->SetParent(tr);
		righteffectScript->SetRightGroundEffect(rightgroundeffect);

		SpriteRenderer* rightSr = righteffect->AddComponent<SpriteRenderer>();
		rightSr->SetMaterial(matateiral);
		rightSr->SetMesh(mesh);

		mThekeesiScript->SetLeftEffect(lefteffectScript);
		mThekeesiScript->SetRightEffect(righteffectScript);

		MissionComplete();
	}

	void MapScript::MissionComplete()
	{

		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"M");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(144.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"I");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(145.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"S");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(146.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"SS");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(147.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"II");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(148.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"O");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(149.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"N");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(150.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"one");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(151.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		//
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"C");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(144.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"OO");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(145.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"MM");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(146.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"P");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(147.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"L");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(148.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"E");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(149.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"T");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(150.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"EE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(151.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect);
			obj->SetName(L"WOW");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(152.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
	}
}