#include "Include.h"

Body makeSegment(int x, int y)
{
	Body body;
	body.x = x;
	body.y = y;
	return body;
}

bool operator == (Body comparedObject1, Body comparedObject2)
{
	return (comparedObject1.x == comparedObject2.x && comparedObject1.y == comparedObject2.y);
}