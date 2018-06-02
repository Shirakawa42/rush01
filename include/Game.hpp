#pragma once

# define GAME_HPP
# define W 100
# define H 30
# define SHIP 'D'

#include <string>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <sys/time.h>
#include "GameManager.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include <Star.hpp>

extern GameManager		g_gm;
