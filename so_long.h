/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:06:29 by fsitter           #+#    #+#             */
/*   Updated: 2025/12/12 11:58:32 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// includes
# include "libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <mlx.h>

// global MACROS
# define VALIDSIGN "PCE01"
# define PLAYER 'P'
# define COIN 'C'
# define EXIT 'E'
# define BORDER '1'
# define BG '0'
# define TRUE 1
# define FALSE 0
# define EXTENSION ".ber"
# define PIXEL 25
# define IMAGES 5
# define WINNAME "NETVRK Minerunner/Metaverse 2D"
# define RESOX 1920
# define RESOY 1080

# define ESC 65307

// struct to safe mapdata
typedef struct s_mapdata
{
	char		**map;
	int			player_c;
	int			exit_c;
	int			coin_c;
	int			map_width_x;
	int			map_height_y;
	int			playerposition_x;
	int			playerposition_y;
	int			exitposition_x;
	int			exitposition_y;
}				t_mapdata;

// struct to safe image data
typedef struct s_imagedata
{
	void		*img;
	char		*xmp_path;
	int			img_w_x;
	int			img_h_y;
}				t_imagedata;

// struct to safe window
typedef struct s_windata
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_mapdata	*mapdata;
	t_imagedata	*img;
}				t_windata;

// mapstuff.c
int				count_lines(char *mapfile);
char			**make_map(char *mapfile, t_mapdata *data);
int				count_of(char **map, char what_to_find);
char			**free_map(char **map);

// check_and_find.c
int				check_borders(char **map, int xmax, int ymax);
int				check_form(char **map);
int				check_signs(char **map);
void			find_sign(char **map, char to_find, int *x, int *y);

// input_and_all.c
int				check_input(int argc, char *argv);
int				check_map_all(t_mapdata *data);
int				count_all(t_mapdata *data);
void			find_all(t_mapdata *data);

// check_path.c
int				check_path(t_mapdata *data, char *mapfile);
int				fill_mapdata(t_mapdata *data, char *mapfile);
int				fill_count(t_mapdata *data, char **cpy_map, int x, int y);
void			restore_exit(t_mapdata *map);

// game.c
int				start_game(t_mapdata *mapdata, t_windata *win);
void			del_dest_cl(t_windata *win, int code);
void			my_xpm_to_img(t_windata *win);
void			fillwindow(t_windata *win);
void			fillimg(t_windata *win, int i, int j, int nr);

// gamehook.c
int				my_hook(t_windata win);
int				kill_all(t_windata *win);
int				key(int keysym, t_windata *win);
void			end_game(t_windata *win);
int				valid_move(int x, int y, char **map);

// moves.c
void			move_left(t_windata *win);
void			move_down(t_windata *win);
void			move_right(t_windata *win);
void			move_up(t_windata *win);
void			print_move(void);
#endif