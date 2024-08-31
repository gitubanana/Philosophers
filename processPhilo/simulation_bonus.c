/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:02:57 by taeypark          #+#    #+#             */
/*   Updated: 2022/11/16 10:30:57 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_two_forks_and_eat(t_monitor *monitor)
{
	sem_wait(monitor->fork_sem);
	print_msg(monitor, "has taken a fork");
	sem_wait(monitor->fork_sem);
	print_msg(monitor, "has taken a fork");
	sem_wait(monitor->eat_time_sem[monitor->philo_idx]);
	monitor->last_eat_time = cur_millisec();
	sem_post(monitor->eat_time_sem[monitor->philo_idx]);
	print_msg(monitor, "is eating");
	ft_msleep(monitor->info->time_to_eat);
	sem_post(monitor->fork_sem);
	sem_post(monitor->fork_sem);
}

void	routine(t_monitor *monitor)
{
	uint64_t	eat_time;

	eat_time = 0;
	while (1)
	{
		if (eat_time == monitor->info->must_eat_time)
			exit(NOT_DEAD);
		take_two_forks_and_eat(monitor);
		eat_time++;
		sleeping(monitor);
		thinking(monitor);
	}
}

void	*monitor_philo(void *arg)
{
	uint64_t	cur_ms;
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (1)
	{
		sem_wait(monitor->eat_time_sem[monitor->philo_idx]);
		cur_ms = cur_millisec();
		if (cur_ms - monitor->last_eat_time >= monitor->info->time_to_die)
		{
			sem_wait(monitor->print_sem);
			printf("%lu %lu died\n",
				cur_ms - monitor->start_time, monitor->philo_idx + 1);
			exit(DEAD);
		}
		sem_post(monitor->eat_time_sem[monitor->philo_idx]);
	}
}

void	simulation(t_monitor *monitor)
{
	pthread_t	th;

	sem_open_and_unlink(&monitor->eat_time_sem[monitor->philo_idx], 1);
	pthread_create(&th, NULL, monitor_philo, monitor);
	pthread_detach(th);
	routine(monitor);
}

void	start_simulation(t_monitor *monitor, t_info *info)
{
	uint64_t	i;
	uint64_t	start_time;
	int			status;

	start_time = cur_millisec();
	i = -1;
	while (++i < info->philo_num)
	{
		monitor->pid_arr[i] = fork();
		if (monitor->pid_arr[i] == 0)
		{
			monitor->philo_idx = i;
			monitor->start_time = start_time;
			monitor->last_eat_time = start_time;
			simulation(monitor);
		}
	}
	status = NOT_DEAD;
	i = -1;
	if (monitor->has_option)
		while (++i < monitor->info->philo_num && status == NOT_DEAD)
			waitpid(-1, &status, 0);
	else
		waitpid(-1, 0, 0);
}
