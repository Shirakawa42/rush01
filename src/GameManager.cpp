#include "Game.hpp"

GameManager::GameManager()
{
	this->enemyList = NULL;
	this->currentTime = clock();
	this->lastTime = clock();
	this->p = NULL;
} 

GameManager::~GameManager()
{
	t_projectiles	*tmp;

	while (p != NULL)
	{
		tmp = p;
		if (p->projectile != NULL)
			delete (p->projectile);
		p = p->next;
		delete (tmp);
	}
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


void 	GameManager::removeEnemy(Enemy *enemy)
{
	t_enemy *tmp = NULL;
	t_enemy *tmp2 = NULL;
	tmp = this->enemyList;
	while (tmp != NULL)
	{
		if (tmp->next && tmp->next->enemy != enemy)
			tmp2 = tmp; // backup for rollback and assigning the next one as next of the past one

		if (tmp->enemy == enemy)
		{
			if (tmp2 == NULL) // first of the list found
			{
				if (tmp->next != NULL)
					this->enemyList = tmp->next;
				else
					this->enemyList = NULL;
			}
			else
				tmp2->next = tmp->next;
			delete tmp->enemy; // dans tous les cas on delete
			delete tmp;
		}
		tmp = tmp->next;
	}
}

void 	GameManager::removeProjectile(Projectile *enemy) // copié collé en mode voleur
{
	t_projectiles *tmp = NULL;
	t_projectiles *tmp2 = NULL;
	tmp = this->p;
	while (tmp != NULL)
	{
		if (tmp->next && tmp->next->projectile != enemy)
			tmp2 = tmp; // backup for rollback and assigning the next one as next of the past one

		if (tmp->projectile == enemy)
		{
			if (tmp2 == NULL) // first of the list found
			{
				if (tmp->next != NULL)
					this->p = tmp->next;
				else
					this->p = NULL;
			}
			else
				tmp2->next = tmp->next;
			delete tmp->projectile; // dans tous les cas on delete
			delete tmp;
		}
		tmp = tmp->next;
	}
}

