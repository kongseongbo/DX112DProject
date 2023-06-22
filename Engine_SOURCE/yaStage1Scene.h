#pragma once
#include "yaScene.h"
#include "yaMapScript.h"

#include "yaPlayer.h"
#include "yaBody.h"

#include "yaMosqueArtilleryeHeadLeftScript.h"
#include "yaMosqueArtilleryeHeadCenterScript.h"
#include "yaMosqueArtilleryeHeadRightScript.h"


namespace ya
{

	class Stage1Scene : public Scene
	{
	public:
		Stage1Scene();
		virtual ~Stage1Scene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		
	private:
		GameObject* mCameraObj;
		GameObject* wallObj;
		Player* headObj;
		Body* bodyObj;
		MapScript* mapScript;

		Transform* mMosqueArtilleryleftTr;
		Transform* mMosqueArtilleryrightTr;
		Transform* mMosqueArtillerycenterTr;

		GameObject* mosqueArtilleryLeftObj;
		GameObject* mosqueArtilleryCenterObj;
		GameObject* mosqueArtilleryRightObj;


		MosqueArtilleryeHeadLeftScript* mMosqueArtilleryeHeadLeftScript;
		MosqueArtilleryeHeadCenterScript* mMosqueArtilleryeHeadCenterScript;
		MosqueArtilleryeHeadRightScript* mMosqueArtilleryeHeadRightScript;

		float mTime;
		float mZoom;

		bool mbAudioPlay;
	};
}