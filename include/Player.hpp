#pragma once

#include <ctime>

class Player {
	public:
		Player();
		~Player();

		unsigned int getX(void) const;
		unsigned int getY(void) const;
		unsigned int getLives(void);
		bool isSpawnProtected(void) const;
		bool canShoot(void) const;
		void think(void);
		void killed(void);
		void onHit(void);
		void respawn(void);

	private:
		unsigned int _lives;
		unsigned int _x;
		unsigned int _y;
		Player(Player const &source);
		Player & operator=(const Player & rhs);
		bool _isSpawnProtected;
		std::time_t _SpawnProtectedTime;
		std::time_t _lastshoot;
		bool _canShoot;
};

