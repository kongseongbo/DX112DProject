#include "yaStage1Scene.h"
#include "yaGridScript.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaSpriteRenderer.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaObject.h"
#include "yaCollider2D.h"
#include "yaCollisionManager.h"
#include "yaRigidbody.h"
#include "yaPaintShader.h"

#include "yaMapScript.h"
#include "yaMapWallScript.h"

#include "yaPlayerScript.h"
#include "yaHeadScript.h"
#include "yaBodyScript.h"
#include "yaMachineGunScript.h"
#include "yaMachineGun.h"

#include "yaLight.h"
#include "yaParticleSystem.h"
#include "yaParachute.h"
#include "yaParachuteScript.h"


#include "yaMonster.h"
#include "yaArabian.h"
#include "yaArabianScript.h"
#include "yaHelicopter.h"
#include "yaHelicopterScript.h"
#include "yaMosqueArtilleryScript.h"
#include "yaMosqueArtilleryeHeadCenter.h"
#include "yaCamelArabianScript.h"
#include "yaCamelArabian.h"
#include "yaTheKeesi.h"
#include "yaEngineEffectScript.h"
#include "yaCompleteScript.h"

#include "yaFadeInOutScript.h"

namespace ya
{
	Stage1Scene::Stage1Scene()
		: Scene(eSceneType::Stage1)
		, mCameraObj(nullptr)
		, wallObj(nullptr)
		, headObj(nullptr)
		, bodyObj(nullptr)
		, mapScript(nullptr)
		, mMosqueArtilleryleftTr(nullptr)
		, mMosqueArtilleryrightTr(nullptr)
		, mMosqueArtillerycenterTr(nullptr)
		, mosqueArtilleryLeftObj(nullptr)
		, mosqueArtilleryCenterObj(nullptr)
		, mosqueArtilleryRightObj(nullptr)
		, mMosqueArtilleryeHeadLeftScript(nullptr)
		, mMosqueArtilleryeHeadCenterScript(nullptr)
		, mMosqueArtilleryeHeadRightScript(nullptr)
		, mThekeesiScript(nullptr)
		, mTime(0.0f)
		, mZoom(50.0f)
		//, mbCameraPos(false)
	{
	}

	Stage1Scene::~Stage1Scene()
	{
	}

	void Stage1Scene::Initalize()
	{
		//paint shader
		std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//L"SmileTexture"
		std::shared_ptr<Texture> paintTex = Resources::Find<Texture>(L"PaintTexture");
		paintShader->SetTarget(paintTex);
		paintShader->OnExcute();

		// Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Camera, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		{
			/*GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player, this);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(5.0f);
			lightComp->SetDiffuse(Vector4(1.0f, 0.0f, 0.0f, 1.0f));*/
		}
#pragma region CAMERA
		// Main Camera
		
			mCameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			mCameraObj->SetName(L"MainCamera");
			Camera* cameraComp = mCameraObj->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			CameraScript* cameraScript = mCameraObj->AddComponent<CameraScript>();
			mainCamera = cameraComp;
		
