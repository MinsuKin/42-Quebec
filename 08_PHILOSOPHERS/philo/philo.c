/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:43:53 by minkim            #+#    #+#             */
/*   Updated: 2022/07/27 12:26:03 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo(t_args *args, t_phil *phil)
{
	int	i;

	i = 0;
	while (i < args->p_num)
	{
		phil[i].last_time_eat = ft_get_time();
		if (args->p_num == 1)
		{
			ft_philo_printf(args, phil->my_num, "has taken a fork");
			break ;
		}
		if (pthread_create(&phil[i].tid, NULL, thread, &(phil[i])))
			return (1);
		i++;
	}
	ft_check_finish(phil, args);
	i = 0;
	while (i < args->p_num)
	{
		pthread_join(phil[i].tid, NULL);
		i++;
	}
	ft_free_thread(phil, args);
	return (0);
}

int	ft_error(void)
{
	write(1, "Error\n", 7);
	return (0);
}

int	check_digit(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_isdigit(args[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_args(int ac, char **av)
{
	if (check_digit(av[1]))
		return (1);
	if (check_digit(av[2]))
		return (1);
	if (check_digit(av[3]))
		return (1);
	if (check_digit(av[4]))
		return (1);
	if (ac == 6 && check_digit(av[5]))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int		err;
	t_args	args;
	t_phil	*phil;

	if (ac != 5 && ac != 6)
		return (ft_error());
	err = check_args(ac, av);
	if (err)
		return (ft_error());
	memset(&args, 0, sizeof(t_args));
	err = args_init(&args, ac, av);
	if (err)
		return (ft_error());
	err = phil_init(&args, &phil);
	if (err)
		return (ft_error());
	err = ft_philo(&args, phil);
	if (err)
		return (ft_error());
	return (0);
}
