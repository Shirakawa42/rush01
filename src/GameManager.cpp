#include "Game.hpp"

GameManager::GameManager()
{
	this->enemyList = NULL;
	this->currentTime = clock();
	this->lastTime = clock();
} 

GameManager::~GameManager()
{

}


Player &GameManager::getPlayer()
{
	return (this->player);
}


GameManager::GameManager(GameManager const &source)
{
	*this = source;
}

GameManager & GameManager::operator=(const GameManager & rhs)
{
	(void)rhs;
	return (*this);
}


void GameManager::popEnemy(unsigned int type)
{

}

t_enemy *GameManager::getEnemyList()
{
	return (this->enemyList);
}

double GameManager::frameTime()
{
	return ((double)(this->currentTime - this->lastTime)/CLOCKS_PER_SEC);
}

void GameManager::updateTime()
{
	this->lastTime = this->currentTime;
	this->currentTime = clock();
}

void	GameManager::putStrings(int x, int y, std::string *strings, int size)
{
	for (int i = 0 ; i < size ; i++)
	{
		for (int j = 0 ; strings[i][j] ; j++)
		{
			if (strings[i][j] != ' ')
			{
				wmove(g_gm.win, y + i, x + j);
				wprintw(g_gm.win, "%c", strings[i][j]);
			}
		}
	}
}

void	GameManager::putString(int x, int y, std::string string)
{
	for (int j = 0 ; string[j] ; j++)
	{
		if (string[j] != ' ')
		{
			wmove(g_gm.win, y, x + j);
			wprintw(g_gm.win, "%c", string[j]);
		}
	}
}
