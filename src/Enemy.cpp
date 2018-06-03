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
		case 2 :
				this->_size = 4;
				this->_drawMap = new std::string[4];
				this->_drawMap[0] = "/||>";
				this->_drawMap[1] = "<|||";
				this->_drawMap[2] = "\\||>";
				this->_drawMap[3] = "    ";
				break;
	}

	_x -= this->_size; 
	this->_lastshoot = clock();
	g_gm.registerEnemy(this);
	_shootingRate = 1;
}

Enemy::~Enemy()
{
	g_gm.removeEnemy(this);
}

Enemy::Enemy(Enemy const &source)
{
	(void)source;
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


	if ((clock() - this->_lastshoot )/CLOCKS_PER_SEC >=this->_shootingRate)
	{
//		new Projectile(_x + -5, _y + this->_size / 2 -1, 'L');
		if (  std::fabs(g_gm.getPlayer().getX() - this->_x) < 7)
		{
			this->_lastshoot = clock();
				
		}


	}
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
