#include "yaCamera.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaApplication.h"

extern ya::Application application;

namespace ya
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Perspective)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mScale(1.0f)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::Initalize()
	{
	}

	void Camera::Update()
	{
	}

	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();
	}

	void Camera::Render()
	{
	}

	void Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		// Crate Translate view matrix
		View = Matrix::Identity;
		View += Matrix::CreateTranslation(-pos);

		// 회전 정보
		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 foward = tr->Foward();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = foward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = foward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = foward.z;

		View += viewRotate;
	}

	void Camera::CreateProjectionMatrix()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{
			Projection = Matrix::CreatePerspectiveFieldOfViewLH
			(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
		}
		else
		{
			Projection = Matrix::CreateOrthographicLH(width / 100.0f, height / 100.0f, mNear, mFar);
		}
	}

}