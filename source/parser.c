/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:37:22 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/02 18:31:59 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
** Vérifie si un caractère est un chiffre
** Renvoie true si le caractère est entre '0' et '9'
*/
static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
** Vérifie si un caractère est un espace
** Renvoie true si le caractère est un espace, une tabulation, etc.
*/
static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

/*
** Vérifie si une chaîne représente un nombre valide
** 1. Vérifie les nombres négatifs
** 2. Vérifie si les caractères sont des chiffres
** 3. Vérifie si le nombre dépasse INT_MAX
** 4. Renvoie un pointeur vers le début du nombre
*/
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

/*
** Convertit une chaîne en long
** Vérifie si le nombre dépasse INT_MAX
*/
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

/*
** Analyse les arguments d'entrée et initialise la table
** 1. Convertit les arguments en valeurs numériques
** 2. Vérifie que les timestamps sont supérieurs à 60ms
** 3. Initialise le nombre de repas limites (-1 si non spécifié)
*/
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
