#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#pragma once

#include "GameBoard.h"
#include "Paddle.h"
#include "Ball.h"

class Game
{
	public:
		
		Game();
		~Game();

		bool Initialize();
		void Run();

	private:

		void Clean();
		void Update(float fDeltaTime);
		void Render(float fDeltaTime);

		void NewGame();
		void ResetPaddle();
		void StickBall();

		void SetPaddleX(float fPositionX);
		void CheckBoardCollisions();
		float GetReflection(float fBallHitX);
		void CheckPaddleCollisions();
		void CheckBrickCollisions();
		void CheckBrickCollisions2();
		void BallBrickResponse(int iDirectionIndex);
		int GetBrickCount();

	private:

		SDL_Window* m_pxWindow;
		SDL_Renderer* m_pxRenderer;

		unsigned int m_uiLastTick;
		unsigned int m_uiFpsTick;
		unsigned int m_uiFramesPerSecond;
		unsigned int m_uiFrameCount;

		bool m_bPaddleStick;

		std::unique_ptr<GameBoard> m_pxGameboard;
		std::unique_ptr<Paddle> m_pxPaddle;
		std::unique_ptr<Ball> m_pxBall;

}; // Game

#endif // GAME_H_INCLUDED