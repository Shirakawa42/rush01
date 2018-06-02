#pragma once

#include <Player.hpp>
#include <Enemy.hpp>
#include <curses.h>
#include <ctime>
#include "Game.hpp"

struct t_enemy
{
	Enemy *enemy;
	t_enemy *next;
};

typedef struct	s_projectiles
{
	Projectile		*projectile;
	s_projectiles	*next;
}				t_projectiles;

class GameManager
{



public:
	GameManager();
	Player &getPlayer();
	~GameManager();
	void popEnemy(unsigned int type);
	t_enemy *getEnemyList();
	WINDOW *win;
	double frameTime();
	void updateTime();
	void	putStrings(int x, int y, std::string *strings, int size);
	void	putString(int x, int y, std::string string);
	void 	removeEnemy(Enemy *enemy);
	t_projectiles	*p;

private:
	GameManager(GameManager const &source);
	GameManager & operator=(const GameManager & rhs);
	Player player;
	t_enemy *enemyList;
	std::clock_t lastTime;
	std::clock_t currentTime;
};
