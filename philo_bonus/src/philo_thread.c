/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:28:51 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/08 16:29:10 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*main_routine(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	while (42)
	{
		if (take_two_forks(philo) \
				|| do_eating(philo) \
				|| release_two_forks(philo) \
				|| do_sleeping(philo) \
				|| do_thinking(philo))
			exit(1);
	}
}
