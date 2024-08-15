/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:30:22 by zchia             #+#    #+#             */
/*   Updated: 2024/08/04 22:30:22 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHI 1000

typedef struct s_rules
{
	int	nbr_phi;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nbr_eat;
}	t_rules;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_param
{
	t_rules			rules;
	t_fork			*forks;
	int				begin_time;
	int				stop;
	pthread_mutex_t	print_mutex;
}	t_param;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				phi_id;
	int				nbr_eaten;
	int				start_eat;
	t_param			*param;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	die_mutex;
}	t_philo;

int		get_time(void);
void	print_log(t_philo *phi, char *status);
void	*est_actions(void *arg);
int		eat_sleep_think(t_rules rules, t_philo *phi);
int		ft_isint(const char *str);

#endif