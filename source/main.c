/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:22:18 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/05/14 11:37:12 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		// Correct input
		// 1: error checking, filling table
		parse_input(&table, av);
		// 2: creating the thing
		data_init(&table);
		//3
		dinner_start(&table);
		//4: No leaks
		clean(&table);
	}
	else
	{
		clean_exit("Wrong input!\nCorrect is: ./philo 5 800 200 200 [5]\n");
	}
}