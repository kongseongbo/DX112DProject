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
		Arabian* arabianObj = new Arabian();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(arabianObj,eLayerType::Monster);
		arabianObj->SetName(L"Arabian");
		Transform* arabianTr = arabianObj->GetComponent<Transform>();
		arabianTr->SetPosition(Vector3(9.0f, -3.5f, 5.0f));
		arabianTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
		//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		arabianObj->AddComponent<ArabianScript>();
		
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