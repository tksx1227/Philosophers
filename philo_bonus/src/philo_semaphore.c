/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_semaphore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:55:28 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/09 22:55:34 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	destroy_all_sem(t_global_info *info)
{
	if (destroy_sem(&info->forks_sem, FORKS_SEM_NAME) || \
		destroy_sem(&info->print_sem, PRINT_SEM_NAME) || \
		destroy_sem(&info->completed_eating_sem, COMPLETED_EATING_SEM_NAME))
		return (1);
	return (0);
}

int init_sem(sem_t **sem, const char *name, int init_val)
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
