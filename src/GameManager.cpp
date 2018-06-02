#include <GameManager.hpp>
#include <Player.hpp>
#include <Enemy.hpp>


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


