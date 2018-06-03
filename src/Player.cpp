#include "Game.hpp"


Player::Player() :   cooldown(0.0f),realX(5.0f), realY((float)H / 2.0f),    speed(1.0f),    _lives(3),_x(5),_y(H / 2), _projectile_speed(0.1f),  _firerate(0.6f) // a changer, _firerate est le temps entre les attaques
{
	up = false;
	down = false;
	left = false;
	right = false;
	shooting = false;
}
Player::~Player()
{

}
unsigned int Player::getX(void) const
{
	return (_x);
}
unsigned int Player::getY(void) const
{
	return (_y);
} 
  
unsigned int Player::getLives(void)
{
	return (_lives);
}

float	Player::getProjectileSpeed(void) const
{
	return _projectile_speed;
}


static bool checkProjectileCollision(void)
{
	t_projectiles	*tmp;

	tmp = g_gm.p;
	while (tmp)
	{
		if (tmp->projectile->getX() == g_gm.getPlayer().getX() && tmp->projectile->getY() == g_gm.getPlayer().getY() && tmp->projectile->getDirection() == 'L')
		{
			//g_gm.removeProjectile(tmp->projectile);
			delete tmp->projectile;
			return true;
		}
		tmp = tmp->next;
	}
	return false;
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
			if (tmp->enemy->collides(this->_x, this->_y))
			{
				this->onHit();
				delete(tmp->enemy);
				break;
			}
			tmp = tmp->next;
		}
		if (checkProjectileCollision())
			this->onHit();
	}
}

void Player::putPlayer(void)
{
	wmove(g_gm.win, _y, _x);
	wprintw(g_gm.win, "%c", SHIP);
}

void Player::respawn(void)
{
	this->killed();
	_y = H / 2;
	_x = 5;

	realX = _x;
	realY = _y;
}

void Player::movePlayer(void)
{
	int		ch;

	nodelay(stdscr, TRUE);
	ch = getch();

	this->down = (ch==115);
	this->up = (ch==119);
	this->right = (ch==100);
	this->left = (ch==97);
	this->shooting = (ch==32);

	if (up && _y > 1)
	{
		realY -= speed;
		_y = (int)realY;
	}
	if (down && _y < H - 2)
	{
		realY += speed;
		_y = (int)realY;
	}
	if (right && _x < W - 2)
	{
		realX += speed;
		_x = (int)realX;
	}
	if (left && _x > 1)
	{
		realX -= speed;
		_x = (int)realX;
	}
	if (shooting && cooldown <= 0)
	{
		new Projectile(_x + 1, _y, 'R');
		cooldown = _firerate;
	}
}

void Player::onHit(void)
{
	if (this->_lives == 0)
	{
		std::cout << std::endl << "sans rancune tete de prune" <<std::endl;
		exit(0);
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

void handlePlayer(void)
{
	g_gm.getPlayer().movePlayer();
	g_gm.getPlayer().putPlayer();
	if (g_gm.getPlayer().cooldown > 0.0f)
		g_gm.getPlayer().cooldown -= g_gm.frameTime();
}
