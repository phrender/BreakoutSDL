#include "stdafx.h"
#include "Entity.h"

Entity::Entity(SDL_Renderer* pRenderer)
{
	m_pxRenderer = pRenderer;

	m_fPositionX = 0.0f;
	m_fPositionY = 0.0f;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
};

Entity::~Entity()
{
	if (m_pxRenderer)
	{
		SDL_DestroyRenderer(m_pxRenderer);
		m_pxRenderer = nullptr;
	};
};

void Entity::Update(float fDeltaTime)
{
};

void Entity::Render(float fDeltaTime)
{
};

bool Entity::Collides(Entity* pOtherEntity)
{
	if (m_fPositionX + m_fWidth > pOtherEntity->m_fPositionX &&
		m_fPositionX < pOtherEntity->m_fPositionX + pOtherEntity->m_fWidth &&
		m_fPositionY + m_fHeight > pOtherEntity->m_fPositionY &&
		m_fPositionY < pOtherEntity->m_fPositionY + pOtherEntity->m_fHeight)
	{
		return true;
	};

	return false;
};

float Entity::GetWidth()
{
	return m_fWidth;
};

float Entity::GetHeight()
{
	return m_fHeight;
};

float Entity::GetPositionX()
{
	return m_fPositionX;
};

float Entity::GetPositionY()
{
	return m_fPositionY;
};

void Entity::SetWidth(float fNewWidth)
{
	m_fWidth = fNewWidth;
};

void Entity::SetHeight(float fNewHeight)
{
	m_fHeight = fNewHeight;
};

void Entity::SetPositionX(float fNewPositionX)
{
	m_fPositionX = fNewPositionX;
};

void Entity::SetPositionY(float fNewPositionY)
{
	m_fPositionY = fNewPositionY;
};
