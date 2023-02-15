#pragma once
#include "yaComponent.h"

namespace ya
{
	using namespace math;
	class Camera : public Component
	{
	public :
		enum eProjectionType
		{
			Perspective,
			Orthographic,
		};

		__forceinline static Matrix& GetViewMatrix() { return View; }
		__forceinline static Matrix& GetProjectionMatrix() { return Projection; }

		Camera();
		virtual ~Camera();

		virtual void Initalize()  override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix();

	private :
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;

		float mNear;
		float mFar;
		float mScale;
	};

}