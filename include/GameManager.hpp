#pragma once

#include <Player.hpp>
#include <Enemy.hpp>

struct t_enemy
{
	Enemy enemy;
	t_enemy *next;
};

class GameManager
{



public:
	GameManager();
	Player &getPlayer();
	~GameManager();
	void popEnemy(unsigned int type);
	t_enemy *getEnemyList();

private:
	GameManager(GameManager const &source);
	GameManager & operator=(const GameManager & rhs);
	Player player;
	t_enemy *enemyList;

};