/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:51:22 by minkim            #+#    #+#             */
/*   Updated: 2022/07/27 12:38:54 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_pass_time(long long wait_time, t_args *args)
{
	long long	start;
	long long	now;

	start = ft_get_time();
	while (!(args->finish))
	{
		now = ft_get_time();
		if ((now - start) >= wait_time)
			break ;
		usleep(500);
	}
}

int	arg_init_mutex(t_args *args)
{
	int	i;

	if (pthread_mutex_init(&(args->print), NULL))
		return (1);
	args->forks = malloc(sizeof(pthread_mutex_t) * args->p_num);
	if (!(args->forks))
		return (1);
	i = 0;
	while (i < args->p_num)
	{
		if (pthread_mutex_init(&(args->forks[i]), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	args_init(t_args *args, int ac, char **av)
{
	args->p_num = ft_atoi(av[1]);
	args->t_die = ft_atoi(av[2]);
	args->t_eat = ft_atoi(av[3]);
	args->t_sleep = ft_atoi(av[4]);
	args->start_time = ft_get_time();
	if (args->p_num <= 0 || args->t_die <= 0 || \
		args->t_eat <= 0 || args->t_sleep <= 0)
		return (1);
	args->finish = 0;
	args->finished_eat = 0;
	args->n_must_eat = -1;
	if (ac == 6)
	{
		args->n_must_eat = ft_atoi(av[5]);
		if (args->n_must_eat <= 0)
			return (1);
	}
	if (arg_init_mutex(args))
		return (1);
	return (0);
}

int	phil_init(t_args *args, t_phil **phil)
{
	int	i;

	*phil = malloc(sizeof(t_phil) * args->p_num);
	if (!(phil))
		return (1);
	i = 0;
	while (i < args->p_num)
	{
		(*phil)[i].args = args;
		(*phil)[i].my_num = i;
		(*phil)[i].left = i;
		(*phil)[i].right = (i + 1) % args->p_num;
		(*phil)[i].last_time_eat = ft_get_time();
		(*phil)[i].eating_cnt = 0;
		i++;
	}
	return (0);
}
