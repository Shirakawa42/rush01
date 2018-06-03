#include <Star.hpp>
#include <Game.hpp>
#include <cstdlib>

Star::Star(double speed, int y) : _speed(speed), _y(y)
{
	this->_x = W;
}

Star::Star()
{
	this->_x = W;
	this->_speed = std::rand()%45 +5;
	this->_y = std::rand()%(H-2) + 1;

}

Star::~Star()
{

}

Star::Star(Star const &source)
{
	(void)source;
}

void Star::think()
{
	double time = g_gm.frameTime();
	this->_x -= time * _speed;
	if (_x <= 0)
		_x = W;
	wmove(g_gm.win, this->_y, this->_x);
	wprintw(g_gm.win, "%c", '*');
}


Star & Star::operator=(const Star & rhs)
{
	(void)rhs;
	return (*this);
}

