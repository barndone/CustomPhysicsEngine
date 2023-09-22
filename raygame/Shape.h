#pragma once
#include <cstdint>

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

struct Circle
{
	float Radius;
};

struct AABB 
{
	float Width;
	float Height;
};

//	NOT THE SAME THING AS AN ENUM (not technically)
//	FUNCTIONALLY it is the same though...

//	using unsigned int to explicitly define the size!
//	int is not guaranteed to be 8 bits, at least guaranteed to be a certain number of bits
//	unsigned ints are guaranteed to be the size specified!
enum class ShapeType : uint8_t
{
	NONE		= 0,
	CIRCLE		= 1 << 0,
	AABB		= 1 << 1
};

struct Shape
{
	ShapeType Type;
	//	anonymous union
	//	data structure capable of storing ONE type of data, it only has space for one member
	//	but that member is not always the same thing
	
	//	reserves a space in memory comparable to the LARGEST data size in the union
	//	if you assign or access one ONLY acces the one you assigned to!

	//	accessing the data will not be done through a method name, just by accessing the member itself
	union
	{
		Circle CircleData;	//	4 bytes
		AABB AABBData;
	};
}; 

bool CheckCircleCircle(const glm::vec2& _posA, const Circle& _circleA, const glm::vec2& _posB, const Circle& _circleB);
bool CheckCircleCircle(const glm::vec2& _posA, const Shape& _shapeA, const glm::vec2& _posB, const Shape& _shapeB);
bool CheckAABBAABB(const glm::vec2& _posA, const AABB& _rectA, const glm::vec2& _posB, const AABB& _rectB);
bool CheckAABBAABB(const glm::vec2& _posA, const Shape& _shapeA, const glm::vec2& _posB, const Shape& _shapeB);
bool CheckCircleAABB(const glm::vec2& _posA, const Circle& _circleA, const glm::vec2& _posB, const AABB& _rectB);
bool CheckCircleAABB(const glm::vec2& _posA, const Shape& _shapeA, const glm::vec2& _posB, const Shape& _shapeB);