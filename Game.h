#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector> //added

class Game
{
	Ball ball;
	Box paddle;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	//initialize the bricks + vector -> brick details + added to vector in cpp
	Box brick1;
	Box brick2;
	Box brick3;
	Box brick4;
	Box brick5;
	std::vector<Box> bricks;

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};