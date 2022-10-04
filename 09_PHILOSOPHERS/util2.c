/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:51:22 by minkim            #+#    #+#             */
/*   Updated: 2022/07/27 13:24:30 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_printf(t_args *args, int id, char *msg)
{
	long long	now;

	now = ft_get_time();
	if (now == -1)
		return (-1);
	pthread_mutex_lock(&(args->print));
	if (args->finish == 0)
		printf("%lld %d %s\n", now - args->start_time, id + 1, msg);
	pthread_mutex_unlock(&(args->print));
	return (0);
}

int	ft_philo_action(t_args *args, t_phil *phil)
{
	pthread_mutex_lock(&(args->forks[phil->left]));
	ft_philo_printf(args, phil->my_num, "has taken a fork");
	pthread_mutex_lock(&(args->forks[phil->right]));
	ft_philo_printf(args, phil->my_num, "has taken a fork");
	ft_philo_printf(args, phil->my_num, "is eating");
	phil->last_time_eat = ft_get_time();
	phil->eating_cnt++;
	ft_pass_time((long long)args->t_eat, args);
	pthread_mutex_unlock(&(args->forks[phil->right]));
	pthread_mutex_unlock(&(args->forks[phil->left]));
	return (0);
}

void	*thread(void *argv)
{
	t_args	*args;
	t_phil	*phil;

	phil = argv;
	args = phil->args;
	if (phil->my_num % 2)
		usleep(1000);
	while (args->finish == 0)
	{
		ft_philo_action(args, phil);
		if (args->n_must_eat == phil->eating_cnt)
		{
			args->finished_eat++;
			ft_philo_printf(args, phil->my_num, "is thinking");
			break ;
		}
		ft_philo_printf(args, phil->my_num, "is sleeping");
		ft_pass_time((long long)args->t_sleep, args);
		ft_philo_printf(args, phil->my_num, "is thinking");
	}
	return (0);
}

void	ft_check_finish(t_phil *phil, t_args *args)
{
	int			i;
	long long	now;

	while (args->finish == 0)
	{
		if ((args->n_must_eat != -1) && (args->p_num == args->finished_eat))
		{
			args->finish = 1;
			break ;
		}
		i = 0;
		while (i < args->p_num)
		{
			now = ft_get_time();
			if ((now - phil[i].last_time_eat) >= args->t_die)
			{
				ft_philo_printf(args, i, "died");
				args->finish = 1;
				break ;
			}
			i++;
		}
	}
}

void	ft_free_thread(t_phil *phil, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->p_num)
	{
		pthread_mutex_destroy(&(args->forks[i]));
		i++;
	}
	free(phil);
	free(args->forks);
	pthread_mutex_destroy(&(args->print));
}
