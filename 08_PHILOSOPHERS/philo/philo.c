/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:43:53 by minkim            #+#    #+#             */
/*   Updated: 2022/06/02 19:17:48 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_init(t_args *args, int ac, char **av)
{
	if (!args || !ac || !av)
		return (1);
	args->p_cnt = 0;
	args->p_num = ft_atoi(av[1]);
	args->t_die = ft_atoi(av[2]) * 1000;
	args->t_eat = ft_atoi(av[3]) * 1000;
	args->t_sleep = ft_atoi(av[4]) * 1000;
	if (args->p_num < 1 || args->t_die < 0 || args->t_eat < 0 || args->t_sleep < 0)
		return (1);
	args->n_must_eat = -1;
	if (ac == 6)
	{
		args->n_must_eat = ft_atoi(av[5]);
		if (args->n_must_eat < 0)
			return (1);
	}
	return (0);
}

int	phil_init(t_args *args, t_phil **phil)
{
	int i;
	t_lock chop;

	*phil = malloc(sizeof(t_phil) * args->p_num);
	if (!args || !phil)
		return (1);
	chop.chopstick = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args->p_num);
	i = 0;
	while (i < args->p_num)
	{
		pthread_mutex_init(&chop.chopstick[i], NULL);
		i++;
	}
	i = 0;
	while (i < args->p_num)
	{
		(*phil)[i].args = args;
		(*phil)[i].lock = chop;
		(*phil)[i].my_num = i;
		(*phil)[i].last_time_eat = -1;
		(*phil)[i].eating_cnt = 0;
		i++;
	}
	return (0);
}

size_t    relative_time(size_t time_start)
{
	struct timeval    current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000 * 1000 + current.tv_usec - time_start);
}

void	ft_sleep(t_phil *phil, t_args *args)
{
	size_t cnt;

	cnt = relative_time(0);
	printf("%zd %d is sleeping\n", relative_time(args->start_time) / 1000, phil->my_num + 1);
	while (relative_time(cnt) <= args->t_sleep) {}
}

void	ft_odd(t_phil *phil, t_args *args)
{
	int	i;
	size_t	cnt;

	if (phil->my_num == 0)
		i = args->p_num - 1;
	else
		i = phil->my_num - 1;
	pthread_mutex_lock(&phil->lock.chopstick[phil->my_num]);
	printf("%zd %d has taken a fork\n", relative_time(args->start_time) / 1000, phil->my_num + 1);
	pthread_mutex_lock(&phil->lock.chopstick[i]);
	printf("%zd %d has taken a fork\n", relative_time(args->start_time) / 1000, phil->my_num + 1);
	printf("%zd %d is eating\n", relative_time(args->start_time) / 1000, phil->my_num + 1);
	cnt = relative_time(0);
	while (relative_time(cnt) <= args->t_eat) {}
	phil->eating_cnt++;
	pthread_mutex_unlock(&phil->lock.chopstick[i]);
	pthread_mutex_unlock(&phil->lock.chopstick[phil->my_num]);	
}

void	ft_even(t_phil *phil, t_args *args)
{
	int	i;
	size_t	cnt;
	
	i = phil->my_num;
	pthread_mutex_lock(&phil->lock.chopstick[i - 1]);
	printf("%zd %d has taken a fork\n", relative_time(args->start_time) / 1000, i + 1);
	pthread_mutex_lock(&phil->lock.chopstick[i]);
	printf("%zd %d has taken a fork\n", relative_time(args->start_time) / 1000, i + 1);
	printf("%zd %d is eating\n", relative_time(args->start_time) / 1000, i + 1);
	cnt = relative_time(0);
	while (relative_time(cnt) <= args->t_eat) {}
	phil->eating_cnt++;
	pthread_mutex_unlock(&phil->lock.chopstick[i]);
	pthread_mutex_unlock(&phil->lock.chopstick[i - 1]);
}

int	ft_check_finish(t_phil *phil, t_args *args)
{
	int	i;
	int eat;

	while (1)
	{
		i = 0;
		eat = 0;
		while (i < args->p_num)
		{
			if (relative_time(0) - phil[i].last_time_eat >= args->t_die)
			{
				printf("%zd %d died\n", relative_time(args->start_time) / 1000, i + 1);
				return (1);
			}
			if (args->n_must_eat != -1)
			{
				if (phil[i].eating_cnt >= args->n_must_eat)
					eat++;
				if (eat == args->p_num)
				{
					printf("eating finish\n");
					return (2);
				}
			}
			i++;
		}
	}
	return (0);
}

void	*thread(void *argv)
{
	t_args	*args;
	t_phil	*phil;

	phil = argv;
	args = phil->args;
	++args->p_cnt;
	while (args->p_cnt != args->p_num) {}
	phil->last_time_eat = relative_time(0);
	while (1)
	{
		if ((phil->my_num + 1) % 2 == 1)
			ft_odd(phil, args);
		else
			ft_even(phil, args);
		phil->last_time_eat = relative_time(0);
		ft_sleep(phil, args);
		printf("%zd %d is thinking\n", relative_time(args->start_time) / 1000, phil->my_num + 1);
	}
	return (0);
}

int	ft_philo(t_args *args, t_phil *phil)
{
	int	i;

	i = 0;
	args->start_time = relative_time(0);
	while (i < args->p_num)
	{
		pthread_create(&phil[i].tid, NULL, thread, &phil[i]);
		i++;
	}
	ft_check_finish(phil, args);
	i = 0;
	while (i < args->p_num)
	{
		pthread_join(phil[i].tid, NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	err;
	t_args	args;
	t_phil	*phil;

	// argc는 무조건 5개 아니면 6개이므로 에러 처리
	if (ac != 5 && ac != 6)
		write(1, "Error\n", 7);

	// argv를 구조체에 저장하고 필요한 변수들을 할당하고 초기화해준다
	memset(&args, 0, sizeof(t_args));
	err = args_init(&args, ac, av);
	if (err)
		write(1, "Error\n", 7);

	// 철학자별로 들어갈 변수들을 초기화한다
	err = phil_init(&args, &phil);
	if (err)
		write(1, "Error\n", 7);

	// 철학자를 시작하고 종료될때까지 동작한다
	err = ft_philo(&args, phil);
	if (err)
		write(1, "Error\n", 7);

	return (0);
}

	// printf("%d\n", args.p_num);
	// printf("%d\n", args.t_die);
	// printf("%d\n", args.t_eat);
	// printf("%d\n", args.t_sleep);
	// printf("%d\n", args.n_must_eat);

	// printf("\n");

	// printf("%d\n", phil[0].my_num);
	// printf("%d\n", phil[0].chopstick_left);
	// printf("%d\n", phil[0].chopstick_right);
	// printf("%d\n", phil[0].eating);
	// printf("%d\n", phil[0].sleeping);
	// printf("%d\n", phil[0].waiting);
	// printf("%d\n", phil[0].died);
	// printf("%d\n", phil[0].eating_cnt);


	// printf("num %d\n", phil->my_num + 1);
	// printf("num %d\n", (phil->my_num + 1) % 2);
	// printf("%zd\n", relative_time(args->start_time));


	// timestamp_in_ms X has taken a fork
	// timestamp_in_ms X is eating
	// timestamp_in_ms X is sleeping
	// timestamp_in_ms X is thinking
	// timestamp_in_ms X died


	// 	}
	// 	else
	// 	{
	// 		printf("%zd %d is thinking\n", relative_time(args->start_time), phil->my_num + 1);
	// 		while (phil->lock.num[i] != 0 && phil->lock.num[i] != -i-1) {}
	// 	}
	// 	pthread_mutex_unlock(&phil->lock.chopstick[i - 1]);
	// }
	// else
	// {
	// 	printf("%zd %d is thinking\n", relative_time(args->start_time), phil->my_num + 1);
	// 	while (phil->lock.num[i - 1] != 0 && phil->lock.num[i - 1] != -i-1) {}
	// }