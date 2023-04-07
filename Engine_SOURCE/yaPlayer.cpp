#include "yaPlayer.h"
#include "yaResources.h"


namespace ya
{
	Player::Player()
		//: mGuntype(eGunState::GUN)
	{
	}

	Player::~Player()
	{

	}

	void Player::Initalize()
	{
		GameObject::Initalize();
	}

	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

}
