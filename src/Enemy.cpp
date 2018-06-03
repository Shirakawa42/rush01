#include <Enemy.hpp>
#include <Game.hpp>


Enemy::Enemy(unsigned int x, unsigned int y, unsigned int type) : _x(x), _y(y), movmentCD(1.0f)
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

		case 3 :
				this->_size = 5;
				this->_drawMap = new std::string[5];
				this->_drawMap[0] = "     ";
				this->_drawMap[1] = "    0";
				this->_drawMap[2] = "c====";
				this->_drawMap[3] = "    0";
				this->_drawMap[4] = "     ";
				break;
		case 4 :
				this->_size = 9;
				this->_drawMap = new std::string[9];
				this->_drawMap[0] = "    __   ";
				this->_drawMap[1] = "===[__]  ";
				this->_drawMap[2] = " (______)";
				this->_drawMap[4] = "         ";
				this->_drawMap[5] = "         ";
				this->_drawMap[6] = "         ";
				this->_drawMap[7] = "         ";
				this->_drawMap[8] = "         ";
				break;

		case 5 :
				this->_size = 18;
				this->_drawMap = new std::string[18];
				this->_drawMap[0] = "       .--.       ";
				this->_drawMap[1] = " (\\_/)/  _ \\      ";
				this->_drawMap[2] = " (o.o) _(   |____ ";
				this->_drawMap[3] = ".- \".-`----'`"""")";
				this->_drawMap[4] = "             '--` ";
				this->_drawMap[5] = "                  ";
				this->_drawMap[6] = "                  ";
				this->_drawMap[7] = "                  ";
				this->_drawMap[8] = "                  ";
				this->_drawMap[9] = "                  ";
				this->_drawMap[10] = "                  ";
				this->_drawMap[11] = "                  ";
				this->_drawMap[12] = "                  ";
				this->_drawMap[13] = "                  ";
				this->_drawMap[14] = "                  ";
				this->_drawMap[15] = "                  ";
				this->_drawMap[16] = "                  ";
				this->_drawMap[17] = "                  ";
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

void Enemy::randomMovments(void)
{
	int		i = rand() % 4;
	if (i == 0 && _x <= W - 1 - _size)
		_x += 1;
	else if (i == 1 && _x > (W / 2) + _size)
		_x -= 1;
	else if (i == 2 && _y <= H - 1 - _size)
		_y += 1;
	else if (i == 3 && _y > 1 + _size)
		_y -= 1;
}

void Enemy::think()
{
	g_gm.putStrings(this->_x, this->_y, this->_drawMap, this->_size);
	if ((clock() - this->_lastshoot )/CLOCKS_PER_SEC >=this->_shootingRate)
	{
		if (  std::fabs(g_gm.getPlayer().getY() - this->_y) < 7)
		{
			this->_lastshoot = clock();
			int offset = 0;
			if (this->_size == 4 || this->_size == 9)
				offset = 1;
			else if (this->_size == 5)
				offset = 2;
			else if (this->_size == 18)
				offset = 2;
			new Projectile(_x - 1, _y + offset, 'L');
		}
	}
	
	t_projectiles	*tmp = g_gm.p;;
	t_projectiles	*skip;
	while (tmp)
	{
		skip = tmp->next;
		if (tmp->projectile->getDirection() == 'R' && (this->collides(tmp->projectile->getX() ,tmp->projectile->getY())))
		{
			this->onHit();
			delete tmp->projectile;
		}
		tmp = skip;
	}


}

void Enemy::onHit()
{
	g_gm.getPlayer().score += 100;
	delete this;
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
		{
			tmp->enemy->think();
			if (tmp->enemy->movmentCD <= 0.0f)
			{
				tmp->enemy->randomMovments();
				tmp->enemy->movmentCD = 1.0f;
			}
			if (tmp->enemy->movmentCD >= 0.0f)
				tmp->enemy->movmentCD -= g_gm.frameTime();
		}
		tmp = tmp->next;
	}
}
