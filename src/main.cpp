#include <string>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <sys/time.h>
#include "GameManager.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

# define H 30
# define W 100

GameManager		g_gm;

void	putStrings(int x, int y, std::string *strings, int size)
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

void	putString(int x, int y, std::string string)
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

void	init_map()
{
	for (int i = 0 ; i < H ; i++)
	{
		wmove(g_gm.win, i, 0);
		wprintw(g_gm.win, "%c", '#');
		wmove(g_gm.win, i, W - 1);
		wprintw(g_gm.win, "%c", '#');
	}
	for (int i = 1 ; i < W ; i++)
	{
		wmove(g_gm.win, 0, i);
		wprintw(g_gm.win, "%c", '#');
		wmove(g_gm.win, H - 1, i);
		wprintw(g_gm.win, "%c", '#');
	}
}

long	getMicrotime()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

void	create_star(int y, double speed)
{
	// fonctionne pas trop, a ameliorer
	wmove(g_gm.win, y, (int)(std::tan(getMicrotime() * speed) * W));
	wprintw(g_gm.win, "%c", '*');
}

int		main()
{
	initscr();
	g_gm.win = newwin(H, W, 0, 0);
	noecho();
	while (1)
	{
		wclear(g_gm.win);
		// c'est ici qu'on affiche des trucs

		create_star(4, 1.0);
		create_star(8, 1.2);
		create_star(12, 0.7);
		create_star(16, 1.35);
		create_star(20, 0.5);
		create_star(24, 1.5);

		////////////////////////////////////
		init_map();
		wrefresh(g_gm.win);
		usleep(50000);
	}
	delwin(g_gm.win);
	endwin();
	return 0;
}
