/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:49:26 by taeypark          #+#    #+#             */
/*   Updated: 2022/11/12 20:29:57 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	cur_millisec(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
}

int	right_fork_idx(t_simul *simul)
{
	if (simul->philo_idx == 0)
		return (simul->info->philo_num - 1);
	return (simul->philo_idx - 1);
}

int	left_fork_idx(t_simul *simul)
{
	return (simul->philo_idx);
}

void	take_two_forks_even(t_simul *simul)
{
	pthread_mutex_lock(simul->left_fork_mutex);
	simul->fork++;
	print_msg(simul, "has taken a fork");
	pthread_mutex_lock(simul->right_fork_mutex);
	simul->fork++;
	print_msg(simul, "has taken a fork");
	pthread_mutex_lock(simul->eat_time_mutex);
	simul->last_eat_time = cur_millisec();
	pthread_mutex_unlock(simul->eat_time_mutex);
	print_msg(simul, "is eating");
	ft_msleep(simul->info->time_to_eat);
	pthread_mutex_unlock(simul->right_fork_mutex);
	pthread_mutex_unlock(simul->left_fork_mutex);
}

void	take_two_forks_odd(t_simul *simul)
{
	pthread_mutex_lock(simul->right_fork_mutex);
	simul->fork++;
	print_msg(simul, "has taken a fork");
	pthread_mutex_lock(simul->left_fork_mutex);
	simul->fork++;
	print_msg(simul, "has taken a fork");
	pthread_mutex_lock(simul->eat_time_mutex);
	simul->last_eat_time = cur_millisec();
	pthread_mutex_unlock(simul->eat_time_mutex);
	print_msg(simul, "is eating");
	ft_msleep(simul->info->time_to_eat);
	pthread_mutex_unlock(simul->left_fork_mutex);
	pthread_mutex_unlock(simul->right_fork_mutex);
}
