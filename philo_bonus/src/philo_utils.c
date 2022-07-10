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

char	*get_sem_name(int index)
{
	size_t	len;
	int		buf_size;
	char	*name;
	char	*index_str;

	buf_size = 128;
	name = (char *)malloc(sizeof(char) * buf_size);
	if (name == NULL)
		return (NULL);
	memset(name, 0, buf_size);
	index_str = ft_itoa(index);
	if (index_str == NULL)
	{
		free(name);
		return (NULL);
	}
	len = ft_strlen(PHILO_SEM_NAME_TEMPLATE);
	ft_strcpy(name, PHILO_SEM_NAME_TEMPLATE);
	ft_strcpy(name + len, index_str);
	free(index_str);
	return (name);
}

static t_philo	*get_new_philo(int index, t_global_info *info)
{
	char	*sem_name;
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
	sem_name = get_sem_name(philo->index);
	if (sem_name == NULL || init_sem(&philo->eating_status_sem, sem_name, 1))
	{
		free(sem_name);
		free(philo);
		return (NULL);
	}
	free(sem_name);
	return (philo);
}
