/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:19:25 by taeypark          #+#    #+#             */
/*   Updated: 2022/11/17 17:04:04 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_atoi(char *str, int *is_error)
{
	int	ret;

	if (*is_error)
		return (0);
	ret = 0;
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
		{
			*is_error = 1;
			return (0);
		}
		ret = ret * 10 + (*str - '0');
		str++;
	}
	return (ret);
}

int	init_info(t_info *info, char *argv[], int has_option)
{
	int	is_error;

	is_error = 0;
	info->philo_num = philo_atoi(argv[PHILO_NUM_IDX], &is_error);
	info->time_to_die = philo_atoi(argv[TIME_TO_DIE_IDX], &is_error);
	info->time_to_eat = philo_atoi(argv[TIME_TO_EAT_IDX], &is_error);
	info->time_to_sleep = philo_atoi(argv[TIME_TO_SLEEP_IDX], &is_error);
	info->must_eat_time = ULL_MAX;
	if (has_option)
		info->must_eat_time = philo_atoi(argv[must_eat_time_IDX], &is_error);
	return (is_error);
}

int	init_monitor(t_monitor *monitor, t_info *info)
{
	monitor->eat_time_sem = malloc(sizeof(sem_t *) * info->philo_num);
	monitor->pid_arr = malloc(sizeof(pid_t) * info->philo_num);
	if (!monitor->eat_time_sem || !monitor->pid_arr)
	{
		free(monitor->eat_time_sem);
		free(monitor->pid_arr);
		return (ERROR);
	}
	sem_unlink(SEM_NAME);
	sem_open_and_unlink(&monitor->fork_sem, info->philo_num);
	sem_open_and_unlink(&monitor->print_sem, 1);
	monitor->info = info;
	monitor->has_option = (info->must_eat_time != ULL_MAX);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info		info;
	t_monitor	monitor;

	if (argc < 5 || argc > 6)
	{
		print_error("usage: ");
		print_error(argv[0]);
		print_error(" [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (number_of_times_each_philosopher_must_eat)\n");
	}
	else
	{
		if (init_info(&info, argv, argc == 6) == ERROR)
			print_error("Error: invalid arguments\n");
		else
		{
			if (init_monitor(&monitor, &info) == ERROR)
				print_error("Error: malloc\n");
			else
			{
				start_simulation(&monitor, &info);
				free_and_kill_all(&monitor);
			}
		}
	}
	return (0);
}
