#pragma once

#include "Game.hpp"

class	Projectile
{
	public:
		
		Projectile(int x, int y, char direction, float speed);
		~Projectile();
		Projectile(unsigned int x, unsigned int y, char direction);
		Projectile( const Projectile & );
		Projectile(int x, int y, char direction);
		Projectile &	operator = ( const Projectile & );
		char	getDirection() const;
		unsigned int		getX() const;
		unsigned int		getY() const;
		void	move(void);
		float	realX;
		float	realY;
		float	speed;
	private:
		unsigned int		_x;
		unsigned int		_y;
		char	_direction;
		Projectile();
};

void	spawnProjectile(int x, int y, char direction, float speed);
void	deleteProjectile(Projectile *p);
void	HandleProjectiles(void);
