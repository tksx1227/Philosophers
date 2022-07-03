/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:00:35 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/03 15:08:55 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int				params[5];
	t_global_info	info;
	t_philo			*head;
	pthread_t		observer;

	if (parse_args(params, argc, argv))
	{
		print_usage();
		return (1);
	}
	if (init_global_info(&info, params))
		return (1);
	if (init_philos_circular(&head, &info))
		return (1);
	if (pthread_create(&observer, NULL, &do_monitoring, head))
		return (1);
	if (start_all_threads(head))
		return (1);
	if (pthread_join(observer, NULL) || join_all_threads(head))
		return (1);
	if (destroy_all_mutex(head) || free_philos_circular(head) || \
			pthread_mutex_destroy(&info.system_status_mutex))
		return (1);
	return (0);
}
