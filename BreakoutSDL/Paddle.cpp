#include "stdafx.h"
#include "Paddle.h"


Paddle::Paddle(SDL_Renderer* pRenderer) : Entity(pRenderer)
{
	SDL_Surface* pSurface = IMG_Load("Data\\Images\\Paddle.png");
	m_pxPaddleTexture = SDL_CreateTextureFromSurface(m_pxRenderer, pSurface);
	SDL_FreeSurface(pSurface);

	m_fWidth = 128.0f;
	m_fHeight = 32.0f;
	m_fPositionY = 560.0f;
};

Paddle::~Paddle()
{
	SDL_DestroyTexture(m_pxPaddleTexture);
};

void Paddle::Update(float fDeltaTime)
{
};

void Paddle::Render(float fDeltaTime)
{
	SDL_Rect destRect;
	destRect.x = (int)(m_fPositionX + 0.5f);
	destRect.y = (int)(m_fPositionY + 0.5f);
	destRect.w = (int)m_fWidth;
	destRect.h = (int)m_fHeight;

	SDL_RenderCopy(m_pxRenderer, m_pxPaddleTexture, nullptr, &destRect);
};
