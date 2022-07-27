/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:46:21 by minkim            #+#    #+#             */
/*   Updated: 2022/07/27 12:11:02 by minkim           ###   ########.fr       */
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
	int				p_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	long long		start_time;
	int				finish;
	int				finished_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_args;

typedef struct s_phil
{
	t_args		*args;
	pthread_t	tid;
	int			my_num;
	int			left;
	int			right;
	long long	last_time_eat;
	int			eating_cnt;
}	t_phil;

int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			arg_init_mutex(t_args *args);
int			args_init(t_args *args, int ac, char **av);
int			phil_init(t_args *args, t_phil **phil);
int			ft_philo_printf(t_args *args, int id, char *msg);
int			ft_philo_action(t_args *args, t_phil *phil);
long long	ft_get_time(void);
void		ft_pass_time(long long wait_time, t_args *args);
void		*thread(void *argv);
void		ft_check_finish(t_phil *phil, t_args *args);
void		ft_free_thread(t_phil *phil, t_args *args);

#endif
