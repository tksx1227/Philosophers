/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:32:00 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/06 11:50:11 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	int				params[5];
	t_philo			*philos;
	t_global_info	info;

	if (parse_args(params, argc, argv))
	{
		print_usage();
		return (1);
	}
	if (init_global_info(&info, params))
		return (1);
	if (init_philos(&info, &philos))
		return (1);
	if (create_philo_processes(philos))
		return (1);
	if (wait_process())
		return (1);
	if (kill_all_process(philos))
		return (1);
	if (destroy_philos_sem(philos) || destroy_global_info_sem(&info))
		return (1);
	if (free_all_philos(&philos))
		return (1);
	return (0);
}
