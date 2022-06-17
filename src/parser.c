/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:20:16 by ttomori           #+#    #+#             */
/*   Updated: 2022/06/18 01:31:38 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	atoi_for_philo(char *str);
static void	print_usage_and_exit(void);

void	parse_args(int params[], int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		params[i - 1] = atoi_for_philo(argv[i]);
		i++;
	}
	if (argc == 5)
		params[i - 1] = -1;
}

static int	atoi_for_philo(char *str)
{
	int			i;
	long long	n;

	if (str[0] == '0' && str[1] != '\0')
		print_usage_and_exit();
	i = 0;
	n = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		if ((long long)INT_MAX < n)
			print_usage_and_exit();
		i++;
	}
	if (i == 0)
		print_usage_and_exit();
	return ((int)n);
}

static void	print_usage_and_exit(void)
{
	print_usage();
	exit(1);
}
