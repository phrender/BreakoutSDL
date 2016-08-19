#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#pragma once

class Entity
{
	public:

		Entity(SDL_Renderer* pRenderer);
		virtual ~Entity();

		virtual void Update(float fDeltaTime);
		virtual void Render(float fDeltaTime);

		virtual float GetPositionX();
		virtual void SetPositionX(float fNewPositionX);
		virtual float GetPositionY();
		virtual void SetPositionY(float fNewPositionY);
		virtual float GetWidth();
		virtual void SetWidth(float fNewWidth);
		virtual float GetHeight();
		virtual void SetHeight(float fNewHeight);

		bool Collides(Entity* pOtherEntity);

	protected:

		float m_fPositionX;
		float m_fPositionY;
		float m_fWidth;
		float m_fHeight;

		SDL_Renderer* m_pxRenderer;

}; // Entity

#endif // ENTITY_H_INCLUDED