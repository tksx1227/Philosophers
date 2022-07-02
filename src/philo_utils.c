/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:47:25 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/02 15:08:38 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_philo(t_philo *philo);

void	free_philos_circular(t_philo *head)
{
	int		i;
	int		n_of_philos;
	t_philo	*philo;
	t_philo	*tmp;

	if (head == NULL)
		return ;
	i = 0;
	philo = head;
	n_of_philos = head->info->n_of_philos;
	while (i < n_of_philos)
	{
		tmp = philo->next;
		free_philo(philo);
		philo = tmp;
		i++;
	}
}

static void	free_philo(t_philo *philo)
{
	pthread_mutex_destroy(&philo->fork_mutex);
	free(philo);
}
