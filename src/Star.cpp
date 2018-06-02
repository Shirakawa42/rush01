#include <Star.hpp>
#include <Game.hpp>
#define W 100

Star::Star(double speed, int y) : _speed(speed), _y(y)
{
	this->_x = W;
}

Star::~Star()
{

}

Star::Star(Star const &source)
{

}

void Star::think()
{
	double time = g_gm.frameTime();
	this->_x -= time * _speed;
	if (_x <= 0)
		_x = W;
	//std::cout << _x << std::endl;
	wmove(g_gm.win, this->_y, this->_x);
	wprintw(g_gm.win, "%c", '*');
}


Star & Star::operator=(const Star & rhs)
{
	(void)rhs;
	return (*this);
}

