/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:53:41 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/08 23:52:04 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_putstr_fd(char const *s, int fd);

int	init_global_info(t_global_info *info, int params[])
{
	info->n_of_philos = params[0];
	info->time_to_die = params[1];
	info->time_to_eat = params[2];
	info->time_to_sleep = params[3];
	info->n_of_times_each_philo_must_eat = params[4];
	info->is_system_stopped = false;
	if (sem_unlink(FORKS_SEM_NAME) || sem_unlink(SYSTEM_STATUS_SEM_NAME))
		return (1);
	info->forks_sem = \
		sem_open(FORKS_SEM_NAME, O_CREAT, O_RDWR, info->n_of_philos);
	if (info->forks_sem == SEM_FAILED)
		return (1);
	info->system_status_sem = \
		sem_open(SYSTEM_STATUS_SEM_NAME, O_CREAT, O_RDWR, 1);
	if (info->system_status_sem == SEM_FAILED)
	{
		sem_close(info->forks_sem);
		sem_unlink(FORKS_SEM_NAME);
		return (1);
	}
	return (0);
}

int	msleep_precise(unsigned int ms)
{
	t_timestamp	end_time_us;
	t_timestamp	left_time_us;

	end_time_us = get_current_time_us() + ms * 1000;
	while (42)
	{
		left_time_us = end_time_us - get_current_time_us();
		if (left_time_us <= 0)
			break ;
		if (usleep(left_time_us / 2))
			return (1);
	}
	return (0);
}

t_timestamp	get_current_time_us(void)
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
