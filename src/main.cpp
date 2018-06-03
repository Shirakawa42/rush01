#include "Game.hpp"

GameManager	g_gm;

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


static void drawStars(Star *starmap)
{
	int thinkstar = 0;
	while (thinkstar < NSTARS-1)
	{
		starmap[thinkstar].think();
		thinkstar++;
	}
}

int		main()
{
	initscr();
	g_gm.win = newwin(H, W, 0, 0);
	noecho();

	Star starmap[NSTARS];
	


	while (1)
	{
		g_gm.updateTime();
		wclear(g_gm.win);
		// c'est ici qu'on affiche des trucs
		drawStars(starmap);
		HandleProjectiles();
		////////////////////////////////////
		handlePlayer();
		init_map();
		wrefresh(g_gm.win);
		clock_t clock1 = clock();
		while ((clock() - clock1 )/CLOCKS_PER_SEC + g_gm.frameTime() < 1/60)
		{
		}
	}
	delwin(g_gm.win);
	endwin();
	return 0;
}
