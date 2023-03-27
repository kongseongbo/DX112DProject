#include "yaBody.h"
#include "yaResources.h"

namespace ya
{
	Body::Body()
	{
	}

	Body::~Body()
	{

	}

	void Body::Initalize()
	{ 
		GameObject::Initalize();
	}

	void Body::Update()
	{
		GameObject::Update();
	}

	void Body::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Body::Render()
	{
		GameObject::Render();
	}

}
