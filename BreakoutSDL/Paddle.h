#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED
#pragma once

#include "Entity.h"

class Paddle : public Entity
{
	public:
		Paddle(SDL_Renderer* pRenderer);
		~Paddle();

		void Update(float fDeltaTime);
		void Render(float fDeltaTime);

	private:

		SDL_Texture* m_pxPaddleTexture;

}; // Paddle

#endif // PADDLE_H_INCLUDED