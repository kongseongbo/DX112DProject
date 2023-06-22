#pragma once

namespace ya::enums
{
	enum class eSceneType
	{
		Tilte,
		CharacterSelect,
		Stage1,
		Stage2,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		FadeIn,
		Map,
		MapLine,
		Particle,
		Effect,
		MiddleBoss,
		MapWall,
		Obj,
		MonsterAttack,
		Monster,
		Bullet,
		Body,
		Player,
		Bomb,
		MachineGunItem,
		Animator,
		Collider,

		Delete,
		UI,
		End = 26,
	};

	enum class eComponentType
	{
		None,
		Transform, 
		Camera,
		Mesh,
		Collider,
		//Collider2,
		MeshRenerer,
		SpriteRenderer,
		Animator,
		Rigidbody,
		ParticleSystem,
		AudioListener,
		AudioSource,
		Light,
		UI,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		/*Font,*/
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		AudioClip,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,
		Rect,
		Line,
		Circle,
		Box,
		Sphere,
		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	enum class eGunState
	{
		GUN,
		MACHINEGUN,
	};
}