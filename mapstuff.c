/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapstuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:40:27 by fsitter           #+#    #+#             */
/*   Updated: 2025/11/27 11:31:00 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		count_lines(char *mapfile);
char	**make_map(char *mapfile, t_mapdata *data);
int		count_of(char **map, char what_to_find);
char	**free_map(char **map);

int	count_lines(char *mapfile)
{
	int		fd;
	int		line_count;
	char	*a;

	a = NULL;
	fd = open(mapfile, O_RDONLY);
	line_count = 0;
	while (1)
	{
		a = get_next_line(fd);
		if (a == NULL)
			break ;
		line_count++;
		free(a);
	}
	a = NULL;
	close(fd);
	return (line_count);
}

char	**make_map(char *mapfile, t_mapdata *data)
{
	char	**map;
	int		row;
	int		fd;

	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error:\nFilediscriptor\n", 2), NULL);
	data->map_height_y = count_lines(mapfile);
	map = malloc(sizeof(char *) * (data->map_height_y + 1));
	if (!map)
		return (ft_putstr_fd("Error:\nMalloc error\n", 2), NULL);
	row = 0;
	while (row < data->map_height_y)
	{
		map[row] = get_next_line(fd);
		data->map_width_x = (int)ft_strlen(map[row]);
		if (map[row][data->map_width_x - 1] == '\n')
			map[row][data->map_width_x - 1] = '\0';
		row++;
	}
	map[data->map_height_y] = NULL;
	close(fd);
	return (map);
}

int	count_of(char **map, char what_to_find)
{
	int	c_count;
	int	i;
	int	j;

	c_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == what_to_find)
				c_count++;
			j++;
		}
		i++;
	}
	return (c_count);
}

char	**free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (NULL);
}
