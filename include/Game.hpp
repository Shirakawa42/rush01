#pragma once

# define GAME_HPP
# define W 100
# define H 30
# define SHIP 'D'
# define NSTARS 50

#include <string>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <sys/time.h>
#include "Projectile.hpp"
#include "GameManager.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include <Star.hpp>

extern GameManager		g_gm;
