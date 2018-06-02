#include <GameManager.hpp>
#include <Player.hpp>
#include <Enemy.hpp>


GameManager::GameManager()
{
	this->enemyList = NULL;

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
