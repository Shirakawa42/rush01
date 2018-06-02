#pragma once

#include <Player.hpp>
#include <Enemy.hpp>



class GameManager
{
	struct t_enemy
	{
		Enemy enemy;
		t_enemy *next;
	};


public:
	GameManager();
	Player &getPlayer() const;
	~GameManager();

private:
	GameManager(GameManager const &source);
	GameManager & operator=(const GameManager & rhs);
	Player player;

};