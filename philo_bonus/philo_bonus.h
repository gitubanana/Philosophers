/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:20:04 by taeypark          #+#    #+#             */
/*   Updated: 2022/11/16 13:05:32 by taeypark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <unistd.h>
# define DEAD 1
# define NOT_DEAD 0
# define ERROR 1
# define SEM_NAME "sem"
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

typedef struct s_monitor
{
	uint64_t			philo_idx;
	uint64_t			start_time;
	_Atomic uint64_t	last_eat_time;
	pid_t				*pid_arr;
	t_info				*info;
	sem_t				*fork_sem;
	sem_t				*print_sem;
	sem_t				**eat_time_sem;
	int					has_option;
}	t_monitor;

void		sem_open_and_unlink(sem_t **sem, uint64_t sem_value);
void		ft_msleep(uint64_t ms);
void		print_msg(t_monitor *monitor, char *msg);
uint64_t	cur_millisec(void);
void		free_and_kill_all(t_monitor *monitor);
void		print_error(char *str);
void		start_simulation(t_monitor *monitor, t_info *info);
void		sleeping(t_monitor *monitor);
void		thinking(t_monitor *monitor);

#endif
