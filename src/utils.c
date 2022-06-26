/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:53:41 by ttomori           #+#    #+#             */
/*   Updated: 2022/06/26 22:34:24 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_info(t_philo_info *philo_info, int params[])
{
	philo_info->n_of_philos = params[0];
	philo_info->time_to_die = params[1];
	philo_info->time_to_eat = params[2];
	philo_info->time_to_sleep = params[3];
	philo_info->n_of_times_each_philo_must_eat = params[4];
}

t_timestamp	get_timestamp_ms(void)
{
	long long		ms;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit(1);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

void	ft_putstr_fd(char const *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = 0;
	while (s[len] != '\0')
		len++;
	while (INT_MAX < len)
	{
		write(fd, s, INT_MAX);
		s += INT_MAX;
		len -= INT_MAX;
	}
	write(fd, s, len);
}

void	print_usage(void)
{
	ft_putstr_fd("Usage: philo <NUMBER_OF_PHILOSOPHERS> <TIME_TO_DIE> "
		"<TIME_TO_EAT>\n\t<TIME_TO_SLEEP> "
		"[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT]\n\n",
		STDERR_FILENO);
	ft_putstr_fd("The explanation of each argument is:\n",
		STDERR_FILENO);
	ft_putstr_fd("  - NUMBER_OF_PHILOSOPHERS: "
		"The number of philosophers and also the number of forks.\n",
		STDERR_FILENO);
	ft_putstr_fd("  - TIME_TO_DIE: "
		"The time it takes for the philosopher to die.\n",
		STDERR_FILENO);
	ft_putstr_fd("  - TIME_TO_EAT: "
		"The time it takes for a philosopher to eat.\n",
		STDERR_FILENO);
	ft_putstr_fd("  - TIME_TO_SLEEP: "
		"The time a philosopher will spend sleeping.\n",
		STDERR_FILENO);
	ft_putstr_fd("  - NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT: "
		"The number of meals each philosopher needs to stop the simulation.\n",
		STDERR_FILENO);
}
