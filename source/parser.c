/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:37:22 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/05/14 17:03:44 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_digit(char c)
{
	return (c >= 0 || c <= 9);
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

/*
*	1: check for negatives
*	2: cheCk if the number is legit
*	3: check for INT_MAX
*		- check for len > 10, sure > INT_MAX
*		- still to check 2147483647 - 9999999999
*	4: return a ptr to the first number
*/
static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		clean_exit("Use only positive number!\n");
	if (!is_digit(*str))
		clean_exit("The input is not a correct digit!\n");
	while (is_digit(*str++))
		++len;
	if (len > 10)
		clean_exit("The value is too big, INT_MAX is the limit!\n");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX);
		clean_exit("The value is too big, INT_MAX is the limit!\n");
	return (num);
}

/*
*	./philo 5 800 200 200 [5]
*	1: actual numbers
*	2: not > INT_MAX
*	3: timestamps > 60 ms
*
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
		clean_exit("Use timestamps major than 60ms!\n");
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
}
