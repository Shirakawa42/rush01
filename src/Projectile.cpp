#include "Game.hpp"


#include <fstream>
/*Projectile::Projectile() : _x(1), _y(1), _direction('R'), realX(1.0f), realY(1.0f), speed(8.0f)
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
}*/


Projectile::Projectile(unsigned int x, unsigned int y, char direction) :    speed(8.0f), _x(x), _y(y), _direction(direction)
{


	realX = (double)x;
	realY = (double)y;
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

Projectile::~Projectile()
{
	t_projectiles	*tmp;
	t_projectiles	*prev;

	prev = NULL;
	tmp = g_gm.p;
	while (tmp && tmp->projectile != this)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp && tmp->projectile == this)
	{
		//delete tmp->projectile; // pas de boucle infinie svp les enfants
		if (!prev)
		{
			if (tmp->next)
				g_gm.p = tmp->next; // ca rient pas au meme non ?
			else
				g_gm.p = NULL;
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

unsigned int		Projectile::getX() const
{
	return _x;
}

unsigned int		Projectile::getY() const
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
	t_projectiles	*tmp2;

	tmp = g_gm.p;
	while (tmp != NULL)
	{
		if (tmp->projectile != NULL)
		{
			tmp2 = tmp->next;
			tmp->projectile->move();
			if (tmp->projectile->getX() >= W || tmp->projectile->getX() <= 0)
				delete tmp->projectile;
			tmp = tmp2;
		}
		else
			tmp = tmp->next;
	}
}
