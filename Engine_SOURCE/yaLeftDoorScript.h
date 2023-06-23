#pragma once
#include "yaScript.h"

#include "yaMosqueArtilleryeHeadLeftScript.h"
#include "yaMosqueArtilleryeHeadCenterScript.h"
#include "yaMosqueArtilleryeHeadRightScript.h"

#include "yaCameraScript.h"

namespace ya
{
	class LeftDoorScript : public Script
	{
	public:
		LeftDoorScript();
		virtual ~LeftDoorScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) {};
		virtual void OnCollisionStay(Collider2D* collider) {};
		virtual void OnCollisionExit(Collider2D* collider) {};

		virtual void OnTriggerEnter(Collider2D* collider) {};
		virtual void OnTriggerStay(Collider2D* collider) {};
		virtual void OnTriggerExit(Collider2D* collider) {};

		void SetLeft(MosqueArtilleryeHeadLeftScript* scr) { mLeft = scr; }
		void SetCenter(MosqueArtilleryeHeadCenterScript* scr) { mCenter = scr; }
		void SetRight(MosqueArtilleryeHeadRightScript* scr) { mRight = scr; }

		void SetCameraScrit(CameraScript* scr) { mCameraScript = scr; }

		bool GetNext() { return mNext; }

	private:
		Transform* mTr;

		MosqueArtilleryeHeadLeftScript* mLeft;
		MosqueArtilleryeHeadCenterScript* mCenter;
		MosqueArtilleryeHeadRightScript* mRight;

		CameraScript* mCameraScript;

		float mTime;
		bool mNext;
	};
}