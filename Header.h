#pragma once
#include <stdio.h>

class Player
{
private:
	int x, y;
public:
	Player() { x = 0; y = 0; }
	~Player(){}
	void move(int direction)
	{
		printf("Testing");
	}
};
