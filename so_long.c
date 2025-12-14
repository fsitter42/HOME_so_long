/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:38:11 by fsitter           #+#    #+#             */
/*   Updated: 2025/12/12 17:19:37 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_mapdata	mapdata;
	t_windata	windata;

	if (!check_input(argc, argv[1]))
		return (-1);
	if (!fill_mapdata(&mapdata, argv[1]))
		return (-1);
	if (!check_path(&mapdata, argv[1]))
		return (-1);
	if (!start_game(&mapdata, &windata))
	{
		ft_printf("Error:\nMLX Error!\n");
		return (-1);
	}
}
