#include "yaMapScript.h"
#include "yaGameObject.h"
#include "yaArabian.h"
#include "yaArabianScript.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaHeadScript.h"
#include "yaStage1Scene.h"

namespace ya
{
	MapScript::MapScript()
		: Script()
		, mbPlayerCamera(true)

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
		// Arabian Object »ý¼º
		if (GetOwner()->GetName() == L"NewMonster")
		{
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			CreatMonster(pos);
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
	void MapScript::CreatMonster(Vector3 position)
	{
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 10.0f, -3.4f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
		{
			Arabian* arabianObj = new Arabian();
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			Transform* arabianTr = arabianObj->GetComponent<Transform>();
			arabianTr->SetPosition(Vector3(position.x + 15.0f, -3.4f, 5.0f));
			arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
		}
	}
}