#include <Enemy.hpp>



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



}

Enemy::~Enemy()
{

}

Enemy::Enemy(Enemy const &source)
{

}

Enemy & Enemy::operator=(const Enemy & rhs)
{
	(void)rhs;
	return (*this);
}


size_t Enemy::getSize(void) const
{
	return (this->_size);
}
