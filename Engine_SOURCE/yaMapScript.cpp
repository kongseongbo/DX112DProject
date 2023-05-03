#include "yaMapScript.h"
#include "yaGameObject.h"
#include "yaArabian.h"
#include "yaArabianScript.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaHeadScript.h"
namespace ya
{
	MapScript::MapScript()
		: Script()

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
		// Arabian Object

		if (GetOwner()->GetName() == L"NewMonster")
		{
			{
				Arabian* arabianObj = new Arabian();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(arabianObj, eLayerType::Monster);
				Transform* arabianTr = arabianObj->GetComponent<Transform>();
				arabianTr->SetPosition(Vector3(10.0f, -3.4f, 5.0f));
				arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
				ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
			}
			{
				Arabian* arabianObj = new Arabian();
				Scene* scene = SceneManager::GetActiveScene();
				scene->AddGameObject(arabianObj, eLayerType::Monster);
				Transform* arabianTr = arabianObj->GetComponent<Transform>();
				arabianTr->SetPosition(Vector3(15.0f, -3.4f, 5.0f));
				arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
				ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
			}
		}

		if (collider->GetOwner()->GetName() == L"Head" && GetOwner()->GetName() == L"MapLeft")
		{
			HeadScript* headScr = collider->GetOwner()->GetScript<HeadScript>();
			headScr->SetStop(-1);
		}

	}
	void MapScript::OnCollisionStay(Collider2D* collider)
	{
		if (collider->GetOwner()->GetName() == L"Head" && GetOwner()->GetName() == L"CollMap")
		{
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
		if (collider->GetOwner()->GetName() == L"Head" && GetOwner()->GetName() == L"MapLeft")
		{
			HeadScript* headScr = collider->GetOwner()->GetScript<HeadScript>();
			headScr->SetStop(0);
		}
	}
	void MapScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void MapScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void MapScript::OnTriggerExit(Collider2D* collider)
	{
	}
}