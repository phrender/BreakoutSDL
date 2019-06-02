#include "stdafx.h"
#include "Game.h"

Game::Game() : 
	m_pxWindow(nullptr), m_pxRenderer(nullptr),
	m_pxGameboard(nullptr), m_pxPaddle(nullptr),
	m_pxBall(nullptr), m_uiWindowWidth(0),
	m_uiWindowHeight(0), m_uiLastTick(0), m_uiFpsTick(0),
	m_uiFramesPerSecond(0), m_uiFrameCount(0),
	m_bPaddleStick(true)
{
};

Game::~Game()
{
};

bool Game::Initialize(unsigned int uiWindowWidth, unsigned int uiWindowHeight)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_uiWindowWidth = uiWindowWidth > 800 ? uiWindowWidth : 800;
	m_uiWindowHeight = uiWindowHeight > 600 ? uiWindowWidth : 600;

	m_pxWindow = SDL_CreateWindow("Breakout SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_uiWindowWidth, m_uiWindowHeight, SDL_WINDOW_SHOWN);

	if (!m_pxWindow)
	{
		printf("Failed to create window: %s\n", SDL_GetError());
		return false;
	};

	m_pxRenderer = SDL_CreateRenderer(m_pxWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!m_pxRenderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		return false;
	};

	m_uiLastTick = SDL_GetTicks();
	m_uiFpsTick = m_uiLastTick;

	return true;
};

void Game::Clean()
{
	if (m_pxBall)
	{
		delete m_pxBall;
		m_pxBall = nullptr;
	};

	if (m_pxPaddle)
	{
		delete m_pxPaddle;
		m_pxPaddle = nullptr;
	};

	if (m_pxGameboard)
	{
		delete m_pxGameboard;
		m_pxGameboard = nullptr;
	};

	if (m_pxRenderer)
	{
		SDL_DestroyRenderer(m_pxRenderer);
		m_pxRenderer = nullptr;
	};

	if (m_pxWindow)
	{
		SDL_DestroyWindow(m_pxWindow);
		m_pxWindow = nullptr;
	};
};

void Game::Run()
{
	SDL_ShowCursor(false);

	m_pxGameboard = new GameBoard(m_pxRenderer);
	m_pxPaddle = new Paddle(m_pxRenderer);
	m_pxBall = new Ball(m_pxRenderer);

	NewGame();

	while (true)
	{
		SDL_Event e;
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				break;
			};
		};

		unsigned int uiCurrentTick = SDL_GetTicks();
		float fDeltaTime = (uiCurrentTick - m_uiLastTick) / 1000.0f;

		if (uiCurrentTick - m_uiFpsTick >= FPSDelay)
		{
			m_uiFramesPerSecond = m_uiFrameCount * (1000.0f / (uiCurrentTick - m_uiFpsTick));
			m_uiFpsTick = uiCurrentTick;
			m_uiFrameCount = 0;

			/*
			char rgcBuffer[128];
			snprintf(rgcBuffer, 128, "Breakout SDL (fps: %u)", m_uiFramesPerSecond);
			SDL_SetWindowTitle(m_pxWindow, rgcBuffer);
			*/
		}
		else
		{
			m_uiFrameCount++;
		};

		m_uiLastTick = uiCurrentTick;

		Update(fDeltaTime);
		Render(fDeltaTime);
	}

	Clean();

	SDL_Quit();
};

void Game::NewGame()
{
	m_pxGameboard->CreateLevel();
	ResetPaddle();
};

void Game::ResetPaddle()
{
	m_bPaddleStick = true;
	StickBall();
};

void Game::StickBall()
{
	m_pxBall->SetPositionX(m_pxPaddle->GetPositionX() + m_pxPaddle->GetWidth() / 2 - m_pxBall->GetWidth() / 2);
	m_pxBall->SetPositionY(m_pxPaddle->GetPositionY() - m_pxBall->GetHeight());
};