		// UI Camera	
		{
			GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
			cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
			cameraUIComp->DisableLayerMasks();
			cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		}
#pragma endregion

#pragma region MAP
		{
			GameObject* mapObj = object::Instantiate<GameObject>(eLayerType::Map, this);
			mapObj->SetName(L"Mission1Map");
			Transform* map1Tr = mapObj->GetComponent<Transform>();
			map1Tr->SetPosition(Vector3(1.0f, 1.0f, 10.0f));
			map1Tr->SetScale(Vector3(180.0f, 18.0f, 1.0f));

			SpriteRenderer* mapMr = mapObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> mapMaterial = Resources::Find<Material>(L"MapMaterial");
			mapMr->SetMaterial(mapMaterial);
			mapMr->SetMesh(mesh);
		}
#pragma endregion
#pragma region MAP GROUND COLLIDER
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::MapLine, this);
			mapcolliderObj->SetName(L"CollMap");
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(-83.0f, -4.1f, 1.0f));
			mapcolliderTr->SetRotation(Vector3(0.0f,0.0f, 10.0f));
			mapcolliderTr->SetScale(Vector3(10.0f, 1.0f, 1.0f));
			//MapScript* mapScript = mapcolliderObj->AddComponent<MapScript>();
			
			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Line);
			mapCollider->SetCenter(Vector2(0.0f, 0.0f));
			//mapCollider->SetSize(Vector2(5.f, 0.1f));
		}
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::MapLine, this);
			mapcolliderObj->SetName(L"CollMap");
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(-74.f, -4.1f, 1.0f));
			mapcolliderTr->SetRotation(Vector3(0.0f, 0.0f, -10.0f));
			mapcolliderTr->SetScale(Vector3(10.0f, 1.0f, 1.0f));
			//MapScript* mapScript = mapcolliderObj->AddComponent<MapScript>();

			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Line);
			mapCollider->SetCenter(Vector2(0.0f, 0.0f));
			//mapCollider->SetSize(Vector2(5.f, 0.1f));
		}
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::MapLine, this);
			mapcolliderObj->SetName(L"CollMap");
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(-64.f, -4.5f, 1.0f));
			mapcolliderTr->SetRotation(Vector3(0.0f, 0.0f, 5.0f));
			mapcolliderTr->SetScale(Vector3(10.0f, 1.0f, 1.0f));
			//MapScript* mapScript = mapcolliderObj->AddComponent<MapScript>();

			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Line);
			mapCollider->SetCenter(Vector2(0.0f, 0.0f));
			//mapCollider->SetSize(Vector2(5.f, 0.1f));
		}
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::MapLine, this);
			mapcolliderObj->SetName(L"CollMap");
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(-54.f, -5.0f, 1.0f));
			mapcolliderTr->SetRotation(Vector3(0.0f, 0.0f, -11.0f));
			mapcolliderTr->SetScale(Vector3(10.0f, 1.0f, 1.0f));
			//MapScript* mapScript = mapcolliderObj->AddComponent<MapScript>();

			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Line);
			mapCollider->SetCenter(Vector2(0.0f, 0.0f));
			//mapCollider->SetSize(Vector2(5.f, 0.1f));
		}
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::Map, this);
			mapcolliderObj->SetName(L"RectCollMap");
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(55.0f, -5.8f, 1.0f));
			mapcolliderTr->SetScale(Vector3(250.0f, 1.5f, 1.0f));
			//MapScript* mapScript = mapcolliderObj->AddComponent<MapScript>();

			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
			mapCollider->SetCenter(Vector2(0.0f, -0.0f));
			//mapCollider->SetSize(Vector2(5.f, 0.1f));
		}
#pragma endregion

#pragma region PLAYER
		{

			headObj = object::Instantiate<Player>(eLayerType::Player, this);
			headObj->SetName(L"Head");
			Transform* headTr = headObj->GetComponent<Transform>();
			//headTr->SetPosition(Vector3(-75.0f, 3.0f, 5.0f));
			headTr->SetPosition(Vector3(3.0f, 3.0f, 5.0f)); //47
			headTr->SetScale(Vector3(15.0f, 15.0f, 1.0f));
			headObj->AddComponent<Animator>();
			Rigidbody* playerGirigid = headObj->AddComponent<Rigidbody>();
			playerGirigid->SetGravity(Vector2(0.0f, 102.0f));
			HeadScript* playerscript = headObj->AddComponent<HeadScript>();

			Collider2D* collider = headObj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.1f, 0.2f));

			SpriteRenderer* headMr = headObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> headMateiral = Resources::Find<Material>(L"SpriteMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			headMr->SetMaterial(headMateiral);
			headMr->SetMesh(mesh);
			object::DontDestroyOnLoad(headObj);
		
		//Player Body

			bodyObj = object::Instantiate<Body>(eLayerType::Body, this);
			bodyObj->SetName(L"Body");
			Transform* bodyTr = bodyObj->GetComponent<Transform>();
			bodyTr->SetPosition(Vector3(headTr->GetPosition().x, headTr->GetPosition().y - 1.f, 5.0f));
			bodyTr->SetScale(Vector3(15.0f, 15.0f, 1.0f));
			bodyObj->AddComponent<Animator>();
			BodyScript* bodyScript = bodyObj->AddComponent<BodyScript>();
			bodyScript->mHead = headObj;

			Collider2D* bodyCollider = bodyObj->AddComponent<Collider2D>();
			bodyCollider->SetType(eColliderType::Rect);
			bodyCollider->SetSize(Vector2(0.1f, 0.07f));

			SpriteRenderer* bodyMr = bodyObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> bodyMateiral = Resources::Find<Material>(L"SpriteMaterial");
			bodyMr->SetMaterial(bodyMateiral);
			bodyMr->SetMesh(mesh);
			object::DontDestroyOnLoad(bodyObj);

			playerscript->SetBody(bodyObj);

		//parachute
			Parachute* parachute = object::Instantiate<Parachute>(eLayerType::Bullet, this);
			parachute->SetName(L"parachute");
			Transform* parachuteTr = parachute->GetComponent<Transform>();
			parachuteTr->SetPosition(Vector3(headTr->GetPosition().x , headTr->GetPosition().y, headTr->GetPosition().z));
			parachuteTr->SetScale(Vector3(10.0f, 10.0f, 1.0f)); 
			parachuteTr->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
			ParachuteScript* script = parachute->AddComponent<ParachuteScript>();
			script->SetPlayer(headObj);
		}
