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
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	g_gm.win = newwin(H, W, 0, 0);
	noecho();

	Star starmap[NSTARS];
	time_t lastpop = std::time(0);


	while (g_gm.end == false)
	{
		if (std::time(0) > lastpop + 4)
		{
			new Enemy(W-8, 3 + std::rand()%(H-12), 1+std::rand()%5);
			lastpop = std::time(0);
		} 
		g_gm.updateTime();
		wclear(g_gm.win);
		wmove(g_gm.win, 2, 2);
		wattron(g_gm.win, COLOR_PAIR(1));
		wprintw(g_gm.win, "%s%d%s%d%s%d", "Score: ", g_gm.getPlayer().score,
				" | Time: ", (int)g_gm.getPlayer().actual_time, " | Lives: ",
				g_gm.getPlayer().getLives());
		wattron(g_gm.win, COLOR_PAIR(2));
		HandleProjectiles();
		HandleEnemies(); 
		drawStars(starmap);
		g_gm.getPlayer().think();
		handlePlayer();
		init_map();
		wrefresh(g_gm.win);
	}
	wclear(g_gm.win);
	delwin(g_gm.win);
	endwin();
	std::cout << "YOU LOOSE !" << std::endl;
	return 0;
}