void Game::Update(float fDeltaTime)
{
	int iMouseX;
	int iMouseY;
	Uint8 ui8MouseState = SDL_GetMouseState(&iMouseX, &iMouseY);

	SetPaddleX(iMouseX - m_pxPaddle->GetWidth() / 2.0f);

	if (ui8MouseState & SDL_BUTTON(1))
	{
		if (m_bPaddleStick)
		{
			m_bPaddleStick = false;
			m_pxBall->SetDirection(1.0f, -1.0f);
		};
	};

	if (m_bPaddleStick)
	{
		StickBall();
	};

	CheckBoardCollisions();
	CheckPaddleCollisions();
	CheckBrickCollisions();

	
	if (GetBrickCount() == 0)
	{
		NewGame();
	};
	

	m_pxGameboard->Update(fDeltaTime);
	m_pxPaddle->Update(fDeltaTime);

	if (!m_bPaddleStick)
	{
		m_pxBall->Update(fDeltaTime);
	};

};

void Game::SetPaddleX(float fPositionX)
{
	float fNewPositionX;

	if (fPositionX < m_pxGameboard->GetPositionX())
	{
		fNewPositionX = m_pxGameboard->GetPositionX();
	}
	else if (fPositionX + m_pxPaddle->GetWidth() > m_pxGameboard->GetPositionX() + m_pxGameboard->GetWidth())
	{
		fNewPositionX = m_pxGameboard->GetPositionX() + m_pxGameboard->GetWidth() - m_pxPaddle->GetWidth();
	}
	else
	{
		fNewPositionX = fPositionX;
	};

	m_pxPaddle->SetPositionX(fNewPositionX);
};

void Game::CheckBoardCollisions()
{
	if (m_pxBall->GetPositionY() < m_pxGameboard->GetPositionY())
	{
		m_pxBall->SetPositionY(m_pxGameboard->GetPositionY());
		m_pxBall->m_fDirectionY *= -1.0f;
	}
	else if (m_pxBall->GetPositionY() + m_pxBall->GetHeight() > m_pxGameboard->GetPositionY() + m_pxGameboard->GetHeight())
	{
		ResetPaddle();
	};

	if (m_pxBall->GetPositionX() <= m_pxGameboard->GetPositionX())
	{
		m_pxBall->SetPositionX(m_pxGameboard->GetPositionX());
		m_pxBall->m_fDirectionX *= -1.0f;
	}
	else if (m_pxBall->GetPositionX() + m_pxBall->GetWidth() >= m_pxGameboard->GetPositionX() + m_pxGameboard->GetWidth())
	{
		m_pxBall->SetPositionX(m_pxGameboard->GetPositionX() + m_pxGameboard->GetWidth() - m_pxBall->GetWidth());
		m_pxBall->m_fDirectionX *= -1.0f;
	};
};

float Game::GetReflection(float fBallHitX)
{
	if (fBallHitX < 0.0f)
	{
		fBallHitX = 0.0f;
	}
	else if (fBallHitX > m_pxPaddle->GetWidth())
	{
		fBallHitX = m_pxPaddle->GetWidth();
	};

	fBallHitX -= m_pxPaddle->GetWidth() / 2.0f;

	return (2.0f * (fBallHitX / (m_pxPaddle->GetWidth() / 2.0f)));
};

void Game::CheckPaddleCollisions()
{
	float fBallCenterX = m_pxBall->GetPositionX() + (m_pxBall->GetWidth() / 2.0f);

	if (m_pxBall->Collides(m_pxPaddle))
	{
		m_pxBall->SetPositionY(m_pxPaddle->GetPositionY() - m_pxBall->GetHeight());
		m_pxBall->SetDirection(GetReflection(fBallCenterX - m_pxPaddle->GetPositionX()), -1.0f);
	};
};

