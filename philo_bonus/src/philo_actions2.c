/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:38:26 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/08 13:43:45 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	release_a_fork(t_philo *philo);
static int	take_a_fork(t_philo *philo);

int	take_two_forks(t_philo *philo)
{
	if (take_a_fork(philo) || take_a_fork(philo))
		return (1);
	return (0);
}

int	release_two_forks(t_philo *philo)
{
	if (release_a_fork(philo) || release_a_fork(philo))
		return (1);
	return (0);
}

static int	take_a_fork(t_philo *philo)
{
	if (sem_wait(philo->info->forks_sem))
		return (1);
	return (print_action(philo->info, TAKE_A_FORK, philo->index));
}

static int	release_a_fork(t_philo *philo)
{
	if (sem_post(philo->info->forks_sem))
		return (1);
	return (0);
}
