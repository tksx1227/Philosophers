/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 00:25:01 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/07 00:25:07 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philo	*get_new_philo(int index, t_global_info *info);

int	init_philos(t_global_info *info, t_philo **head_p)
{
	int		index;
	t_philo	*philo;

	if (info->n_of_philos < 1)
		return (1);
	*head_p = get_new_philo(1, info);
	if (*head_p == NULL)
		return (1);
	index = 2;
	philo = *head_p;
	while (index <= info->n_of_philos)
	{
		philo->next = get_new_philo(index, info);
		if (philo->next == NULL)
		{
			free_all_philos(head_p);
			return (1);
		}
		philo = philo->next;
		index++;
	}
	return (0);
}

int	free_all_philos(t_philo **head_p)
{
	t_philo	*tmp;
	t_philo	*philo;

	if (head_p == NULL)
		return (1);
	philo = *head_p;
	while (philo != NULL)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
	*head_p = NULL;
	return (0);
}

static t_philo	*get_new_philo(int index, t_global_info *info)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->index = index;
	philo->eat_count = 0;
	philo->next = NULL;
	philo->last_ate_at_us = 0;
	philo->pid = INITIAL_PID;
	philo->info = info;
	return (philo);
}
