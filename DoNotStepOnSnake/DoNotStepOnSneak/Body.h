#pragma once
struct Body
{
public:
	int x;
	int y;
};
Body makeSegment(int x, int y);
bool operator == (Body comparedObject1, Body comparedObject2);