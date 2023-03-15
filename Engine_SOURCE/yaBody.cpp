#include "yaBody.h"
#include "yaComponent.h"
#include "yaTransform.h"
#include "yaResources.h"

namespace ya
{
    Body::Body()
        : Component(eComponentType::Body)
        , mAnimator(nullptr)
       
    {
       
    }

    Body::~Body()
    {
    }

    void Body::Initalize()
    {
        mAnimator = GetOwner()->GetComponent<Animator>();
        std::shared_ptr<Texture> bodyTexture = Resources::Load<Texture>(L"Zelda1", L"Character\\Marco\\IdleD.png");
        mAnimator->Create(L"BodyIdle", bodyTexture, Vector2(0.0f, 0.0f), Vector2(33.0f, 36.0f), Vector2::Zero, 1, 0.3f);
        mAnimator->Play(L"BodyIdle", true);
       
    }

    void Body::Update()
    {
        
    }

    void Body::FixedUpdate()
    {
    }

    void Body::Render()
    {
    }

}