#include "stdafx.h"
#include "Vector2.h"


const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::UNIT_X(1.0f, 0.0f);
const Vector2 Vector2::UNIT_Y(0.0f, 1.0f);
const Vector2 Vector2::NEGATIVE_UNIT_X(-1.0f, 0.0f);
const Vector2 Vector2::NEGATIVE_UNIT_Y(0.0f, -1.0f);

Vector2::Vector2()
{
	m_fPositionX = 0;
	m_fPositionY = 0;
};

Vector2::Vector2(float fPositionX, float fPositionY)
{
	m_fPositionX = fPositionX;
	m_fPositionY = fPositionY;
};

Vector2::Vector2(const Vector2 &kVector2)
{
	m_fPositionX = kVector2.m_fPositionX;
	m_fPositionY = kVector2.m_fPositionY;
};

Vector2::~Vector2()
{
};

Vector2& Vector2::operator = (const Vector2 &kVector2)
{
	m_fPositionX = kVector2.m_fPositionX;
	m_fPositionY = kVector2.m_fPositionY;

	return (*this);
};

bool Vector2::operator==(const Vector2 &kVector2) const
{
	if (m_fPositionX == kVector2.m_fPositionX && m_fPositionY == kVector2.m_fPositionY)
	{
		return true;
	};

	return false;
};

bool Vector2::operator!=(const Vector2 &kVector2) const
{
	if (m_fPositionX != kVector2.m_fPositionX || m_fPositionY != kVector2.m_fPositionY)
	{
		return true;
	};

	return false;
};

Vector2 Vector2::operator*(const Vector2 &kVector2) const
{
	Vector2 result;

	result.m_fPositionX = m_fPositionX * kVector2.m_fPositionX;
	result.m_fPositionY = m_fPositionY * kVector2.m_fPositionY;

	return result;
};

Vector2 Vector2::operator/(const Vector2 &kVector2) const
{
	Vector2 result;

	result.m_fPositionX = m_fPositionX / kVector2.m_fPositionX;
	result.m_fPositionY = m_fPositionY / kVector2.m_fPositionY;

	return result;
};

Vector2 Vector2::operator+(const Vector2 &kVector2) const
{
	Vector2 result;

	result.m_fPositionX = m_fPositionX + kVector2.m_fPositionX;
	result.m_fPositionY = m_fPositionY + kVector2.m_fPositionY;

	return result;
};

Vector2 Vector2::operator-(const Vector2 &kVector2) const
{
	Vector2 result;

	result.m_fPositionX = m_fPositionX - kVector2.m_fPositionX;
	result.m_fPositionY = m_fPositionY - kVector2.m_fPositionY;

	return result;
};

Vector2 Vector2::operator*(const float scalar) const
{
	Vector2 result;

	result.m_fPositionX = m_fPositionX * scalar;
	result.m_fPositionY = m_fPositionY * scalar;

	return result;
};

Vector2 Vector2::operator/(const float kfScalar) const
{
	Vector2 result;

	result.m_fPositionX = m_fPositionX / kfScalar;
	result.m_fPositionY = m_fPositionY / kfScalar;

	return result;
};

Vector2 Vector2::operator+(const float kfScalar) const
{
	Vector2 result;

	result.m_fPositionX = m_fPositionX + kfScalar;
	result.m_fPositionY = m_fPositionY + kfScalar;

	return result;
};

Vector2 Vector2::operator-(const float kfScalar) const
{
	Vector2 result;

	result.m_fPositionX = m_fPositionX - kfScalar;
	result.m_fPositionY = m_fPositionY - kfScalar;

	return result;
};

Vector2& Vector2::operator*=(const Vector2 &kVector2)
{
	m_fPositionX *= kVector2.m_fPositionX;
	m_fPositionY *= kVector2.m_fPositionY;

	return (*this);
};

Vector2& Vector2::operator +=(const Vector2 &kVector2)
{
	m_fPositionX += kVector2.m_fPositionX;
	m_fPositionY += kVector2.m_fPositionY;

	return (*this);
};

Vector2& Vector2::operator -=(const Vector2 &kVector2)
{
	m_fPositionX -= kVector2.m_fPositionX;
	m_fPositionY -= kVector2.m_fPositionY;

	return (*this);
};

Vector2& Vector2::operator += (const float scalar)
{

	m_fPositionX += scalar;
	m_fPositionY += scalar;

	return (*this);
};

float Vector2::Magnitude() const
{
	return sqrtf((m_fPositionX * m_fPositionX) + (m_fPositionY * m_fPositionY));
};

float Vector2::SquaredMagnitude() const
{
	return (m_fPositionX * m_fPositionX) + (m_fPositionY * m_fPositionY);
};

void Vector2::Normalize()
{
	float length(1 / sqrtf((m_fPositionX * m_fPositionX) + (m_fPositionY * m_fPositionY)));

	m_fPositionX *= length;
	m_fPositionY *= length;
};

Vector2 Vector2::NormalizedCopy() const
{
	float length(1 / sqrtf((m_fPositionX * m_fPositionX) + (m_fPositionY * m_fPositionY)));

	Vector2 result;

	result.m_fPositionX = m_fPositionX * length;
	result.m_fPositionY = m_fPositionY * length;

	return result;
};

float Vector2::Dot(const Vector2 &kVector2) const
{
	return (m_fPositionX * kVector2.m_fPositionX) + (m_fPositionY * kVector2.m_fPositionY);
};
