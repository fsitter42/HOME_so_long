/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:29:05 by fsitter           #+#    #+#             */
/*   Updated: 2025/11/26 16:08:59 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_left(t_windata *win);
void	move_down(t_windata *win);
void	move_right(t_windata *win);
void	move_up(t_windata *win);
void	print_move(void);

void	move_left(t_windata *win)
{
	int	x;
	int	y;

	x = win->mapdata->playerposition_x;
	y = win->mapdata->playerposition_y;
	if (!valid_move(x, y - 1, win->mapdata->map))
		return ;
	if (win->mapdata->map[x][y - 1] == COIN)
		win->mapdata->coin_c--;
	win->mapdata->map[x][y] = BG;
	restore_exit(win->mapdata);
	win->mapdata->map[x][y - 1] = PLAYER;
	win->mapdata->playerposition_y -= 1;
	print_move();
}

void	move_down(t_windata *win)
{
	int	x;
	int	y;

	x = win->mapdata->playerposition_x;
	y = win->mapdata->playerposition_y;
	if (!valid_move(x + 1, y, win->mapdata->map))
		return ;
	if (win->mapdata->map[x + 1][y] == COIN)
		win->mapdata->coin_c--;
	win->mapdata->map[x][y] = BG;
	restore_exit(win->mapdata);
	win->mapdata->map[x + 1][y] = PLAYER;
	win->mapdata->playerposition_x += 1;
	print_move();
}

void	move_right(t_windata *win)
{
	int	x;
	int	y;

	x = win->mapdata->playerposition_x;
	y = win->mapdata->playerposition_y;
	if (!valid_move(x, y + 1, win->mapdata->map))
		return ;
	if (win->mapdata->map[x][y + 1] == COIN)
		win->mapdata->coin_c--;
	win->mapdata->map[x][y] = BG;
	restore_exit(win->mapdata);
	win->mapdata->map[x][y + 1] = PLAYER;
	win->mapdata->playerposition_y += 1;
	print_move();
}

void	move_up(t_windata *win)
{
	int	x;
	int	y;

	x = win->mapdata->playerposition_x;
	y = win->mapdata->playerposition_y;
	if (!valid_move(x - 1, y, win->mapdata->map))
		return ;
	if (win->mapdata->map[x - 1][y] == COIN)
		win->mapdata->coin_c--;
	win->mapdata->map[x][y] = BG;
	restore_exit(win->mapdata);
	win->mapdata->map[x - 1][y] = PLAYER;
	win->mapdata->playerposition_x -= 1;
	print_move();
}

void	print_move(void)
{
	static int	c_moves;

	ft_printf("Moves: %i\n", ++c_moves);
}
