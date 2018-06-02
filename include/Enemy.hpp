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

	private:
		unsigned int _x;
		unsigned int _y;
		double _shootingRate;
		std::string *_drawMap;
		std::time_t _lastshoot;
		bool _canShoot;
		size_t _size;
};