#pragma endregion

#pragma region 1에서 1.2 넘어가는 벽오브젝트
		{
			wallObj = object::Instantiate<GameObject>(eLayerType::Obj, this);
			wallObj->SetName(L"Wall");
			Transform* tr = wallObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(88.0f, -2.0f, 9.0f));
			tr->SetScale(Vector3(13.0f, 13.0f, 1.0f));
			MapWallScript* scr = wallObj->AddComponent<MapWallScript>();
			scr->SetPlayerObj(headObj);

			Collider2D* coll = wallObj->AddComponent<Collider2D>();
			coll->SetType(eColliderType::Rect);
			coll->SetSize(Vector2(0.2f, 0.2f));

			SpriteRenderer* mr = wallObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			mr->SetMaterial(material);
			mr->SetMesh(mesh);
		}
#pragma endregion

#pragma region Map Collider
		// 캐릭터 이동시 같이 따라가는 coll
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::MapWall, this);
			mapcolliderObj->SetName(L"CollMap");
			Transform* headTr = headObj->GetComponent<Transform>();
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(headTr->GetPosition().x, headTr->GetPosition().y - 2.5f, headTr->GetPosition().z));
			mapcolliderTr->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
			mapcolliderTr->SetScale(Vector3(1.0f, 10.0f, 1.0f));
			mapScript = mapcolliderObj->AddComponent<MapScript>();
			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		// 맵왼쪽끝 벽
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::MapWall, this);
			mapcolliderObj->SetName(L"MapLeft");
			Transform* headTr = headObj->GetComponent<Transform>();
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(-89.0f,1.0f,1.0f));
			mapcolliderTr->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
			mapcolliderTr->SetScale(Vector3(1.0f, 10.0f, 1.0f));
			MapScript* mapScript = mapcolliderObj->AddComponent<MapScript>();

			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		// 맵오른쪽끝 벽
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::MapWall, this);
			mapcolliderObj->SetName(L"MapRight");
			Transform* headTr = headObj->GetComponent<Transform>();
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(174.0f, 1.0f, 1.0f));
			mapcolliderTr->SetRotation(Vector3(0.0f, 0.0f, 180.0f));
			mapcolliderTr->SetScale(Vector3(1.0f, 10.0f, 1.0f));
			MapScript* mapScript = mapcolliderObj->AddComponent<MapScript>();

			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
		}
		// Monster 생성 Collider
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::Collider, this);
			mapcolliderObj->SetName(L"NewMonster");
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(-55.0f, 0.0f, 1.0f));
			mapcolliderTr->SetScale(Vector3(0.5f, 20.0f, 1.0f));
			MapScript* mapScript = mapcolliderObj->AddComponent<MapScript>();

			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
			mapCollider->SetCenter(Vector2(0.0f, 0.0f));
			//mapCollider->SetSize(Vector2(1.f, 1.f));
		}
		{
			GameObject* mapcolliderObj = object::Instantiate<GameObject>(eLayerType::Collider, this);
			mapcolliderObj->SetName(L"NewMonster");
			Transform* mapcolliderTr = mapcolliderObj->GetComponent<Transform>();
			mapcolliderTr->SetPosition(Vector3(-40.0f, 0.0f, 1.0f));
			mapcolliderTr->SetScale(Vector3(0.5f, 20.0f, 1.0f));
			MapScript* mapScript = mapcolliderObj->AddComponent<MapScript>();

			Collider2D* mapCollider = mapcolliderObj->AddComponent<Collider2D>();
			mapCollider->SetType(eColliderType::Rect);
			mapCollider->SetCenter(Vector2(0.0f, 0.0f));
			//mapCollider->SetSize(Vector2(1.f, 1.f));
		}
