#include <Player.hpp>

#include <ctime>

Player::Player() : _lives(3), _x(50), _y(50) // a changer
{

}
Player::~Player()
{

}
unsigned int Player::getX(void) const
{
	return (_y);
}
unsigned int Player::getY(void) const
{
	return (_x);
} 
  
unsigned int Player::getLives(void)
{
	return (_lives);
}

void Player::think()
{
	if (this->_isSpawnProtected)
	{
		time_t curtime = std::time(0);
		if (curtime - _SpawnProtectedTime >= 2) // hardcoded
			this->_isSpawnProtected = false;
	}
}

void Player::respawn(void)
{

}

void Player::onHit(void)
{
	if (this->_lives == 0)
	{
		//endgame
		return;
	}
	this->_lives--;
	this->respawn();
}


Player::Player(Player const &rhs)
{
	*this = rhs;
}


Player & Player::operator=(const Player & source)
{
	(void)source;
	return (*this);
}

bool Player::isSpawnProtected(void) const
{
	return (this->_isSpawnProtected);
}

bool Player::canShoot(void) const
{
	return (this->_canShoot);
}

void Player::killed(void) // not permakilled
{
	this->_isSpawnProtected = true;
	this->_SpawnProtectedTime = std::time(0);
}
