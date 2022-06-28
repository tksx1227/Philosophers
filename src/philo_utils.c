/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:47:25 by ttomori           #+#    #+#             */
/*   Updated: 2022/06/28 23:51:19 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*main_loop(void *content)
{
	return (NULL);
}

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
	philo->updated_at = get_timestamp_ms();
	if (pthread_create(philo->thread, NULL, &main_loop, NULL) != 0)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}
