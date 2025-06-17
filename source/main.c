/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:22:18 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/17 15:03:36 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		simulation_start(&table);
		ft_clean(&table);
	}
	else
	{
		ft_exit("Wrong input!\nCorrect is: ./philo 5 800 200 200 [5]");
	}
	return (0);
}
