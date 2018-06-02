#pragma once

#include <ctime>

class Player {
	public:
		Player();
		~Player();

		unsigned int getX(void) const;
		unsigned int getY(void) const;
		unsigned int getLives(void);
		float	getProjectileSpeed(void) const;
		bool isSpawnProtected(void) const;
		bool canShoot(void) const;
		void think(void);
		void killed(void);
		void onHit(void);
		void respawn(void);
		void putPlayer(void);
		void movePlayer(void);
		float cooldown;
		float realX;
		float realY;
		float speed;
		bool right;
		bool left;
		bool up;
		bool down;
		bool shooting;

	private:
		unsigned int _lives;
		unsigned int _x;
		unsigned int _y;
		float		_projectile_speed;
		float _firerate;
		Player(Player const &source);
		Player & operator=(const Player & rhs);
		bool _isSpawnProtected;
		std::time_t _SpawnProtectedTime;
		std::time_t _lastshoot;
		bool _canShoot;
};

void	handlePlayer(void);
