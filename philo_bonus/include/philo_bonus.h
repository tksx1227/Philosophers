/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:28:52 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/06 11:50:37 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef long long		t_timestamp;

/* Utils */
int			parse_args(int params[], int argc, char **argv);
int			msleep_precise(unsigned int ms);
void		print_usage(void);
t_timestamp	get_current_time_us(void);

#endif
