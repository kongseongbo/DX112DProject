#include "yaMachineGunScript.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaSpriteRenderer.h"
#include "yaMesh.h"
#include "yaObject.h"
#include "yaHeadScript.h"
#include "yaInput.h"


#include "yaAudioListener.h"
#include "yaAudioClip.h"
#include "yaFmod.h"
#include "yaAudioSource.h"


namespace ya
{
	MachineGunScript::MachineGunScript()
		:Script()
	{
	}
	MachineGunScript::~MachineGunScript()
	{
	}
	void MachineGunScript::Initalize()
	{
		//GetOwner()->AddComponent<AudioListener>();
		AudioSource* aaa = GetOwner()->AddComponent<AudioSource>();

		std::shared_ptr<AudioClip> myAudioClip = Resources::Load<AudioClip>(L"machinegun", L"Sound\\machinegun.mp3");
		aaa->SetClip(myAudioClip);
		aaa->SetLoop(false);
	}
	void MachineGunScript::Update()
	{
	}
	void MachineGunScript::FixedUpdate()
	{
	}
	void MachineGunScript::Render()
	{
	}
	void MachineGunScript::OnCollisionEnter(Collider2D* collider)
	{
		if (collider->GetOwner()->GetName() == L"Head")
		{
			AudioSource* aaa = GetOwner()->GetComponent<AudioSource>();
			aaa->Play();

			HeadScript* scr = collider->GetOwner()->GetScript<HeadScript>();
			scr->SetGunState(eGunState::MACHINEGUN);
			GetOwner()->Death();
		}

	}
	void MachineGunScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void MachineGunScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void MachineGunScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void MachineGunScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void MachineGunScript::OnTriggerExit(Collider2D* collider)
	{
	}
}