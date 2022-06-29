/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:37:25 by ttomori           #+#    #+#             */
/*   Updated: 2022/06/29 18:47:03 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutex(t_philo *philo);

t_philo	*get_new_philo(int index)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->index = index;
	philo->status = INIT;
	philo->exist_my_fork = true;
	philo->next = NULL;
	philo->eat_count = 0;
	philo->last_ate_at = get_timestamp_ms();
	init_mutex(philo);
	if (philo->fork_mutex == NULL)
	{
		free(philo);
		return (NULL);
	}
	if (pthread_create(philo->thread, NULL, &main_loop, NULL) != 0)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}

static void	init_mutex(t_philo *philo)
{
	pthread_mutex_t	*mutex;

	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
	{
		philo->fork_mutex = NULL;
		return ;
	}
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		free(mutex);
		philo->fork_mutex = NULL;
	}
}
