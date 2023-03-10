#include "yaCharacterSelect.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"


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

		if (mTime > 1.0f)
		{
			tr->SetPosition(Vector3(tr->GetPosition().x, pos.y += Time::DeltaTime(), tr->GetPosition().z));
		}

	}

	void CharacterSelect::Render()
	{
	}

}