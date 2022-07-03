/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:53:41 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/03 15:36:45 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_putstr_fd(char const *s, int fd);

void	msleep(unsigned int ms)
{
	usleep(ms * 1000);
}

int	init_global_info(t_global_info *info, int params[])
{
	info->n_of_philos = params[0];
	info->time_to_die = params[1];
	info->time_to_eat = params[2];
	info->time_to_sleep = params[3];
	info->n_of_times_each_philo_must_eat = params[4];
	info->is_system_stopped = false;
	if (pthread_mutex_init(&info->system_status_mutex, NULL))
		return (1);
	return (0);
}

t_timestamp	get_timestamp_us(void)
{
	t_timestamp		us;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	us = tv.tv_sec * 1000000 + tv.tv_usec;
	return (us);
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

static void	ft_putstr_fd(char const *s, int fd)
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
