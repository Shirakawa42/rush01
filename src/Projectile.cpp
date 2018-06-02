#include "Game.hpp"

Projectile::Projectile() : _x(1), _y(1), _direction('R'), realX(1.0f), realY(1.0f), speed(1.0f)
{
	
}

Projectile::~Projectile()
{
}

Projectile::Projectile( const Projectile & cpy )
{
	*this = cpy;
}

Projectile &	Projectile::operator = ( const Projectile & cpy )
{
	_x = cpy.getX();
	_y = cpy.getY();
	_direction = cpy.getDirection();
	return *this;
}

Projectile::Projectile(int x, int y, char direction, float s)
{
	_x = x;
	_y = y;
	_direction = direction;
	speed = s;
	realX = (float)x;
	realY = (float)y;
}

char	Projectile::getDirection() const
{
	return _direction;
}

int		Projectile::getX() const
{
	return _x;
}

int		Projectile::getY() const
{
	return _y;
}

void	deleteProjectile(Projectile *p)
{
	t_projectiles	*tmp;
	t_projectiles	*prev;

	prev = NULL;
	tmp = g_gm.p;
	while (tmp && tmp->projectile != p)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp && tmp->projectile == p)
	{
		delete tmp->projectile;
		if (!prev)
		{
			if (tmp->next)
				g_gm.p = tmp->next;
			else
				g_gm.p = NULL;
			delete tmp;
		}
		else
		{
			prev = tmp->next;
			delete tmp;
		}
	}
}

void	spawnProjectile(int x, int y, char direction, float speed)
{
	t_projectiles	*tmp;

	if (g_gm.p == NULL)
	{
		g_gm.p = new (t_projectiles);
		g_gm.p->projectile = NULL;
		g_gm.p->next = NULL;
	}
	tmp = g_gm.p;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->projectile)
	{
		tmp->next = new (t_projectiles);
		tmp->next->projectile = new Projectile(x, y, direction, speed);
		tmp->next->next = NULL;
		tmp->next->projectile = NULL;
	}
	else
	{
		tmp->projectile = new Projectile(x, y, direction, speed);
	}
}

void	Projectile::move()
{
	if (_direction == 'R')
	{
		realX += speed;
		_x = (int)realX;
	}
	else if (_direction == 'L')
	{
		realX -= speed;
		_x = (int)realX;
	}
	wmove(g_gm.win, _y, _x);
	wprintw(g_gm.win, "%c", '-');
}

void	HandleProjectiles(void)
{
	t_projectiles	*tmp;

	tmp = g_gm.p;
	while (tmp)
	{
		if (tmp->projectile != NULL)
		{
			tmp->projectile->move();
			if (tmp->projectile->getX() == W || tmp->projectile->getX() == 0)
				deleteProjectile(tmp->projectile);
		}
		tmp = tmp->next;
	}
}
