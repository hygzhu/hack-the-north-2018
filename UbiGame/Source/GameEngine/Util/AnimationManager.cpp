#include "AnimationManager.h"


using namespace GameEngine;

AnimationManager* AnimationManager::sm_instance = nullptr;

AnimationManager::AnimationManager()
{

}


AnimationManager::~AnimationManager()
{

}


void AnimationManager::InitStaticGameAnimations()
{
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::PlayerIdle,
			eTexture::Player,
			sf::Vector2i(0, 0),
			20,
			10)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::WalkFront,
			eTexture::Player,
			sf::Vector2i(0, 1),
			4,
			10)
	);
	
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::WalkBack,
			eTexture::Player,
			sf::Vector2i(0, 2),
			4,
			10)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::WalkRight,
			eTexture::Player,
			sf::Vector2i(0, 3),
			4,
			10)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::WalkLeft,
			eTexture::Player,
			sf::Vector2i(0, 4),
			4,
			10)
	);
}


void AnimationManager::ReleaseStaticGameAnimations()
{
	m_animDefinitions.clear();
}


const SAnimationDefinition* AnimationManager::GetAnimDefinition(EAnimationId::type animId) const
{
	for (int a = 0; a < m_animDefinitions.size(); ++a)
	{
		if (m_animDefinitions[a].m_animId == animId)
			return &m_animDefinitions[a];
	}

	return nullptr;
}
