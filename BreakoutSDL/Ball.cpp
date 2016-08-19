#include "stdafx.h"
#include "Ball.h"


Ball::Ball(SDL_Renderer* pRenderer) : Entity(pRenderer)
{
	SDL_Surface* pSurface = IMG_Load("Data\\Images\\ball.png");
	m_pxBallTexture = SDL_CreateTextureFromSurface(m_pxRenderer, pSurface);
	SDL_FreeSurface(pSurface);

	m_fPositionX = 0.0f;
	m_fPositionY = 0.0f;
	m_fWidth = 24.0f;
	m_fHeight = 24.0f;

	SetDirection(1.0f, 1.0f);
};

Ball::~Ball()
{
	SDL_DestroyTexture(m_pxBallTexture);
};

void Ball::Update(float fDeltaTime)
{
	m_fPositionX += m_fDirectionX * fDeltaTime;
	m_fPositionY += m_fDirectionY * fDeltaTime;
};

void Ball::Render(float fDeltaTime)
{
	SDL_Rect destRect;
	destRect.x = (int)(m_fPositionX + 0.5f);
	destRect.y = (int)(m_fPositionY + 0.5f);
	destRect.w = m_fWidth;
	destRect.h = m_fHeight;

	SDL_RenderCopy(m_pxRenderer, m_pxBallTexture, nullptr, &destRect);
};

void Ball::SetDirection(float fDirectionX, float fDirectionY)
{
	float fLength = sqrt((fDirectionX * fDirectionX) + (fDirectionY * fDirectionY));
	m_fDirectionX = g_fkBallSpeed * (fDirectionX / fLength);
	m_fDirectionY = g_fkBallSpeed * (fDirectionY / fLength);
}