#pragma endregion

#pragma region MosqueArtillery
		// Left
		{
			mosqueArtilleryLeftObj = object::Instantiate<GameObject>(eLayerType::MiddleBoss, this);
			mosqueArtilleryLeftObj->SetName(L"MosqueArtilleryLeft");
			mMosqueArtilleryleftTr = mosqueArtilleryLeftObj->GetComponent<Transform>();
			mMosqueArtilleryleftTr->SetPosition(Vector3(45.4f, 4.f, 9.0f));
			mMosqueArtilleryleftTr->SetScale(Vector3(15.0f, 15.0f, 1.0f));
			mosqueArtilleryLeftObj->AddComponent<Animator>();

			mMosqueArtilleryeHeadLeftScript = mosqueArtilleryLeftObj->AddComponent<MosqueArtilleryeHeadLeftScript>();
			mMosqueArtilleryeHeadLeftScript->SetTarget(headObj);

			SpriteRenderer* sr = mosqueArtilleryLeftObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			sr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMesh(mesh);
		}
		// Center
		{
			mosqueArtilleryCenterObj = object::Instantiate<GameObject>(eLayerType::MiddleBoss, this);
			mosqueArtilleryCenterObj->SetName(L"MosqueArtilleryCenter");
			mMosqueArtillerycenterTr = mosqueArtilleryCenterObj->GetComponent<Transform>();
			mMosqueArtillerycenterTr->SetPosition(Vector3(51.6f, 4.f, 9.0f));
			mMosqueArtillerycenterTr->SetScale(Vector3(15.0f, 15.0f, 1.0f));
			mosqueArtilleryCenterObj->AddComponent<Animator>();

			mMosqueArtilleryeHeadCenterScript = mosqueArtilleryCenterObj->AddComponent<MosqueArtilleryeHeadCenterScript>();
			mMosqueArtilleryeHeadCenterScript->SetTarget(headObj);

			SpriteRenderer* sr = mosqueArtilleryCenterObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			sr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMesh(mesh);
		}
		// Right
		{
			mosqueArtilleryRightObj = object::Instantiate<GameObject>(eLayerType::MiddleBoss, this);
			mosqueArtilleryRightObj->SetName(L"MosqueArtilleryRight");
			mMosqueArtilleryrightTr = mosqueArtilleryRightObj->GetComponent<Transform>();
			mMosqueArtilleryrightTr->SetPosition(Vector3(57.8f, 4.f, 9.0f));
			mMosqueArtilleryrightTr->SetScale(Vector3(15.0f, 15.0f, 1.0f));
			mosqueArtilleryRightObj->AddComponent<Animator>();

			mMosqueArtilleryeHeadRightScript = mosqueArtilleryRightObj->AddComponent<MosqueArtilleryeHeadRightScript>();
			mMosqueArtilleryeHeadRightScript->SetTarget(headObj);

			SpriteRenderer* sr = mosqueArtilleryRightObj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"SpriteMaterial");
			sr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMesh(mesh);
		}
		// Base
		GameObject* mosqueArtilleryObj = object::Instantiate<GameObject>(eLayerType::MiddleBoss, this);
		mosqueArtilleryObj->SetName(L"MosqueArtilleryBase");
		Transform* baseTr = mosqueArtilleryObj->GetComponent<Transform>();
		baseTr->SetPosition(Vector3(49.0f, -0.5f, 10.0f));
		baseTr->SetScale(Vector3(25.0f, 8.5f, 1.0f));
		mosqueArtilleryObj->AddComponent<MosqueArtilleryScript>();
#pragma endregion
		
#pragma region HELICOPTER
		{
			Helicopter* heliObj = object::Instantiate<Helicopter>(eLayerType::Monster, this);
			heliObj->SetName(L"Helicopter");
			Transform* heliTr = heliObj->GetComponent<Transform>();
			heliTr->SetPosition(Vector3(3.0f, 5.0f, 5.0f));
			heliTr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			HelicopterScript* scr = heliObj->AddComponent<HelicopterScript>();
			scr->SetPlayer(headObj);
		}
