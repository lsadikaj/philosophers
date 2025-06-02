/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:22:18 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/02 18:31:21 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
** Point d'entrée principal du programme
** 1. Vérifie si le nombre d'arguments est correct
** 2. Analyse les arguments et initialise la table
** 3. Lance la simulation du dîner
** 4. Nettoie les ressources à la fin
*/
int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		ft_exit("Wrong input!\nCorrect is: ./philo 5 800 200 200 [5]");
	}
	return (0);
}
