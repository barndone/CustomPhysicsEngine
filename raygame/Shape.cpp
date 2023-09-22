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
	
	return	_rectA.GetMin(_posA).x < _rectB.GetMax(_posB).x&& _rectA.GetMax(_posA).x > _rectB.GetMin(_posB).x
			&& _rectA.GetMin(_posA).y < _rectB.GetMax(_posB).y&& _rectA.GetMax(_posA).y > _rectB.GetMin(_posB).y;
}

bool CheckAABBAABB(const glm::vec2& _posA, const Shape& _shapeA, const glm::vec2& _posB, const Shape& _shapeB)
{
	return CheckAABBAABB(_posA, _shapeA.AABBData, _posB, _shapeB.AABBData);
}

bool CheckCircleAABB(const glm::vec2& _posA, const Circle& _circleA, const glm::vec2& _posB, const AABB& _rectB)
{
	glm::vec2 ClampedPos = { glm::clamp(_posA.x, _rectB.GetMin(_posB).x, _rectB.GetMax(_posB).x), glm::clamp(_posA.y, _rectB.GetMin(_posB).y, _rectB.GetMax(_posB).y)};
	return sqrt(((_posA.x - ClampedPos.x) * (_posA.x - ClampedPos.x)) + ((_posA.y - ClampedPos.y) * (_posA.y - ClampedPos.y)))
																									< _circleA.Radius;
}

bool CheckCircleAABB(const glm::vec2& _posA, const Shape& _shapeA, const glm::vec2& _posB, const Shape& _shapeB)
{
	return CheckCircleAABB(_posA, _shapeA.CircleData, _posB, _shapeB.AABBData);
}

glm::vec2 DepenetrateCircleCircle(const glm::vec2& _posA, const Circle& _circleA, const glm::vec2& _posB, const Circle& _circleB, float& _pen)
{	
	//	grab the distance
	float dist = glm::length(_posB - _posA);
	//	sum of the radii
	float radii = _circleA.Radius + _circleB.Radius;
	//	calculate penetration
	_pen = radii - dist;

	//	if the distance is zero normalized vector will be divide by zero, return an arbitrary normal
	if (dist == 0.0f)
	{
		return glm::vec2(0.0f, 1.0f);
	}
	else
	{
		//	return the collision normal
		return glm::normalize(_posB - _posA);
	}
}

glm::vec2 DepenetrateCircleCircle(const glm::vec2& _posA, const Shape& _shapeA, const glm::vec2& _posB, const Shape& _shapeB, float& _pen)
{
	return DepenetrateCircleCircle(_posA, _shapeA.CircleData, _posB, _shapeB.CircleData, _pen);
}

glm::vec2 DepenetrateAABBAABB(const glm::vec2& _posA, const AABB& _rectA, const glm::vec2& _posB, const AABB& _rectB, float& _pen)
{
	glm::vec2 rawOffset = _posB - _posA;

	//	measure the amount of overlap on each axis and choose the one with the least amount of overlap
	float xPen = (_rectA.Width / 2.0f) + (_rectB.Width / 2.0f) - fabs(_posB.x - _posA.x);
	float yPen = ((_rectA.Height / 2.0f) + (_rectB.Height / 2.0f)) - fabs(_posB.y - _posA.y);

	(xPen <= yPen) ? _pen = xPen : _pen = yPen;
	//	return the collision normal
	return (xPen <= yPen) ? glm::vec2(copysignf(1.0f, rawOffset.x), 0) : glm::vec2(0, copysignf(1.0f, rawOffset.y));
}

glm::vec2 DepenetrateAABBAABB(const glm::vec2& _posA, const Shape& _shapeA, const glm::vec2& _posB, const Shape& _shapeB, float& _pen)
{
	return DepenetrateAABBAABB(_posA, _shapeA.AABBData, _posB, _shapeB.AABBData, _pen);
}

glm::vec2 DepenetrateCircleAABB(const glm::vec2& _posA, const Circle& _circleA, const glm::vec2& _posB, const AABB& _rectB, float& _pen)
{
	glm::vec2 ClampedPos = { glm::clamp(_posA.x, _rectB.GetMin(_posB).x, _rectB.GetMax(_posB).x), glm::clamp(_posA.y, _rectB.GetMin(_posB).y, _rectB.GetMax(_posB).y) };

	
	if (_posA.x >= _rectB.GetMin(_posB).x && _posA.x <= _rectB.GetMax(_posB).x &&
		_posA.y >= _rectB.GetMin(_posB).y && _posA.y <= _rectB.GetMax(_posB).y)
	{
		glm::vec2 rawOffset = _posB - _posA;
		glm::vec2 absOffset = glm::abs(rawOffset);

		glm::vec2 overlap = glm::vec2(_rectB.Width, _rectB.Height) - absOffset;

		glm::vec2 normal = {};

		(overlap.x < overlap.y) ? _pen = overlap.x : _pen = overlap.y;
		return (overlap.x < overlap.y) ? glm::vec2(copysignf(1.0f, rawOffset.x), 0) : glm::vec2(0, copysignf(1.0f, rawOffset.y));
	}
	else
	{
		_pen = _circleA.Radius - glm::length(_posA - ClampedPos);
		return glm::normalize(ClampedPos - _posA);
	}
}

glm::vec2 DepenetrateCircleAABB(const glm::vec2& _posA, const Shape& _shapeA, const glm::vec2& _posB, const Shape& _shapeB, float& _pen)
{
	return DepenetrateCircleAABB(_posA, _shapeA.CircleData, _posB, _shapeB.AABBData, _pen);
}
