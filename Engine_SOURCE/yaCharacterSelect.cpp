#include "yaCharacterSelect.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSpriteRenderer.h"

namespace ya
{
	CharacterSelect::CharacterSelect()
		: Script()
		, mTime(0.0f)
	{
	}

	CharacterSelect::~CharacterSelect()
	{
	}

	void CharacterSelect::Initalize()
	{
	}

	void CharacterSelect::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mTime += Time::DeltaTime();

		std::shared_ptr<Material> marco1Material = Resources::Find<Material>(L"marco1Material");
		std::shared_ptr<Material> marco2Material = Resources::Find<Material>(L"marco2Material");
		std::shared_ptr<Material> marco3Material = Resources::Find<Material>(L"marco3Material");

		std::shared_ptr<Material> eri1Material = Resources::Find<Material>(L"eri1Material");
		std::shared_ptr<Material> eri2Material = Resources::Find<Material>(L"eri2Material");
		std::shared_ptr<Material> eri3Material = Resources::Find<Material>(L"eri3Material");

		SpriteRenderer* Mr = GetOwner()->GetComponent<SpriteRenderer>();

		if (GetOwner()->GetName() == L"M2Texture")
		{
			if (mTime > 1.0f)
			{
				if (pos.y >= 8.0f)
					tr->SetPosition(Vector3(tr->GetPosition().x, pos.y = 8.0f, tr->GetPosition().z));

				tr->SetPosition(Vector3(tr->GetPosition().x, pos.y += 5.0f * Time::DeltaTime(), tr->GetPosition().z));
			}
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			if (GetOwner()->GetName() == L"Marco")
				Mr->SetMaterial(marco1Material);
			
			if (GetOwner()->GetName() == L"Eri")
				Mr->SetMaterial(eri2Material);
			
			if (tr->GetName() == L"P1Tr")
				tr->SetPosition(Vector3(pos.x = -1.5f, tr->GetPosition().y, tr->GetPosition().z));
		}

		if (Input::GetKey(eKeyCode::LEFT))
		{
			if (GetOwner()->GetName() == L"Marco")
				Mr->SetMaterial(marco2Material);
			
			if (GetOwner()->GetName() == L"Eri")
				Mr->SetMaterial(eri1Material);
			
			if (tr->GetName() == L"P1Tr")
				tr->SetPosition(Vector3(pos.x = -6.0f, tr->GetPosition().y, tr->GetPosition().z));
		}

		if (Input::GetKey(eKeyCode::ENTER))
		{

		}
	}

	void CharacterSelect::Render()
	{
	}
}