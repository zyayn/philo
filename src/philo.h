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

# define MAX_PHI 42

# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules
{
	int	nbr_phi;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nbr_eat;
}	t_rules;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				phi_id;
	int				left;
	int				right;
	int				nbr_eaten;
	int				start_time;
	int				t_hungry;
	int				is_dead;
	pthread_mutex_t	think_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	die_mutex;
	struct s_param	*param;
}	t_philo;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_param
{
	t_rules			rules;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	print_mutex;
	int				stop;
}	t_param;

int		get_time(void);
void	print_log(t_param *param, int id, char *status);
int		init_param(t_param *param, t_rules rules, t_philo *phi);
void	destroy_param(t_param *param);
int		eat_sleep_think(t_rules rules, t_philo *phi);

#endif