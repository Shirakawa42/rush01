#pragma once

#include "Game.hpp"

class	Projectile
{
	public:
		Projectile();
		Projectile(int x, int y, char direction, float speed);
		~Projectile();
		Projectile( const Projectile & );
		Projectile &	operator = ( const Projectile & );
		char	getDirection() const;
		int		getX() const;
		int		getY() const;
		void	move(void);
		float	realX;
		float	realY;
		float	speed;
	private:
		int		_x;
		int		_y;
		char	_direction;
};

void	spawnProjectile(int x, int y, char direction, float speed);
void	deleteProjectile(Projectile *p);
void	HandleProjectiles(void);
