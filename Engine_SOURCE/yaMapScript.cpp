#include "yaMapScript.h"
#include "yaGameObject.h"
#include "yaArabian.h"
#include "yaArabianScript.h"
#include "yaObject.h"


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
		for (size_t i = 0; i < 3; i++)
		{
			Arabian* arabianObj = new Arabian();
			if (i ==0)
				arabianObj->SetName(L"Arabian1");
			if (i == 1)
				arabianObj->SetName(L"Arabian2");
			if (i == 2)
				arabianObj->SetName(L"Arabian3");
			Scene* scene = SceneManager::GetActiveScene();
			scene->AddGameObject(arabianObj, eLayerType::Monster);
			arabianTr[i] = arabianObj->GetComponent<Transform>();
			arabianTr[i]->SetPosition(Vector3(10.0f + i, - 3.4f, 5.0f));
			arabianTr[i]->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
			ArabianScript* script = arabianObj->AddComponent<ArabianScript>();
			script->SetIndex(i);
		}
	}
	void MapScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MapScript::OnCollisionExit(Collider2D* collider)
	{
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