// Old collision code
/*
void Game::CheckBrickCollisions()
{
	for (int i = 0; i < BoardWidth; i++)
	{
		for (int j = 0; j < BoardHeight; j++) 
		{
			Brick brick = m_pxGameboard->m_rgBricks[i][j];

			// Check if brick is present
			if (brick.m_bBrickState)
			{
				// Brick x and y coordinates
				float brickx = m_pxGameboard->m_fBrickOffsetX + m_pxGameboard->GetPositionX() + i * BoardBrickWidth;
				float bricky = m_pxGameboard->m_fBrickOffsetY + m_pxGameboard->GetPositionY() + j * BoardBrickHeight;

				float w = 0.5f * (m_pxBall->GetWidth() + BoardBrickHeight);
				float h = 0.5f * (m_pxBall->GetHeight() + BoardBrickHeight);
				float dx = (m_pxBall->GetPositionX() + 0.5f * m_pxBall->GetWidth()) - (brickx + 0.5f * BoardBrickWidth);
				float dy = (m_pxBall->GetPositionY() + 0.5f * m_pxBall->GetHeight()) - (bricky + 0.5f * BoardBrickHeight);

				if (fabs(dx) <= w && fabs(dy) <= h) 
				{
					// Collision detected
					m_pxGameboard->m_rgBricks[i][j].m_bBrickState = false;

					float wy = w * dy;
					float hx = h * dx;

					if (wy > hx)
					{
						if (wy > -hx)
						{
							// Bottom (y is flipped)
							BallBrickResponse(3);
						}
						else 
						{
							// Left
							BallBrickResponse(0);
						};
					}
					else 
					{
						if (wy > -hx) 
						{
							// Right
							BallBrickResponse(2);
						}
						else
						{
							// Top (y is flipped)
							BallBrickResponse(1);
						};
					};
					return;
				};
			};
		};
	};
};
*/

void Game::CheckBrickCollisions()
{
	for (int i = 0; i < BoardWidth; i++) 
	{
		for (int j = 0; j < BoardHeight; j++) 
		{
			Brick brick = m_pxGameboard->m_rgBricks[i][j];

			// Check if brick is present
			if (brick.m_bBrickState) 
			{
				// Brick x and y coordinates
				float brickx = m_pxGameboard->m_fBrickOffsetX + m_pxGameboard->GetPositionX() + i * BoardBrickWidth;
				float bricky = m_pxGameboard->m_fBrickOffsetY + m_pxGameboard->GetPositionY() + j * BoardBrickHeight;

				// Center of the ball x and y coordinates
				float ballcenterx = m_pxBall->GetPositionX() + 0.5f * m_pxBall->GetWidth();
				float ballcentery = m_pxBall->GetPositionY() + 0.5f * m_pxBall->GetHeight();

				// Center of the brick x and y coordinates
				float brickcenterx = brickx + 0.5f * BoardBrickWidth;
				float brickcentery = bricky + 0.5f * BoardBrickHeight;

				if (m_pxBall->GetPositionX() <= brickx + BoardBrickWidth && m_pxBall->GetPositionX() + m_pxBall->GetWidth() >= brickx && m_pxBall->GetPositionY() <= bricky + BoardBrickHeight && m_pxBall->GetPositionY() + m_pxBall->GetHeight() >= bricky) 
				{
					// Collision detected, remove the brick
					m_pxGameboard->m_rgBricks[i][j].m_bBrickState = false;

					// Asume the ball goes slow enough to not skip through the bricks

					// Calculate ysize
					float ymin = 0;
					if (bricky > m_pxBall->GetPositionY())
					{
						ymin = bricky;
					}
					else 
					{
						ymin = m_pxBall->GetPositionY();
					};

					float ymax = 0;
					if (bricky + BoardBrickHeight < m_pxBall->GetPositionY() + m_pxBall->GetHeight()) 
					{
						ymax = bricky + BoardBrickHeight;
					}
					else 
					{
						ymax = m_pxBall->GetPositionY() + m_pxBall->GetHeight();
					};

					float ysize = ymax - ymin;

					// Calculate xsize
					float xmin = 0;
					if (brickx > m_pxBall->GetPositionX())
					{
						xmin = brickx;
					}
					else 
					{
						xmin = m_pxBall->GetPositionX();
					};

					float xmax = 0;
					if (brickx + BoardBrickWidth < m_pxBall->GetPositionX() + m_pxBall->GetWidth()) 
					{
						xmax = brickx + BoardBrickWidth;
					}
					else 
					{
						xmax = m_pxBall->GetPositionX() + m_pxBall->GetWidth();
					};

					float xsize = xmax - xmin;
					if (xsize > ysize) 
					{
						if (ballcentery > brickcentery) 
						{
							// Bottom
							m_pxBall->SetPositionY(m_pxBall->GetPositionY() - ysize + 0.01f); // Move out of collision
							BallBrickResponse(3);
						}
						else
						{
							// Top
							m_pxBall->SetPositionY(m_pxBall->GetPositionY() - ysize + 0.01f); // Move out of collision
							BallBrickResponse(1);
						};
					}
					else 
					{
						if (ballcenterx < brickcenterx) 
						{
							// Left
							m_pxBall->SetPositionX(m_pxBall->GetPositionX() - xsize + 0.01f); // Move out of collision
							BallBrickResponse(0);
						}
						else 
						{
							// Right
							m_pxBall->SetPositionX(m_pxBall->GetPositionX() - xsize + 0.01f); // Move out of collision
							BallBrickResponse(2);
						}
					};

					return;
				};
			};
		};
	};
};

