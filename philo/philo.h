/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:35:39 by taeypark          #+#    #+#             */
/*   Updated: 2022/11/14 14:11:50 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# define ERROR 1
# define ULL_MAX 18446744073709551615ULL

enum	e_idx
{
	PHILO_NUM_IDX = 1,
	TIME_TO_DIE_IDX,
	TIME_TO_EAT_IDX,
	TIME_TO_SLEEP_IDX,
	must_eat_time_IDX
};

typedef struct s_info
{
	uint64_t	philo_num;
	uint64_t	time_to_eat;
	uint64_t	time_to_die;
	uint64_t	time_to_sleep;
	uint64_t	must_eat_time;
}	t_info;

typedef struct s_simul
{
	int				fork;
	t_info			*info;
	uint64_t		philo_idx;
	uint64_t		start_time;
	uint64_t		last_eat_time;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*eat_time_mutex;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	int				have_eaten_the_times;
}	t_simul;

typedef struct s_monitor
{
	t_info			*info;
	t_simul			*simul;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*eat_time_mutex;
	pthread_mutex_t	print_mutex;
}	t_monitor;

void		ft_msleep(uint64_t ms);
int			ft_strlen(char *str);
void		print_error(char *msg);
void		print_msg(t_simul *simul, char *msg);
uint64_t	cur_millisec(void);
int			right_fork_idx(t_simul *simul);
int			left_fork_idx(t_simul *simul);
void		take_two_forks_even(t_simul *simul);
void		free_all(t_monitor *monitor);
void		take_two_forks_odd(t_simul *simul);
void		start_simulation(t_monitor *monitor, t_info *info);

#endif
