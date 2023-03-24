#include "MapPixelObject.h"
#include "yaResources.h"
#include "yaPlayer.h"
#include "yaRigidbody.h"
#include "yaInput.h"
#include "yaCamera.h"
#include "yaTime.h"

namespace ya
{
	MapPixelObject::MapPixelObject()
		: mbDebug(false)
		, mGroundOX(false)
	{
		SetName(L"Bg");
	}

	MapPixelObject::~MapPixelObject()
	{

	}

	void MapPixelObject::Initalize()
	{
	}

	void MapPixelObject::Update()
	{
		GameObject::Update();

		//if (mPlayer == nullptr)
		//	return;

		//Transform* tr = mPlayer->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();

		//Pixel pixel = mPixelImage->GetPixelImage(pos.x, pos.y + 110.0f);
		///*Pixel pixelRight = mPixelImage->GetPixelImage(pos.x + 20, pos.y + 50.0f);
		//Pixel pixelLeft = mPixelImage->GetPixelImage(pos.x - 20, pos.y + 50.0f);*/

		//// ¹Ù´Ú
		//if (pixel.R == 255 && pixel.G == 0 && pixel.B == 255)
		//{
		//	if (mGroundOX == false)
		//	{
		//		mPlayer->GetComponent<Rigidbody>()->SetGravity(Vector2(0.0f, 0.01f));
		//		mPlayer->GetComponent<Rigidbody>()->SetGround(true);
		//		mGroundOX = true;
		//	}
		//}
		//else if (!(pixel.R == 255 && pixel.G == 0 && pixel.B == 255))
		//{
		//	mGroundOX = false;
		//	mPlayer->GetComponent<Rigidbody>()->SetGravity(Vector2(0.0f, 110.0f));
		//	mPlayer->GetComponent<Rigidbody>()->SetGround(false);
		//}

		//// ¿À¸¥ÂÊ º®
		//if (pixelRight.R == 255 && pixelRight.G == 0 && pixelRight.B == 255)
		//{
		//	mPlayer->SetMoveRight(false);
		//	mPlayer->GetComponent<Rigidbody>()->SetGround(true);
		//}
		//else
		//{
		//	mPlayer->SetMoveRight(true);
		//}
		//// ¿ÞÂÊ º®
		//if (pixelLeft.R == 255 && pixelLeft.G == 0 && pixelLeft.B == 255)
		//{
		//	mPlayer->SetMoveLeft(false);
		//	mPlayer->GetComponent<Rigidbody>()->SetGround(true);
		//}
		//else
		//{
		//	mPlayer->SetMoveLeft(true);
		//}

		if (Input::GetKeyDown(eKeyCode::P))
		{
			if (mbDebug)
				mbDebug = false;
			else
				mbDebug = true;
		}
	}

	void MapPixelObject::FixedUpdate()
	{
	}

	void MapPixelObject::Render()
	{

		GameObject::Render();
	}
}