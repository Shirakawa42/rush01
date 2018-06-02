#include <GameManager.hpp>
#include <Player.hpp>

GameManager::GameManager()
{

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

