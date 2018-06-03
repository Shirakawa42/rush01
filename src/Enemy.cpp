#include <Enemy.hpp>
#include <Game.hpp>


Enemy::Enemy(unsigned int x, unsigned int y, unsigned int type) : _x(x), _y(y)
{
	// atension ca va aitr moch
	switch (type)
	{
		case 1 :
				this->_size = 1;
				this->_drawMap = new std::string[1];
				this->_drawMap[0] = "&";
				break;
	}
	g_gm.registerEnemy(this);
}

Enemy::~Enemy()
{
	g_gm.removeEnemy(this);
}

Enemy::Enemy(Enemy const &source)
{

}

Enemy & Enemy::operator=(const Enemy & rhs)
{
	(void)rhs;
	return (*this);
}


unsigned int Enemy::getX()
{
	return (this->_x);
}

unsigned int Enemy::getY()
{
	return (this->_y);
}

size_t Enemy::getSize()
{
	return (this->_size);
}


std::string *Enemy::getDrawMap()
{
	return (this->_drawMap);
}

void Enemy::think()
{
	g_gm.putStrings(this->_x, this->_y, this->_drawMap, this->_size);
	// onhit()
}

void Enemy::onHit()
{
	//g_gm.destroyProjectile(self);
}





size_t Enemy::getSize(void) const
{
	return (this->_size);
}


bool Enemy::collides(int x, int y)
{
	if (x < this->getX())
		return false;
	if (y < this->getY())
		return false;

	int diffx = x - this->getX();
	int diffy = y - this->getY();
	if (diffx > this->getSize())
		return false;
	if (diffy > this->getSize())
		return false;
	char c = this->getDrawMap()[x].c_str()[y];
	if (c != ' ')
		return (true);
	return (false);
}