#include "yaFadeInOutScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaApplication.h"
#include "yaConstantBuffer.h"
#include "yaRenderer.h"
#include "yaTime.h"
#include "yaInput.h"


extern ya::Application application;

namespace ya
{
	FadeInOutScript::FadeInOutScript()
		: Script()
		, mCamera(nullptr)
		, mTime(0.0f)
	{
	}
	FadeInOutScript::~FadeInOutScript()
	{
	}
	void FadeInOutScript::Initalize()
	{
		//mCamera = renderer::cameras[0];
	}
	void FadeInOutScript::Update()
	{
		/*if (mCamera == nullptr)
			return;

		GameObject* gameObj = mCamera->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		Vector3 cameraPos = tr->GetPosition();
		Vector4 position = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);

		float scale = mCamera->GetScale();*/

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		// Constant buffer
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::FadeInOut];
		renderer::FadeInOutCB data;

		if (Input::GetKeyState(eKeyCode::F) == eKeyState::PRESSED)
		{
			mTime += 1.0f * Time::DeltaTime();
			data.onoff = 1;	
		}
		else if(Input::GetKeyState(eKeyCode::F) == eKeyState::UP)
		{
			mTime = 0.0f;
			data.onoff = 0;
		}
			
		data.fadePosition = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
		data.fadeTime = mTime;
		data.fadeResolution = resolution;

		
		cb->Bind(&data);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);
	}
	void FadeInOutScript::FixedUpdate()
	{
	}
	void FadeInOutScript::Render()
	{
	}
}