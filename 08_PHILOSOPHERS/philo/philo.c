/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:43:53 by minkim            #+#    #+#             */
/*   Updated: 2022/05/25 18:59:12 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_args
{
	size_t	start_time;
	pthread_mutex_t lock;
	int	*chopsticks;
	int	p_cnt;
	int	p_num; //number_of_philosophers;
	int	t_die; //time_to_die;
	int	t_eat; //time_to_eat;
	int	t_sleep; //time_to_sleep;
	int	n_must_eat; //number_of_times_each_philosopher_must_eat;
}	t_args;

typedef struct s_phil
{
	t_args *args;
	pthread_t tid;
	int my_num;
	int chopstick_left;
	int chopstick_right;
	int eating;
	int sleeping;
	int waiting;
	int died;
	int eating_cnt;
}	t_phil;

int	args_init(t_args *args, int ac, char **av)
{
	if (!args || !ac || !av)
		return (1);
	pthread_mutex_init(&args->lock, NULL);
	args->p_cnt = 0;
	args->p_num = ft_atoi(av[1]);
	args->t_die = ft_atoi(av[2]);
	args->t_eat = ft_atoi(av[3]);
	args->t_sleep = ft_atoi(av[4]);
	if (args->p_num < 1 || args->t_die < 0 || args->t_eat < 0 || args->t_sleep < 0)
		return (1);
	args->n_must_eat = -1;
	if (ac == 6)
	{
		args->n_must_eat = ft_atoi(av[5]);
		if (args->n_must_eat < 1)
			return (1);
	}
	return (0);
}

int	phil_init(t_args *args, t_phil **phil)
{
	int i;

	i = 0;
	*phil = malloc(sizeof(t_phil) * args->p_num);
	if (!args || !phil)
		return (1);
	while (i < args->p_num)
	{
		(*phil)[i].args = args;
		(*phil)[i].my_num = i;
		(*phil)[i].chopstick_left = 0;
		(*phil)[i].chopstick_right = 0;
		(*phil)[i].eating = 0;
		(*phil)[i].sleeping = 0;
		(*phil)[i].waiting = 0;
		(*phil)[i].died = 0;
		(*phil)[i].eating_cnt = -1;
		if (args->n_must_eat != -1)
			(*phil)[i].eating_cnt = args->n_must_eat;
		i++;
	}
	return (0);
}

int	init_chop(int *chopsticks, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		chopsticks[i] = 1;
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

void *thread(void *argv)
{
	t_args	*args;
	t_phil	*phil;
	

	phil = argv;
	args = phil->args;
	++args->p_cnt;
	while (args->p_cnt != args->p_num && !args->start_time)
		usleep(1);
	usleep(1);
	printf("%zd\n", relative_time(args->start_time));
	return (0);
}

int	ft_philo(t_args *args, t_phil *phil)
{
	int	i;

	args->chopsticks = (int *)malloc(sizeof(int) * args->p_num);
	init_chop(args->chopsticks, args->p_num);
	i = 0;
	while (i < args->p_num)
	{
		pthread_create(&phil[i].tid, NULL, thread, &phil[i]);
		i++;
	}
	args->start_time = relative_time(0);
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