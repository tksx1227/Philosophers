/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:20:16 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/03 15:09:09 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_digit(char *str);
static bool	is_digit_all(int argc, char **argv);
static bool	is_valid_args(int argc, char **argv);
static int	atoi_for_philo(char *str);

int	parse_args(int params[], int argc, char **argv)
{
	int	i;
	int	n;

	if (!is_valid_args(argc, argv))
		return (1);
	i = 1;
	while (i < argc)
	{
		n = atoi_for_philo(argv[i]);
		if (n == -1)
			return (1);
		params[i - 1] = n;
		i++;
	}
	if (argc == 5)
		params[i - 1] = -1;
	return (0);
}

static bool	is_valid_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (false);
	if (!is_digit_all(argc, argv))
		return (false);
	return (true);
}

static bool	is_digit(char *str)
{
	size_t	i;

	if (*str == '\0')
		return (false);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || '9' < str[i])
			return (false);
		i++;
	}
	return (true);
}

static bool	is_digit_all(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	atoi_for_philo(char *str)
{
	size_t		i;
	long long	n;

	if (str[0] == '0' && str[1] != '\0')
		return (-1);
	i = 0;
	n = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		if ((long long)INT_MAX < n)
			return (-1);
		i++;
	}
	return ((int)n);
}
