#include "Shape.h"
#include "glm/glm.hpp"

bool CheckCircleCircle(const glm::vec2& _posA, const Circle& _circleA, const glm::vec2& _posB, const Circle& _circleB)
{
	float radii = _circleA.Radius + _circleB.Radius;

	float distance = glm::length(_posB - _posA);

	return distance < radii;
}
bool CheckCircleCircle(const glm::vec2& _posA, const Shape& _shapeA, const glm::vec2& _posB, const Shape& _shapeB)
{
	return CheckCircleCircle(_posA, _shapeA.CircleData, _posB, _shapeB.CircleData);
}

bool CheckAABBAABB(const glm::vec2& _posA, const AABB& _rectA, const glm::vec2& _posB, const AABB& _rectB)
{
	glm::vec2 RectAMin = { _posA.x - _rectA.Width, _posA.y - _rectA.Height };
	glm::vec2 RectAMax = { _posA.x + _rectA.Width, _posA.y + _rectA.Height };
	glm::vec2 RectBMin = { _posB.x - _rectB.Width, _posB.y - _rectB.Height };
	glm::vec2 RectBMax = { _posB.x + _rectB.Width, _posB.y + _rectB.Height };

	return	RectAMin.x < RectBMax.x && RectAMax.x > RectBMin.x
			&& RectAMin.y < RectBMax.y && RectAMax.y > RectBMin.y;
}

bool CheckAABBAABB(const glm::vec2& _posA, const Shape& _shapeA, const glm::vec2& _posB, const Shape& _shapeB)
{
	return CheckAABBAABB(_posA, _shapeA.AABBData, _posB, _shapeB.AABBData);
}

bool CheckCircleAABB(const glm::vec2& _posA, const Circle& _circleA, const glm::vec2& _posB, const AABB& _rectB)
{
	float TestValueX = 0;
	float TestValueY = 0;

	//	circle to the left of rect
	if (_posA.x < _posB.x - _rectB.Width / 2.0f)
	{
		TestValueX = _posB.x - _rectB.Width / 2.0f;
	}

	//	circle to the right of rect
	else if (_posA.x > _posB.x + _rectB.Width / 2.0f)
	{
		TestValueX = _posB.x + _rectB.Width / 2.0f;
	}
	else { TestValueX = _posA.x; }

	//	circle above rect (screenspace)
	if (_posA.y < _posB.y - _rectB.Height / 2.0f)
	{
		TestValueY = _posB.y - _rectB.Height / 2.0f;
	}

	//	circle below rect
	else if (_posA.y > _posB.y + _rectB.Height / 2.0f)
	{
		TestValueY = _posB.y + _rectB.Height / 2.0f;
	}
	else { TestValueY = _posA.y; }
	//	TODO: handle circle inside of the square

	float DistX = _posA.x - TestValueX;
	float DistY = _posA.y - TestValueY;

	float Distance = sqrt((DistX * DistX) + (DistY * DistY));

	return Distance <= _circleA.Radius;
}

bool CheckCircleAABB(const glm::vec2& _posA, const Shape& _shapeA, const glm::vec2& _posB, const Shape& _shapeB)
{
	return CheckCircleAABB(_posA, _shapeA.CircleData, _posB, _shapeB.AABBData);
}
