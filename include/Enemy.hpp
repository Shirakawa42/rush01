#pragma once


#include <string>
#include <ctime>


class Enemy
{



	public:
		Enemy(unsigned int x, unsigned int y, unsigned int size);
		~Enemy();
		Enemy(Enemy const &source);
		Enemy & operator=(const Enemy & rhs);
		size_t getSize() const;
		bool canShoot(void) const;
		unsigned int getX();
		unsigned int getY();
		size_t getSize();
		std::string *getDrawMap();
		void think();
		void onHit();
		bool collides(int x, int y);

	private:
		unsigned int _x;
		unsigned int _y;
		double _shootingRate;
		std::string *_drawMap;
		std::clock_t _lastshoot;
		size_t _size;
};

void	HandleEnemies(void);
