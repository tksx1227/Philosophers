/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_semaphore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:55:28 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/10 18:31:13 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_global_info_sem(t_global_info *info)
{
	if (init_sem(&info->forks_sem, FORKS_SEM_NAME, info->n_of_philos) || \
		init_sem(&info->print_sem, PRINT_SEM_NAME, 1) || \
		init_sem(&info->completed_eating_sem, COMPLETED_EATING_SEM_NAME, 0))
		return (1);
	return (0);
}

int	destroy_philos_sem(t_philo *head)
{
	char	*sem_name;
	t_philo	*philo;

	philo = head;
	while (philo != NULL)
	{
		sem_name = get_sem_name(philo->index);
		if (sem_name == NULL)
			return (1);
		if (destroy_sem(&philo->eating_status_sem, sem_name))
			return (1);
		free(sem_name);
		philo = philo->next;
	}
	return (0);
}

int	destroy_global_info_sem(t_global_info *info)
{
	if (destroy_sem(&info->forks_sem, FORKS_SEM_NAME) || \
		destroy_sem(&info->print_sem, PRINT_SEM_NAME) || \
		destroy_sem(&info->completed_eating_sem, COMPLETED_EATING_SEM_NAME))
		return (1);
	return (0);
}

int	init_sem(sem_t **sem, const char *name, int init_val)
{
	if (sem == NULL)
		return (1);
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT, S_IRWXU, init_val);
	if (*sem == SEM_FAILED)
		return (1);
	return (0);
}

int	destroy_sem(sem_t **sem, const char *name)
{
	if (sem == NULL)
		return (1);
	sem_close(*sem);
	sem_unlink(name);
	*sem = NULL;
	return (0);
}
