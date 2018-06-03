#include "Game.hpp"

Player::Player() : _lives(3), _x(5), _y(H / 2), _firerate(2.0f), cooldown(0.0f), _projectile_speed(0.1f), realX(5.0f), realY((float)H / 2.0f), speed(1.0f) // a changer, _firerate est le temps entre les attaques
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

float	Player::getProjectileSpeed(void) const
{
	return _projectile_speed;
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

static bool checkProjectileCollision(void)
{
	t_projectiles	*tmp;

	tmp = g_gm.p;
	while (tmp)
	{
		if (tmp->projectile->getX() == g_gm.getPlayer().getX() &&
				tmp->projectile->getY() == g_gm.getPlayer().getY())
			return true;
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
			if (checkcollision(this->_x, this->_y, tmp->enemy))
			{
				this->onHit();
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

	this->down = (ch==115);
	this->up = (ch==122);
	this->right = (ch==100);
	this->left = (ch==113);
	this->shooting = (ch==32);

	/*if (ch == 115) // s
	{
		if (up)
			up = !up;
		else
			down = !down;
	}
	else if (ch == 122) // z
	{
		if (down)
			down = !down;
		else
			up = !up;
	}
	else if (ch == 100) // d
	{
		if (left)
			left = !left;
		else
			right = !right;
	}
	else if (ch == 113) // q
	{
		if (right)
			right = !right;
		else
			left = !left;
	}
	else if (ch == 32) // espace
		shooting = !shooting;*/
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
	if (shooting && cooldown <= 0.0f)
	{
		spawnProjectile(_x + 1, _y, 'R', _projectile_speed);
		cooldown = _firerate;
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

void handlePlayer(void)
{
	g_gm.getPlayer().movePlayer();
	g_gm.getPlayer().putPlayer();
	/*if (g_gm.getPlayer().cooldown > 0.0f)
		g_gm.getPlayer().cooldown -= 1.0f/60.0f;*/
}
