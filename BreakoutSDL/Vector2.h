#ifndef VECTOR2_H_INCLUDED
#define VECTOR2_H_INCLUDED
#pragma once

class Vector2
{
	public:
		Vector2();
		Vector2(float fPositionX, float fPositionY);
		Vector2(const Vector2 &kVector2);
		~Vector2();
	
		Vector2& operator=(const Vector2 &kVector2);
		bool operator==(const Vector2 &kVector2) const;
		bool operator!=(const Vector2 &kVector2) const;
	
		Vector2 operator*(const Vector2 &kVector2) const;
		Vector2 operator/(const Vector2 &kVector2) const;
		Vector2 operator+(const Vector2 &kVector2) const;
		Vector2 operator-(const Vector2 &kVector2) const;
	
		Vector2 operator*(const float kfScalar) const;
		Vector2 operator/(const float kfScalar) const;
		Vector2 operator+(const float kfScalar) const;
		Vector2 operator-(const float kfScalar) const;
	
		Vector2& operator*=(const Vector2 &kVector2);
		Vector2& operator+=(const Vector2 &kVector2);
		Vector2& operator-=(const Vector2 &kVector2);
	
		Vector2& operator+=(const float kfScalar);
	
		float Magnitude() const;
		float SquaredMagnitude() const;
		void Normalize();
		Vector2 NormalizedCopy() const;
		float Dot(const Vector2 &kVector2) const;
	
		static const Vector2 ZERO;
		static const Vector2 UNIT_X;
		static const Vector2 UNIT_Y;
		static const Vector2 NEGATIVE_UNIT_X;
		static const Vector2 NEGATIVE_UNIT_Y;
	
		float m_fPositionX;
		float m_fPositionY;
}; // Vector2

#endif // VECTOR2_H_INCLUDED