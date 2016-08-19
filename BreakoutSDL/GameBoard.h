#pragma once

#include "Entity.h"

class Brick
{
	public:

		int m_iBrickType;
		bool m_bBrickState;

};

class GameBoard : public Entity
{
	public:

		GameBoard(SDL_Renderer* pRenderer);
		~GameBoard();

		void Update(float fDeltaTime);
		void Render(float fDeltaTime);
		void CreateLevel();

		Brick m_rgBricks[BoardWidth][BoardHeight];

	public:

		float m_fBrickOffsetX;
		float m_fBrickOffsetY;

	private:

		SDL_Texture* m_pxBrickTexture;
		SDL_Texture* m_pxSideTexture;


};

