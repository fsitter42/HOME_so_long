/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:32:49 by fsitter           #+#    #+#             */
/*   Updated: 2025/12/12 12:18:40 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		start_game(t_mapdata *mapdata, t_windata *win);
void	del_dest_cl(t_windata *win, int code);
void	my_xpm_to_img(t_windata *win);
void	fillwindow(t_windata *win);
void	fillimg(t_windata *win, int i, int j, int nr);
void	my_hook2(t_windata win);

int	start_game(t_mapdata *mapdata, t_windata *win)
{
	t_imagedata *img = ft_calloc(5, sizeof(t_imagedata)); // SAFE allocation
	if (!img)
		return (FALSE);
	win->mapdata = mapdata;
	win->img = img;
	win->win_ptr = NULL;
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
	{
		ft_printf("Error: mlx_init() failed - check X11/DISPLAY\n");
		del_dest_cl(win, 1);
		return (FALSE);
	}
	my_xpm_to_img(win);
	win->win_ptr = mlx_new_window(win->mlx_ptr, mapdata->map_width_x * PIXEL,
			mapdata->map_height_y * PIXEL, WINNAME);
	if (!win->win_ptr)
	{
		ft_printf("Error: mlx_new_window() failed\n");
		del_dest_cl(win, 1);
		return (FALSE);
	}
	fillwindow(win);
	ft_printf("DEBUG: mlx=%p win=%p img=%p map=%p w=%d h=%d\n", win->mlx_ptr,
		win->win_ptr, win->img, win->mapdata, mapdata->map_width_x,
		mapdata->map_height_y);
	if (!win->mlx_ptr || !win->win_ptr || !win->img || !win->mapdata)
	{
		ft_printf("NULL pointer detected!\n");
		return (1);
	}
	my_hook2(*win);
	if (mlx_loop(win->mlx_ptr))
		return (del_dest_cl(win, 1), FALSE);
	del_dest_cl(win, 0);
	return (TRUE);
}

void	del_dest_cl(t_windata *win, int code)
{
	int	i;

	i = 0;
	free_map(win->mapdata->map);
	while (i < IMAGES)
	{
		if (win->img[i].img && win->mlx_ptr)
		{
			mlx_destroy_image(win->mlx_ptr, win->img[i].img);
			win->img[i].img = NULL;
		}
		i++;
	}
	if (win->win_ptr)
	{
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		win->win_ptr = NULL;
	}
	if (win->mlx_ptr)
	{
		mlx_destroy_display(win->mlx_ptr);
		free(win->mlx_ptr);
		win->mlx_ptr = NULL;
	}
	exit(code);
}

void	my_xpm_to_img(t_windata *win)
{
	win->img[0].img = mlx_xpm_file_to_image(win->mlx_ptr, "./textures/BG.xpm",
			&win->img->img_w_x, &win->img->img_h_y);
	win->img[1].img = mlx_xpm_file_to_image(win->mlx_ptr, "./textures/W.xpm",
			&win->img->img_w_x, &win->img->img_h_y);
	win->img[2].img = mlx_xpm_file_to_image(win->mlx_ptr, "./textures/P.xpm",
			&win->img->img_w_x, &win->img->img_h_y);
	win->img[3].img = mlx_xpm_file_to_image(win->mlx_ptr, "./textures/NV.xpm",
			&win->img->img_w_x, &win->img->img_h_y);
	win->img[4].img = mlx_xpm_file_to_image(win->mlx_ptr, "./textures/E.xpm",
			&win->img->img_w_x, &win->img->img_h_y);
	if (!win->img[0].img || !win->img[1].img || !win->img[2].img
		|| !win->img[3].img || !win->img[4].img)
	{
		ft_putstr_fd("Error:\nIn creating images!\n", 2);
		del_dest_cl(win, 1);
		return ;
	}
}

void	fillwindow(t_windata *win)
{
	int	i;
	int	j;

	i = 0;
	while (win->mapdata->map[i])
	{
		j = 0;
		while (win->mapdata->map[i][j])
		{
			if (win->mapdata->map[i][j] == BG)
				fillimg(win, i, j, 0);
			else if (win->mapdata->map[i][j] == BORDER)
				fillimg(win, i, j, 1);
			else if (win->mapdata->map[i][j] == PLAYER)
				fillimg(win, i, j, 2);
			else if (win->mapdata->map[i][j] == COIN)
				fillimg(win, i, j, 3);
			else if (win->mapdata->map[i][j] == EXIT)
				fillimg(win, i, j, 4);
			j++;
		}
		i++;
	}
}

void	fillimg(t_windata *win, int i, int j, int nr)
{
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img[nr].img, j
		* PIXEL, i * PIXEL);
}

void	my_hook2(t_windata win)
{
	ft_printf("HOOK CALLED with param=%p\n", &win);
	mlx_hook(win.win_ptr,2, 1, key, &win);
	mlx_hook(win.win_ptr, 17, 0, kill_all, &win);
	mlx_loop(win.mlx_ptr);
}
