/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:18:54 by fsitter           #+#    #+#             */
/*   Updated: 2025/12/01 18:10:19 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		check_path(t_mapdata *data, char *mapfile);
int		fill_mapdata(t_mapdata *data, char *mapfile);
int		fill_count(t_mapdata *data, char **cpy_map, int x, int y);
void	restore_exit(t_mapdata *map);

int	check_path(t_mapdata *data, char *mapfile)
{
	char	**map_copy;

	map_copy = make_map(mapfile, data);
	if (fill_count(data, map_copy, data->playerposition_x,
			data->playerposition_y) == FALSE)
	{
		map_copy = free_map(map_copy);
		data->map = free_map(data->map);
		ft_putstr_fd("Error:\nInvalid path!\n", 2);
		return (FALSE);
	}
	map_copy = free_map(map_copy);
	return (TRUE);
}

int	fill_mapdata(t_mapdata *data, char *mapfile)
{
	data->map = make_map(mapfile, data);
	if (!data->map)
		return (FALSE);
	if (data->map_width_x > RESOX / PIXEL || data->map_height_y > RESOY / PIXEL)
	{
		data->map = free_map(data->map);
		ft_putstr_fd("Error:\nMap too big!\n", 2);
		return (FALSE);
	}
	if (check_map_all(data) == FALSE)
	{
		data->map = free_map(data->map);
		return (FALSE);
	}
	if (count_all(data) == FALSE)
	{
		data->map = free_map(data->map);
		return (FALSE);
	}
	find_all(data);
	return (TRUE);
}

int	fill_count(t_mapdata *data, char **cpy_map, int x, int y)
{
	static int	coin;
	static int	exit;

	if ((y < 0) || (x < 0) || (x > data->map_height_y - 1)
		|| (y > data->map_width_x - 1) || (cpy_map[x][y] == '1')
		|| (cpy_map[x][y] == '9'))
		return (0);
	if (cpy_map[x][y] == COIN)
		coin++;
	if (cpy_map[x][y] == EXIT)
		exit++;
	cpy_map[x][y] = '9';
	fill_count(data, cpy_map, x, y - 1);
	fill_count(data, cpy_map, x, y + 1);
	fill_count(data, cpy_map, x + 1, y);
	fill_count(data, cpy_map, x - 1, y);
	return (data->coin_c == coin && data->exit_c == exit);
}

void	restore_exit(t_mapdata *map)
{
	if (map->map[map->exitposition_x][map->exitposition_y] != PLAYER)
		map->map[map->exitposition_x][map->exitposition_y] = EXIT;
}
