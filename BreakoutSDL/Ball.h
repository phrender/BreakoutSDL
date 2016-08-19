#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED
#pragma once

#include "Entity.h"

class Ball : public Entity
{
	public:

		Ball(SDL_Renderer* pRenderer);
		~Ball();

		void Update(float fDeltaTime);
		void Render(float fDeltaTime);

		void SetDirection(float fDirectionX, float fDirectionY);

	public:

		float m_fDirectionX;
		float m_fDirectionY;

	private:

		SDL_Texture* m_pxBallTexture;

};

#endif // BALL_H_INCLUDED