#include "yaCameraScript.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaSceneManager.h"
#include "yaScene.h"
#include "yaCollider2D.h"


namespace ya
{
	CameraScript::CameraScript()
		: Script()
		, weakOn(false)
		, strongOn(false)
		, shaketime(0.0f)
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initalize()
	{
		
	}

	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			pos += 100.0f * tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			pos += 100.0f * -tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos += 100.0f * tr->Foward() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos += 100.0f * -tr->Foward() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			pos += 100.0f * tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			pos += 100.0f * -tr->Up() * Time::DeltaTime();
		}

		if (weakOn)
		{
			pos = weakShake(pos);
		}
		if (strongOn)
		{
			pos = strongShake(pos);
		}


		tr->SetPosition(pos);
	}
	void CameraScript::Render()
	{
	}

	Vector3 CameraScript::CameraWeakShakeeffect(Vector3 pos)
	{
		float shakeAmount = 0.05f; // Change this value to adjust the camera shake intensity
		Vector3 shakeOffset = Vector3(RandomRange(-shakeAmount, shakeAmount), RandomRange(-shakeAmount, shakeAmount), 0.0f);
		return pos += shakeOffset;

	}

	Vector3 CameraScript::CameraStrongShakeeffect(Vector3 pos)
	{
		float shakeAmount = 0.1f; // Change this value to adjust the camera shake intensity
		Vector3 shakeOffset = Vector3(RandomRange(-shakeAmount, shakeAmount), RandomRange(-shakeAmount, shakeAmount), 0.0f);
		return pos += shakeOffset;
	}

	Vector3 CameraScript::weakShake(Vector3 pos)
	{
		shaketime += Time::DeltaTime();
		pos = CameraWeakShakeeffect(pos);

		if (shaketime >= 0.2f)
		{
			weakOn = false;
			shaketime = 0.f;
			return pos;
		}

		return pos;

	}

	Vector3 CameraScript::strongShake(Vector3 pos)
	{
		shaketime += Time::DeltaTime();
		pos = CameraStrongShakeeffect(pos);

		if (shaketime >= 0.5f)//∏Ó√ ∞£ 
		{
			strongOn = false;
			shaketime = 0.f;
			return pos;
		}

		return pos;

	}
}