/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamehook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 00:37:13 by fsitter           #+#    #+#             */
/*   Updated: 2025/12/14 14:56:44 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int locking = 0;

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

int press_ctrlaltl() 
{
	ft_printf("works\n");
    Display *d = XOpenDisplay(NULL);
    if (!d) 
	{
		ft_printf("❌ Display failed\n");
		return 1;
	}
    
    KeyCode ctrl = XKeysymToKeycode(d, XStringToKeysym("Control_L"));
    KeyCode alt = XKeysymToKeycode(d, XStringToKeysym("Alt_L"));
    KeyCode lkey = XKeysymToKeycode(d, XStringToKeysym("l"));
    
    XTestFakeKeyEvent(d, ctrl, True, 0);
    XTestFakeKeyEvent(d, alt, True, 0);
    XTestFakeKeyEvent(d, lkey, True, 0);
    usleep(50000);

    XTestFakeKeyEvent(d, lkey, False, 0);
    XTestFakeKeyEvent(d, alt, False, 0);
    XTestFakeKeyEvent(d, ctrl, False, 0);
	ft_printf("ALL UP - Lockscreen should trigger!\n");
    
    XCloseDisplay(d);
    return 0;
}

int	lockscreen(int keysym, t_windata *win)
{
	(void) keysym;
	if (locking)
		return (0);
	locking  = 1;
	press_ctrlaltl();
	fillwindow(win);
	end_game(win);
	del_dest_cl(win, 0);
	locking = 0;
	return (0);
}
// choose and call the one you want my_hook rename the others
//school ori
int	my_hook_ori(t_windata win)
{
	mlx_hook(win.win_ptr, 2, 1L << 0, key, &win);
	mlx_hook(win.win_ptr, 17, 1L << 17, kill_all, &win);
	return (0);
}
// school with lock
int	my_hook_ori_lock(t_windata win)
{
	mlx_hook(win.win_ptr, 2, 1L << 0, lockscreen, &win);
	mlx_hook(win.win_ptr, 17, 1L << 17, lockscreen, &win);
	return (0);
}

// home with lockscreen
int	my_hook(t_windata win)
{
	mlx_hook(win.win_ptr, 2, 1L << 0, lockscreen, &win);
	mlx_hook(win.win_ptr, 17, 1L << 17, lockscreen, &win);
	mlx_loop(win.mlx_ptr); //delete for school
	return (0);
}
// ori home
void	my_hook_home(t_windata win)
{
	mlx_hook(win.win_ptr,2, 1, key, &win);
	mlx_hook(win.win_ptr, 17, 0, kill_all, &win);
	mlx_loop(win.mlx_ptr);
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
