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
		, OnOff(false)
	{
	}
	FadeInOutScript::~FadeInOutScript()
	{
	}
	void FadeInOutScript::Initalize()
	{
	
	}
	void FadeInOutScript::Update()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		// Constant buffer
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::FadeInOut];
		renderer::FadeInOutCB data;

		

		

		if (Input::GetKeyState(eKeyCode::F) == eKeyState::DOWN)
		{
			if (OnOff)
			{
				OnOff = false;
				mTime = 0.0f;
			}
			else
				OnOff = true;
		}
		
		if (OnOff)
		{
			mTime += 1.0f * Time::DeltaTime();
			data.onoff = 1;
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