/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_and_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:17:34 by fsitter           #+#    #+#             */
/*   Updated: 2025/12/01 10:31:00 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		check_input(int argc, char *argv);
int		check_map_all(t_mapdata *data);
int		count_all(t_mapdata *data);
void	find_all(t_mapdata *data);

int	check_input(int argc, char *argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error:\nWrong number of argmuents!\n", 2);
		return (FALSE);
	}
	if (!(ft_strnstr(argv, EXTENSION, ft_strlen(argv))))
	{
		ft_putstr_fd("Error:\nWrong fileextension!\n", 2);
		return (FALSE);
	}
	if (ft_strlen(ft_strnstr(argv, EXTENSION, ft_strlen(argv))) != 4)
	{
		ft_putstr_fd("Error:\nWrong fileextension!\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

int	check_map_all(t_mapdata *data)
{
	if (check_form(data->map) == FALSE)
	{
		ft_putstr_fd("Error:\nNot rectangular!\n", 2);
		return (FALSE);
	}
	if (check_borders(data->map, data->map_width_x - 1, data->map_height_y
			- 1) == FALSE)
	{
		ft_putstr_fd("Error:\nBorders!\n", 2);
		return (FALSE);
	}
	if (check_signs(data->map) == FALSE)
	{
		ft_putstr_fd("Error:\nContains non valid signs!\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

int	count_all(t_mapdata *data)
{
	data->player_c = count_of(data->map, PLAYER);
	if (data->player_c != 1)
	{
		ft_putstr_fd("Error:\nWrong number of players!\n", 2);
		return (FALSE);
	}
	data->exit_c = count_of(data->map, EXIT);
	if (data->exit_c != 1)
	{
		ft_putstr_fd("Error:\nWrong number of exits!\n", 2);
		return (FALSE);
	}
	data->coin_c = count_of(data->map, COIN);
	if (data->coin_c < 1)
	{
		ft_putstr_fd("Error:\nNo coin!\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

void	find_all(t_mapdata *data)
{
	find_sign(data->map, PLAYER, &data->playerposition_x,
		&data->playerposition_y);
	find_sign(data->map, EXIT, &data->exitposition_x, &data->exitposition_y);
}
