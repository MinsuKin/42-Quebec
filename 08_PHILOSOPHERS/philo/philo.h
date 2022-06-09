/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:46:21 by minkim            #+#    #+#             */
/*   Updated: 2022/06/04 15:25:32 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	size_t	start_time;
	int	p_cnt;
	int	p_num; //number_of_philosophers;
	size_t	t_die; //time_to_die;
	size_t	t_eat; //time_to_eat;
	size_t	t_sleep; //time_to_sleep;
	int	n_must_eat; //number_of_times_each_philosopher_must_eat;
	int eating_cnt;
	int finish;
}	t_args;

typedef struct s_lock
{
	pthread_mutex_t *chopstick;
}	t_lock;

typedef struct s_phil
{
	t_args *args;
	t_lock lock;
	pthread_t tid;
	int my_num;
	size_t last_eat_time;
}	t_phil;

int	ft_atoi(const char *str);

#endif
