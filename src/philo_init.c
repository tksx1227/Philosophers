/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:37:25 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/01 15:28:40 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		init_mutex(t_philo *philo);
static void		init_pthread(t_philo *philo);
static t_philo	*get_new_philo(int index, t_rule *rule);
static int		add_philo_to_end_of_circular(int index, \
		t_rule *rule, t_philo *head);

t_philo	*get_philos_circular(t_rule *rule)
{
	int		i;
	t_philo	*head;

	if (rule->n_of_philos < 1)
		return (NULL);
	i = 1;
	head = get_new_philo(1, rule);
	if (head == NULL)
		return (NULL);
	head->prev = head;
	head->next = head;
	while (i < rule->n_of_philos)
	{
		if (add_philo_to_end_of_circular(i + 1, rule, head) != 0)
		{
			free_philos_circular(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}

static int	add_philo_to_end_of_circular(int index, t_rule *rule, t_philo *head)
{
	t_philo	*philo;

	philo = get_new_philo(index, rule);
	if (philo == NULL)
		return (1);
	philo->prev = head->prev;
	philo->next = head;
	head->prev->next = philo;
	head->prev = philo;
	return (0);
}

static t_philo	*get_new_philo(int index, t_rule *rule)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo->index = index;
	philo->status = THINKING;
	philo->exist_my_fork = true;
	philo->prev = NULL;
	philo->next = NULL;
	philo->eat_count = 0;
	philo->last_ate_at = get_timestamp_ms();
	philo->rule = rule;
	init_mutex(philo);
	init_pthread(philo);
	if (philo->fork_mutex == NULL || philo->thread == NULL)
	{
		free(philo->fork_mutex);
		free(philo->thread);
		free(philo);
		return (NULL);
	}
	return (philo);
}

static void	init_mutex(t_philo *philo)
{
	pthread_mutex_t	*mutex;

	philo->fork_mutex = NULL;
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
		return ;
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		free(mutex);
		return ;
	}
	philo->fork_mutex = mutex;
}

static void	init_pthread(t_philo *philo)
{
	pthread_t	*thread;

	philo->thread = NULL;
	thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (thread == NULL)
		return ;
	if (pthread_create(thread, NULL, &main_loop, philo) != 0)
	{
		free(thread);
		return ;
	}
	philo->thread = thread;
}
