#include "stdafx.h"
#include "GameBoard.h"

GameBoard::GameBoard(SDL_Renderer* pRenderer) : Entity(pRenderer)
{
	SDL_Surface* pSurface = IMG_Load("Data\\Images\\bricks.png");
	m_pxBrickTexture = SDL_CreateTextureFromSurface(m_pxRenderer, pSurface);
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("Data\\Images\\side.png");
	m_pxSideTexture = SDL_CreateTextureFromSurface(m_pxRenderer, pSurface);
	SDL_FreeSurface(pSurface);

	srand(time(0));

	for (int i = 0; i < BoardWidth; i++)
	{
		for (int j = 0; j < BoardHeight; j++)
		{
			m_rgBricks[i][j] = Brick();
		};
	};

	m_fPositionX = 16.0f;
	m_fPositionY = 0.0f;
	m_fWidth = 768.0f;
	m_fHeight = 600.0f;

	m_fBrickOffsetX = 0;
	m_fBrickOffsetY = 16.0f;
};

GameBoard::~GameBoard()
{
	SDL_DestroyTexture(m_pxBrickTexture);
	SDL_DestroyTexture(m_pxSideTexture);
};

void GameBoard::Update(float fDeltaTime)
{
};

void GameBoard::Render(float fDeltaTime)
{
	for (int i = 0; i < BoardWidth; i++)
	{
		for (int j = 0; j < BoardHeight; j++)
		{
			Brick brick = m_rgBricks[i][j];

			if (!brick.m_bBrickState)
			{
				continue;
			};

			SDL_Rect sourceRect;

			sourceRect.x = (brick.m_iBrickType % 2) * BoardBrickWidth;
			sourceRect.y = (brick.m_iBrickType % 2) * BoardBrickHeight;
			sourceRect.w = BoardBrickWidth;
			sourceRect.h = BoardBrickHeight;

			SDL_Rect destRect;
			destRect.x = m_fBrickOffsetX + m_fPositionX + i * BoardBrickWidth;
			destRect.y = m_fBrickOffsetY + m_fPositionY + j * BoardBrickHeight;
			destRect.w = BoardBrickWidth;
			destRect.h = BoardBrickHeight;

			SDL_RenderCopy(m_pxRenderer, m_pxBrickTexture, &sourceRect, &destRect);
		};
	};

	SDL_Rect destRect;
	destRect.x = 0;
	destRect.y = 0;
	destRect.w = 16;
	destRect.h = 600;
	SDL_RenderCopy(m_pxRenderer, m_pxSideTexture, nullptr, &destRect);

	destRect.x = 800 - 16;
	destRect.y = 0;
	destRect.w = 16;
	destRect.h = 600;
	SDL_RenderCopy(m_pxRenderer, m_pxSideTexture, nullptr, &destRect);
};

void GameBoard::CreateLevel()
{
	for (int i = 0; i < BoardWidth; i++)
	{
		for (int j = 0; j < BoardHeight; j++)
		{
			Brick brick;

			brick.m_iBrickType = rand() % 4;
			//brick.m_iBrickType = (i ^ j) % 4;
			brick.m_bBrickState = true;
			m_rgBricks[i][j] = brick;
		}
	}
}
