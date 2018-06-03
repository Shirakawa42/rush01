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
	
	_shootingRate = 1;

	t_enemy	*tmp;
	if (g_gm.enemyList == NULL)
	{
		g_gm.enemyList = new (t_enemy);
		g_gm.enemyList->enemy = this;
		g_gm.enemyList->next = NULL;
		return;
	}
	tmp = g_gm.enemyList;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new (t_enemy);
	tmp->next->enemy = this;
	tmp->next->next = NULL;
}

Enemy::~Enemy()
{
	t_enemy	*tmp = g_gm.enemyList;;
	t_enemy	*prev = NULL;;

	while (tmp != NULL && tmp->enemy != this)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp && tmp->enemy == this)
	{
		//delete tmp->projectile; // pas de boucle infinie svp les enfants
		if (prev == NULL)
		{
			if (tmp->next)
				g_gm.enemyList = tmp->next;
			else
				g_gm.enemyList = NULL;
			delete tmp;
		}
		else
		{
			if (tmp->next)
				prev->next = tmp->next;
			else
				prev->next = NULL;
			delete tmp;
		}
	}
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

unsigned int Enemy::getSize()
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
//		new Projectile(_x + 2, _y + this->_size / 2 -1, 'L');
		if (  std::fabs(g_gm.getPlayer().getX() - this->_x) < 7)
		{
			this->_lastshoot = clock();
				
		}


	}
	// onhit()
}

void Enemy::onHit()
{
	//delete this;
}





unsigned int Enemy::getSize(void) const
{
	return (this->_size);
}


bool Enemy::collides(unsigned int x, unsigned int y)
{
	if (x < this->getX())
		return false;
	if (y < this->getY())
		return false;

	int diffx = x - this->getX();
	int diffy = y - this->getY();
	if (diffx > (int)this->getSize())
		return false;
	if (diffy > (int)this->getSize())
		return false;
	char c = this->getDrawMap()[x].c_str()[y];
	if (c != ' ')
		return (true);
	return (false);
}

void	HandleEnemies(void)
{
	t_enemy *tmp = g_gm.enemyList;

	while (tmp != NULL)
	{
		if (tmp->enemy != NULL)
			tmp->enemy->think();
		tmp = tmp->next;
	}
}
