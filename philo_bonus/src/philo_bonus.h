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
# include <stdarg.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <fcntl.h>

# define MAX_PHI 4242

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
	sem_t	*forks;
	sem_t	*print_sem;
	int		begin_time;
	int		stop;
}	t_param;

typedef struct s_philo
{
	pid_t	pid;
	int		phi_id;
	int		nbr_eaten;
	int		start_time;
	int		t_hungry;
	int		is_dead;
	t_param	*param;
}	t_philo;

int		eat_sleep_think(t_rules rules, t_philo *phi);
void	*est_actions(void *arg);
void	print_log(t_philo *phi, char *status);
int		get_time(void);
int		ft_atoi(const char *str);
int		ft_isint(const char *str);

#endif
