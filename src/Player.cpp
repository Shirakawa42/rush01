#include "Game.hpp"

Player::Player() : _lives(3), _x(5), _y(H / 2) // a changer
{

}
Player::~Player()
{

}
unsigned int Player::getX(void) const
{
	return (_y);
}
unsigned int Player::getY(void) const
{
	return (_x);
} 
  
unsigned int Player::getLives(void)
{
	return (_lives);
}

static bool checkcollision(int x, int y, Enemy *enemy)
{
	if (x < enemy->getX())
		return false;
	if (y < enemy->getY())
		return false;

	int diffx = x - enemy->getX();
	int diffy = y - enemy->getY();
	if (diffx > enemy->getSize())
		return false;
	if (diffy > enemy->getSize())
		return false;
	char c = enemy->getDrawMap()[x].c_str()[y];
	if (c != ' ')
		return (true);
	return (false);

}


void Player::think()
{
	if (this->_isSpawnProtected)
	{
		time_t curtime = std::time(0);
		if (curtime - _SpawnProtectedTime >= 2) // hardcoded
			this->_isSpawnProtected = false;
	}
	else
	{
		t_enemy *tmp;
		tmp = g_gm.getEnemyList();
		while (tmp != NULL)
		{
			if (checkcollision(this->_x, this->_y, tmp->enemy))
			{
				this->onHit();
				break;
			}

			tmp = tmp->next;
		}

	}
}

void Player::putPlayer(void)
{
	wmove(g_gm.win, _y, _x);
	wprintw(g_gm.win, "%c", SHIP);
}

void Player::respawn(void)
{
	_y = H / 2;
	_x = 5;

	wmove(g_gm.win, _y, _x);
	wprintw(g_gm.win, "%c", SHIP);
}

void Player::movePlayer(void)
{
	int		ch;

	nodelay(stdscr, TRUE);
	ch = getch();

	if (ch == 115)
	{
		if (_y < H - 2)
			_y++;
	}
	else if (ch == 122)
	{
		if (_y > 1)
			_y--;
	}
	else if (ch == 100)
	{
		if (_x < W - 2)
			_x++;
	}
	else if (ch == 113)
	{
		if (_x > 1)
			_x--;
	}
	else if (ch == 32)
	{
		spawnProjectile(_x + 1, _y, 'R');
	}
}

void Player::onHit(void)
{
	if (this->_lives == 0)
	{
		//endgame
		return;
	}
	this->_lives--;
	this->respawn();
}


Player::Player(Player const &rhs)
{
	*this = rhs;
}


Player & Player::operator=(const Player & source)
{
	(void)source;
	return (*this);
}

bool Player::isSpawnProtected(void) const
{
	return (this->_isSpawnProtected);
}

bool Player::canShoot(void) const
{
	return (this->_canShoot);
}

void Player::killed(void) // not permakilled
{
	this->_isSpawnProtected = true;
	this->_SpawnProtectedTime = std::time(0);
}
