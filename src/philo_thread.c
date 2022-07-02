/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 09:29:42 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/02 09:40:32 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_all_threads(t_philo *head)
{
	int		i;
	int		n_of_philos;
	t_philo	*philo;

	i = 0;
	philo = head;
	n_of_philos = head->rule->n_of_philos;
	while (i < n_of_philos)
	{
		if (pthread_create(&philo->thread, NULL, &main_loop, philo))
			return (1);
		philo = philo->next;
		i++;
	}
	return (0);
}
