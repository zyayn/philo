/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:21:46 by zchia             #+#    #+#             */
/*   Updated: 2024/08/09 22:21:46 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <semaphore.h>

# define MAX_PHI 1000

typedef struct s_rules
{
	int	nbr_phi;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nbr_eat;
}	t_rules;

typedef struct s_param
{
	t_rules	rules;
	int		begin_time;
	sem_t	*forks;
}	t_param;

typedef struct s_philo
{
	pid_t	pid;
	int		phi_id;
	int		nbr_eaten;
	int		start_eat;
	int		is_full;
	t_param	*param;
}	t_philo;

int		eat_sleep_think(t_rules rules, t_philo *phi);
void	*est_actions(void *arg);
int		get_time(void);
int		ft_isint(const char *str);

#endif
