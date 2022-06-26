/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:20:16 by ttomori           #+#    #+#             */
/*   Updated: 2022/06/26 22:47:43 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	atoi_for_philo(char *str);

int	parse_args(int params[], int argc, char **argv)
{
	int	i;
	int	n;

	i = 1;
	while (i < argc)
	{
		n = atoi_for_philo(argv[i]);
		if (n == -1)
			return (-1);
		params[i - 1] = n;
		i++;
	}
	if (argc == 5)
		params[i - 1] = -1;
	return (0);
}

static int	atoi_for_philo(char *str)
{
	int			i;
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
	if (i == 0)
		return (-1);
	return ((int)n);
}
