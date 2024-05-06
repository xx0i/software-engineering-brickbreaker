#pragma once
#include "BaseObject.h"

class Box : public BaseObject
{
public:
	bool doubleThick = false;
	int width = 2;
	int height = 2;
	void Draw() const override;
	bool Contains(int x, int y);
	int count = 0; //added to implement collision response with any colour
};