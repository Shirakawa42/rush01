#include "Game.hpp"

Projectile::Projectile() : _x(1), _y(1), _direction('R'), realX(1.0f), realY(1.0f), speed(8.0f)
{
	t_projectiles	*tmp;

	if (g_gm.p == NULL)
	{
		g_gm.p = new (t_projectiles);
		g_gm.p->projectile = this;
		g_gm.p->next = NULL;
		return;
	}
	tmp = g_gm.p;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new (t_projectiles);
	tmp->next->projectile = this;
	tmp->next->next = NULL;
}


Projectile::Projectile(int x, int y, char direction) : _x(x), _y(y), _direction(direction),  speed(8.0f)
{
	t_projectiles	*tmp;

	if (g_gm.p == NULL)
	{
		g_gm.p = new (t_projectiles);
		g_gm.p->projectile = this;
		g_gm.p->next = NULL;
		return;
	}
	tmp = g_gm.p;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new (t_projectiles);
	tmp->next->projectile = this;
	tmp->next->next = NULL;
	realX = (double)x;
	realY = (double)y;

}

Projectile::~Projectile()
{
	t_projectiles	*tmp;
	t_projectiles	*prev;

	prev = NULL;
	tmp = g_gm.p;
	while (tmp != NULL && tmp->projectile != this)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp != NULL && tmp->projectile == this)
	{
		//delete tmp->projectile; // pas de boucle infinie svp les enfants
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
	else
		exit(0);
}

Projectile::Projectile( const Projectile & cpy )
{
	*this = cpy;
}

Projectile &	Projectile::operator = ( const Projectile & cpy )
{
	(void)cpy;
	return *this;
}

/*Projectile::Projectile(int x, int y, char direction, float s)
{
	_x = x;
	_y = y;
	_direction = direction;
	speed = s;
	realX = (float)x;
	realY = (float)y;
}*/

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

void	Projectile::move()
{
	if (_direction == 'R')
	{
		realX += speed * g_gm.frameTime();
		_x = (int)realX;
	}
	else if (_direction == 'L')
	{
		realX -= speed * g_gm.frameTime();
		_x = (int)realX;
	}
	wmove(g_gm.win, _y, _x);
	wprintw(g_gm.win, "%c", '-');
}

void	HandleProjectiles(void)
{
	t_projectiles	*tmp;

	tmp = g_gm.p;
	while (tmp != NULL)
	{
		if (tmp->projectile != NULL)
		{
			tmp->projectile->move();
			if (tmp->projectile->getX() >= W || tmp->projectile->getX() <= 0)
				delete tmp->projectile;
			break;
		}
		tmp = tmp->next;
	}
}
