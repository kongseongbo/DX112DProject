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
		Particle,
		MapLine,
		Bullet,
		MiddleBoss,
		MapWall,
		Obj,
		Effect,
		MonsterAttack,
		Monster,
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