/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:00:35 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/02 09:48:31 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int				params[5];
	t_global_info	info;
	t_philo			*head;
	pthread_t		observer;

	if ((argc != 5 && argc != 6) || (parse_args(params, argc, argv) == -1))
	{
		print_usage();
		return (1);
	}
	init_global_info(&info, params);
	head = get_philos_circular(&info);
	if (head == NULL)
		return (1);
	if (pthread_create(&observer, NULL, &do_monitoring, head))
		return (1);
	if (start_all_threads(head))
		return (1);
	if (pthread_join(observer, NULL) || join_all_threads(head))
		return (1);
	free_philos_circular(head);
	pthread_mutex_destroy(&info.system_status_mutex);
	return (0);
}
