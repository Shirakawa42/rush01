#include "Game.hpp"

GameManager	g_gm;

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
/*
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
*/
int		main()
{
	initscr();
	g_gm.win = newwin(H, W, 0, 0);
	noecho();
	Star bite = Star(0.001, 10);
	while (1)
	{
		g_gm.updateTime();
		wclear(g_gm.win);
		// c'est ici qu'on affiche des trucs
		bite.think();
		////////////////////////////////////
		g_gm.getPlayer().movePlayer();
		g_gm.getPlayer().putPlayer();
		init_map();
		wrefresh(g_gm.win);
		usleep(5000);
	}
	delwin(g_gm.win);
	endwin();
	return 0;
}
