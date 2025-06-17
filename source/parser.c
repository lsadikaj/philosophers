/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:37:22 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/17 15:08:21 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}


// Vérifie si une chaîne représente un nombre valide
// Renvoie un pointeur vers le début du nombre
static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	number = str;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		ft_exit("Use only positive number!");
	if (!is_digit(*str))
		ft_exit("The input is not a correct digit!");
	number = str;
	while (is_digit(*str))
	{
		++str;
		++len;
	}
	if (len > 10)
		ft_exit("The value is too big, INT_MAX is the limit!");
	return (number);
}

// Convertit une chaîne en long <= INT_MAX
static long	ft_atol(const char *str)
{
	long		num;
	const char	*s;

	num = 0;
	s = valid_input(str);
	while (is_digit(*s))
		num = (num * 10) + (*s++ - '0');
	if (num > INT_MAX)
		ft_exit("The value is too big, INT_MAX is the limit!");
	return (num);
}

// Analyse les arguments d'entrée et initialise la table
void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		ft_exit("Use timestamps major than 60ms!");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
}
