#include "yaBodyAnimator.h"
#include "yaAnimator.h"


namespace ya
{
	BodyAnimator::BodyAnimator()
		: Component(eComponentType::BodyAnimator)
		, mAnimations{}
		, mEvents{}
		, mActiveAnimation(nullptr)
		, mbLoop(false)
	{

	}
	BodyAnimator::~BodyAnimator()
	{
		for (auto anim : mAnimations)
		{
			delete anim.second;
			anim.second = nullptr;
		}

		for (auto evt : mEvents)
		{
			delete evt.second;
			evt.second = nullptr;
		}
	}
	void BodyAnimator::Initalize()
	{
	}
	void BodyAnimator::Update()
	{
		if (mActiveAnimation == nullptr)
			return;

		Events* events = FindEvents(mActiveAnimation->AnimationName());

		if (mActiveAnimation->IsComplete())
		{
			Events* events
				= FindEvents(mActiveAnimation->AnimationName());

			if (events)
				events->mCompleteEvent();

			if (mbLoop)
				mActiveAnimation->Reset();
		}

		UINT spriteIndex = mActiveAnimation->Update();
		if (spriteIndex != -1 && events->mEvents[spriteIndex].mEvent)
			events->mEvents[spriteIndex].mEvent();

		mActiveAnimation->Update();
	}
	void BodyAnimator::FixedUpdate()
	{
	}
	void BodyAnimator::Render()
	{
	}

	bool BodyAnimator::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
		, Vector2 leftTop, Vector2 size, Vector2 offset
		, UINT spriteLegth, float duration)
	{
		if (atlas == nullptr)
			return false;

		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
			return false;

		animation = new Animation();
		animation->Create(name, atlas, leftTop
			, size, offset
			, spriteLegth, duration);


		mAnimations.insert(std::make_pair(name, animation));

		Events* events = new Events();
		events->mEvents.resize(spriteLegth);
		mEvents.insert(std::make_pair(name, events));
	}

	Animation* BodyAnimator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
		{
			return nullptr;
		}

		return iter->second;
	}
	BodyAnimator::Events* BodyAnimator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
		{
			return nullptr;
		}

		return iter->second;
	}
	void BodyAnimator::Play(const std::wstring& name, bool loop)
	{
		Animation* prevAnimation = mActiveAnimation;
		Events* events = nullptr;

		if (prevAnimation)
			events = FindEvents(prevAnimation->AnimationName());

		if (events)
			events->mEndEvent();

		mActiveAnimation = FindAnimation(name);
		mActiveAnimation->Reset();
		mbLoop = loop;

		events = FindEvents(mActiveAnimation->AnimationName());

		if (events)
			events->mStartEvent();
	}

	void BodyAnimator::Binds()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->BindShader();
	}

	void BodyAnimator::Clear()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Clear();
	}

	std::function<void()>& BodyAnimator::GetStartEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mStartEvent.mEvent;
	}
	std::function<void()>& BodyAnimator::GetCompleteEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mCompleteEvent.mEvent;
	}
	std::function<void()>& BodyAnimator::GetEndEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mEndEvent.mEvent;
	}
	std::function<void()>& BodyAnimator::GetEvent(const std::wstring& name, UINT index)
	{
		Events* events = FindEvents(name);

		return events->mEvents[index].mEvent;
	}
}