void Game::BallBrickResponse(int iDirectionIndex)
{
	// iDirectionIndex = [0 - Left, 1 - Top, 2 - Right, 3 - Bottom]

	int iMulX = 1;
	int iMulY = 1;

	if (m_pxBall->m_fDirectionX > 0) 
	{
		if (m_pxBall->m_fDirectionY > 0) 
		{
			if (iDirectionIndex == 0 || iDirectionIndex == 3) 
			{
				iMulX = -1;
			}
			else 
			{
				iMulY = -1;
			};
		}
		else if (m_pxBall->m_fDirectionY < 0) 
		{
			if (iDirectionIndex == 0 || iDirectionIndex == 1) 
			{
				iMulX = -1;
			}
			else 
			{
				iMulY = -1;
			};
		};
	}

	else if (m_pxBall->m_fDirectionX < 0) 
	{
		if (m_pxBall->m_fDirectionY > 0) 
		{
			if (iDirectionIndex == 2 || iDirectionIndex == 3) 
			{
				iMulX = -1;
			}
			else 
			{
				iMulY = -1;
			}
		}
		else if (m_pxBall->m_fDirectionY < 0) 
		{
			if (iDirectionIndex == 1 || iDirectionIndex == 2) 
			{
				iMulX = -1;
			}
			else 
			{
				iMulY = -1;
			};
		}
	};

	m_pxBall->SetDirection(iMulX * m_pxBall->m_fDirectionX, iMulY * m_pxBall->m_fDirectionY);
};

int Game::GetBrickCount()
{
	int iBrickCount = 0;

	for (int i = 0; i < BoardWidth; i++)
	{
		for (int j = 0; j < BoardHeight; j++)
		{
			Brick brick = m_pxGameboard->m_rgBricks[i][j];

			if (brick.m_bBrickState)
			{
				iBrickCount++;
			};
		};
	};

	return iBrickCount;
};

void Game::Render(float fDeltaTime)
{
	SDL_RenderClear(m_pxRenderer);
	
	m_pxGameboard->Render(fDeltaTime);
	m_pxPaddle->Render(fDeltaTime);
	m_pxBall->Render(fDeltaTime);

	SDL_RenderPresent(m_pxRenderer);
}
