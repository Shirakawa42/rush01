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
		unsigned int getSize() const;
		bool canShoot(void) const;
		unsigned int getX();
		unsigned int getY();
		unsigned int getSize();
		std::string *getDrawMap();
		void think();
		void onHit();
		bool collides(unsigned int x, unsigned int y);

	private:
		unsigned int _x;
		unsigned int _y;
		double _shootingRate;
		std::string *_drawMap;
		std::clock_t _lastshoot;
		unsigned int _size;
};