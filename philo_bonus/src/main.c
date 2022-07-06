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
	int	params[5];

	if (parse_args(params, argc, argv))
	{
		print_usage();
		return (1);
	}
	return (0);
}