#pragma endregion

#pragma region CAMELARABIAN
		{
			CamelArabian* camelArabian = object::Instantiate<CamelArabian>(eLayerType::Monster, this);
			camelArabian->SetName(L"CamelArabian");
			Transform* tr = camelArabian->GetComponent<Transform>();
			tr->SetPosition(Vector3(-15.0f, -2.0f, 5.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));
			camelArabian->AddComponent<Animator>();
			camelArabian->AddComponent<Collider2D>();
			camelArabian->AddComponent<CamelArabianScript>();

			SpriteRenderer* sr = camelArabian->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> matateiral = Resources::Find<Material>(L"SpriteMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMaterial(matateiral);
			sr->SetMesh(mesh);
		}
#pragma endregion

#pragma region THEKEESI
		{
			TheKeesi* thekeesi = object::Instantiate<TheKeesi>(eLayerType::Monster, this);
			thekeesi->SetName(L"TheKeesi");
			Transform* tr = thekeesi->GetComponent<Transform>();
			tr->SetPosition(Vector3(164.0f, 4.0f, 5.0f));
			tr->SetScale(Vector3(15.0f, 15.0f, 1.0f));

			mThekeesiScript = thekeesi->AddComponent<TheKeesiScript>();
			mThekeesiScript->SetPlayer(headObj);
			mThekeesiScript->SetCameraScript(cameraScript);
			SpriteRenderer* sr = thekeesi->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> matateiral = Resources::Find<Material>(L"SpriteMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			sr->SetMaterial(matateiral);
			sr->SetMesh(mesh);

			GameObject* leftgroundeffect = object::Instantiate<GameObject>(eLayerType::Animator, this);
			//
			GameObject* lefteffect = object::Instantiate<GameObject>(eLayerType::Monster, this);
			lefteffect->SetName(L"leftengineeffect");
			Transform* leftTr = lefteffect->GetComponent<Transform>();
			leftTr->SetScale(Vector3(10.0f, 10.0f, 4.9f));

			EngineEffectScript* lefteffectScript = lefteffect->AddComponent<EngineEffectScript>();
			lefteffectScript->SetParent(tr);
			lefteffectScript->SetLeftGroundEffect(leftgroundeffect);

			SpriteRenderer* leftSr = lefteffect->AddComponent<SpriteRenderer>();
			leftSr->SetMaterial(matateiral);
			leftSr->SetMesh(mesh);

			
			GameObject* rightgroundeffect = object::Instantiate<GameObject>(eLayerType::Animator, this);
			//
			GameObject* righteffect = object::Instantiate<GameObject>(eLayerType::Monster, this);
			righteffect->SetName(L"rightengineeffect");

			Transform* rightTr = righteffect->GetComponent<Transform>();
			rightTr->SetScale(Vector3(10.0f, 10.0f, 4.9f));
			rightTr->SetRotation(Vector3(1.0f, 180.0f, 1.0f));

			EngineEffectScript* righteffectScript = righteffect->AddComponent<EngineEffectScript>();
			righteffectScript->SetParent(tr);
			righteffectScript->SetRightGroundEffect(rightgroundeffect);

			SpriteRenderer* rightSr = righteffect->AddComponent<SpriteRenderer>();
			rightSr->SetMaterial(matateiral);
			rightSr->SetMesh(mesh);

			mThekeesiScript->SetLeftEffect(lefteffectScript);
			mThekeesiScript->SetRightEffect(righteffectScript);
		}
#pragma endregion

		MissionComplete();
		
		// MachineGunItem
		{
			MachineGun* machineGun = object::Instantiate<MachineGun>(eLayerType::MachineGunItem, this);
			machineGun->SetName(L"machineGun");
			Transform* machineGunTr = machineGun->GetComponent<Transform>();
			machineGunTr->SetPosition(Vector3(5.0f, -2.0f, 2.0f));
			machineGunTr->SetScale(Vector3(10.0f, 10.0f, 1.0f));
			MachineGunScript* machineGunScript = machineGun->AddComponent<MachineGunScript>();

			Collider2D* machineGunCollider = machineGun->AddComponent<Collider2D>();
			machineGunCollider->SetType(eColliderType::Rect);
			machineGunCollider->SetSize(Vector2(0.1f, 0.1f));

			Animator* machineGunAni = machineGun->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"MachineGunItem", L"Bullet\\MachineGunItem.png");
			machineGunAni->Create(L"MachineGunItem", texture, Vector2(0.0f, 0.0f), Vector2(24.0f, 22.0f), Vector2::Zero, 2, 0.3f);

			SpriteRenderer* machineGunSr = machineGun->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> machineGunMateiral = Resources::Find<Material>(L"SpriteMaterial");
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			machineGunSr->SetMaterial(machineGunMateiral);
			machineGunSr->SetMesh(mesh);
			machineGunAni->Play(L"MachineGunItem", true);
		}


		//// HPBAR
		//GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::UI, this);
		//hpBar->SetName(L"HPBAR");
		//Transform* hpBarTR = hpBar->GetComponent<Transform>();
		//hpBarTR->SetPosition(Vector3(-5.0f, 3.0f, 6.0f));
		//hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		//SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
		//std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		//std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
		//hpsr->SetMesh(hpmesh);
		//hpsr->SetMaterial(hpspriteMaterial);

		//// FadeInOut
		//GameObject* fadeObject = object::Instantiate<GameObject>(eLayerType::FadeIn, this);
		//Transform* fadeTr = fadeObject->GetComponent<Transform>();
		//fadeTr->SetPosition(Vector3(0.0f, 0.0f, 2.0f));
		//SpriteRenderer* fadeMr = fadeObject->AddComponent<SpriteRenderer>();
		//fadeMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));
		//fadeObject->AddComponent<FadeInOutScript>();

		////Particle
		//{
		//	GameObject* obj = object::Instantiate<GameObject>(eLayerType::Particle);
		//	obj->SetName(L"PARTICLE");
		//	Transform* tr = obj->GetComponent<Transform>();
		//	tr->SetPosition(Vector3(0.0f, 0.0f, 100.0f));
		//	obj->AddComponent<ParticleSystem>();
		//}

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Map, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MapLine, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MachineGunItem, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Collider, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MonsterAttack, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MapWall, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Bomb, eLayerType::Map, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bomb, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bomb, eLayerType::MiddleBoss, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bomb, eLayerType::Obj, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Body, eLayerType::Map, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Body, eLayerType::MapLine, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Body, eLayerType::MonsterAttack, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::MonsterAttack, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::MiddleBoss, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Bullet, eLayerType::Obj, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Map, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::MapLine, true);

		CollisionManager::CollisionLayerCheck(eLayerType::Obj, eLayerType::Map, true);

		CollisionManager::CollisionLayerCheck(eLayerType::MonsterAttack, eLayerType::Map, true);
		CollisionManager::CollisionLayerCheck(eLayerType::MonsterAttack, eLayerType::MapLine, true);


		Scene::Initalize();
	}

	void Stage1Scene::Update()
	{
		CameraScript* cameraScript = mCameraObj->GetComponent<CameraScript>();
		Transform* cameraTr = mCameraObj->GetComponent<Transform>();
		Camera* camera = mCameraObj->GetComponent<Camera>();
		Vector3 pos = {};
		
		if (headObj->GetState() == GameObject::Active)
		{
			Transform* headTr = headObj->GetComponent<Transform>();
			Vector3 headPos = headTr->GetPosition();

			if (mapScript->GetPlayerCamera())
				pos = headPos;
			else
				pos = cameraTr->GetPosition();

			if (cameraTr->GetPosition().x < -78.0f)
			{
				mapScript->SetPlayerCamera(false);
				cameraTr->SetPosition(Vector3(pos.x, 1.2f , 5.0f));
			}

			
			if (cameraTr->GetPosition().x >= 50.5f)
			{
				if (mosqueArtilleryLeftObj->GetState() == GameObject::Paused && mosqueArtilleryCenterObj->GetState() == GameObject::Paused && mosqueArtilleryRightObj->GetState() == GameObject::Paused)
				{
					mapScript->SetPlayerCamera(true);
					pos = headPos;
					cameraTr->SetPosition(Vector3(pos.x, 1.2f, 5.0f));
					camera->SetRatio(50.0f);
				}
				else
				{
					mZoom -= 5.0f * Time::DeltaTime();
					if (mZoom >= 40.0f)
					{
						camera->SetRatio(mZoom);
						cameraTr->SetPosition(Vector3(cameraTr->GetPosition().x, 1.2f, 5.0f));

						mMosqueArtilleryleftTr->SetPosition(Vector3(mMosqueArtilleryleftTr->GetPosition().x - (0.15f * Time::DeltaTime())
							, mMosqueArtilleryleftTr->GetPosition().y + (0.5f * Time::DeltaTime())
							, mMosqueArtilleryleftTr->GetPosition().z));

						mMosqueArtillerycenterTr->SetPosition(Vector3(mMosqueArtillerycenterTr->GetPosition().x
							, mMosqueArtillerycenterTr->GetPosition().y + (0.5f * Time::DeltaTime())
							, mMosqueArtillerycenterTr->GetPosition().z));

						mMosqueArtilleryrightTr->SetPosition(Vector3(mMosqueArtilleryrightTr->GetPosition().x + (0.15f * Time::DeltaTime())
							, mMosqueArtilleryrightTr->GetPosition().y + (0.5f * Time::DeltaTime())
							, mMosqueArtilleryrightTr->GetPosition().z));
					}
					else
					{
						mMosqueArtilleryeHeadLeftScript->SetStartAni(true);
						mMosqueArtilleryeHeadCenterScript->SetStartAni(true);
						mMosqueArtilleryeHeadRightScript->SetStartAni(true);
					}
				}
			}
			else
			{
				cameraTr->SetPosition(Vector3(pos.x, 1.2f, 5.0f));
			}
		}


		if (headObj->GetState() == GameObject::Paused)
		{
			mTime += 2.0f * Time::DeltaTime();
			if (mTime >= 5.0f)
			{
				headObj->SetState(GameObject::Active);
				bodyObj->SetState(GameObject::Active);
				Transform* headTr = headObj->GetComponent<Transform>();
				Vector3 pos = headTr->GetPosition();
				pos.x -= 5.0f;
				headTr->SetPosition(pos);
				Animator* headAni = headObj->GetComponent<Animator>();
				headAni->Play(L"NewMarco", false);
				HeadScript* headScript = headObj->GetScript<HeadScript>();
				headScript->SetGunState(eGunState::GUN);

				mTime = 0.0f;
			}
		}

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
		}

		Scene::Update();
	}

	void Stage1Scene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void Stage1Scene::Render()
	{
		Scene::Render();
	} 

	void Stage1Scene::OnEnter()
	{

	}

	void Stage1Scene::OnExit()
	{

	}

	void Stage1Scene::MissionComplete()
	{
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"M");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(144.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"I");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(145.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"S");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(146.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"SS");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(147.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"II");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(148.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"O");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(149.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"N");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(150.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"one");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(151.0f, 4.0f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		//
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"C");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(144.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"OO");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(145.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"MM");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(146.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"P");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(147.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"L");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(148.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"E");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(149.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"T");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(150.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"EE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(151.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Effect, this);
			obj->SetName(L"WOW");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(152.0f, 2.5f, 1.0f));
			tr->SetScale(Vector3(12.0f, 12.0f, 1.0f));

			CompleteScript* scr = obj->AddComponent<CompleteScript>();
			scr->SetKeesiScript(mThekeesiScript);
		}
	}
}



/*Animator* animator = obj->AddComponent<Animator>();
std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Zelda", L"Character\\Marco\\IdleU.png");
animator->Create(L"Idle", texture, Vector2(0.0f, 0.0f), Vector2(35.0f, 36.0f), Vector2::Zero, 4, 0.3f);
animator->Create(L"MoveDown", texture, Vector2(0.0f, 520.0f), Vector2(120.0f, 130.0f), Vector2::Zero, 8, 0.1f);
animator->Play(L"HeadIdle", true);*/

//SMILE RECT CHild
/*GameObject* child = object::Instantiate<GameObject>(eLayerType::Player);
child->SetName(L"SMILE");
Transform* childTr = child->GetComponent<Transform>();
childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
childTr->SetParent(tr);

MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");
childMr->SetMaterial(childmateiral);
childMr->SetMesh(mesh);*/