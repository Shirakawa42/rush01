#include "Game.hpp"

GameManager::GameManager()
{
	this->enemyList = NULL;
	this->currentTime = clock();
	this->lastTime = clock();
	this->p = NULL;
	this->end = false;
	score = 0;
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
				wmove(this->win, y + i, x + j);
				wprintw(this->win, "%c", strings[i][j]);
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
			wmove(this->win, y, x + j);
			wprintw(this->win, "%c", string[j]);
		}
	}
}

void	GameManager::HandleEnemies(void)
{
	t_enemy *tmp = this->enemyList;
	t_enemy *skp = NULL;

	while (tmp != NULL)
	{
		if (tmp->enemy != NULL)
		{
			if (tmp->enemy->movmentCD <= 0.0f)
			{
				tmp->enemy->randomMovments();
				tmp->enemy->movmentCD = 1.0f;
			}
			if (tmp->enemy->movmentCD >= 0.0f)
				tmp->enemy->movmentCD -= this->frameTime();
			skp = tmp->next;
			tmp->enemy->think();
		}
		tmp = skp;
	}
}


void GameManager::handlePlayer(void)
{
	this->getPlayer().actual_time += this->frameTime();
	this->getPlayer().movePlayer();
	this->getPlayer().putPlayer();
	if (this->getPlayer().cooldown > 0.0f)
		this->getPlayer().cooldown -= this->frameTime();
}



void	GameManager::HandleProjectiles(void)
{
	t_projectiles	*tmp;
	t_projectiles	*tmp2;

	tmp = this->p;
	while (tmp != NULL)
	{
		if (tmp->projectile != NULL)
		{
			tmp2 = tmp->next;
			tmp->projectile->move();
			if (tmp->projectile->getX() >= W || tmp->projectile->getX() <= 0)
				delete tmp->projectile;
			tmp = tmp2;
		}
		else
			tmp = tmp->next;
	}
}