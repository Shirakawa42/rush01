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
	srand(time(NULL));
	initscr();
	g_gm.win = newwin(H, W, 0, 0);
	noecho();

	Star starmap[NSTARS];
	
	new Enemy(W-5, 5, 2);

	while (1)
	{
		g_gm.updateTime();
		wclear(g_gm.win);
		wmove(g_gm.win, 2, 2);
		wprintw(g_gm.win, "%s%d%s%d", "Score: ", g_gm.getPlayer().score, " | Time: ", (int)g_gm.getPlayer().actual_time);
		HandleProjectiles();
		HandleEnemies();
		// c'est ici qu'on affiche des trucs
		drawStars(starmap);
		g_gm.getPlayer().think();
		
		////////////////////////////////////
		handlePlayer();
		init_map();
		wrefresh(g_gm.win);


	}
	delwin(g_gm.win);
	endwin();
	return 0;
}
