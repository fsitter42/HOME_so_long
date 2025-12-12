/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamehook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:37:13 by fsitter           #+#    #+#             */
/*   Updated: 2025/11/28 15:13:41 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		my_hook(t_windata win);
int		kill_all(t_windata *win);
int		key(int keysym, t_windata *win);
void	end_game(t_windata *win);
int		valid_move(int x, int y, char **map);

int	kill_all(t_windata *win)
{
	del_dest_cl(win, 0);
	return (0);
}

int	key(int keysym, t_windata *win)
{
	if (keysym == ESC)
	{
		kill_all(win);
		return (0);
	}
	if (keysym == 'a')
		move_left(win);
	if (keysym == 's')
		move_down(win);
	if (keysym == 'd')
		move_right(win);
	if (keysym == 'w')
		move_up(win);
	fillwindow(win);
	end_game(win);
	return (0);
}

int	my_hook(t_windata win)
{
	mlx_hook(win.win_ptr, 2, 1L << 0, key, &win);
	mlx_hook(win.win_ptr, 17, 1L << 17, kill_all, &win);
	return (0);
}

void	end_game(t_windata *win)
{
	int	ex;
	int	ey;
	int	px;
	int	py;

	ex = win->mapdata->exitposition_x;
	ey = win->mapdata->exitposition_y;
	px = win->mapdata->playerposition_x;
	py = win->mapdata->playerposition_y;
	if (!win->mapdata->coin_c && ex == px && ey == py)
		del_dest_cl(win, 0);
	return ;
}

int	valid_move(int x, int y, char **map)
{
	if (map[x][y] == BORDER)
		return (FALSE);
	return (TRUE);
}
