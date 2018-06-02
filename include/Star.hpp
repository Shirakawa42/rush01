#pragma once

#include <ctime>

class Star
{
public:
	Star();
	Star(double speed, int y);
	~Star();
	Star(Star const &source);
	Star & operator=(const Star & rhs);
	void think();
private:
	double _speed;
	int _y;
	float _x;
};