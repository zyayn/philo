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
# include <stdarg.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define CONVERSION "cspdiuxX%"
# define BIGHEX "0123456789ABCDEF"
# define SMALLHEX "0123456789abcdef"
# define MAX_PHI 4242

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
	int				nbr_eaten;
	int				start_time;
	int				t_hungry;
	int				is_dead;
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
	int				begin_time;
	int				stop;
}	t_param;

int		get_time(void);
void	print_log(t_param *param, int id, char *status);
void	destroy_param(t_param *param);
void	*est_actions(void *arg);
int		eat_sleep_think(t_rules rules, t_philo *phi);

int		ft_printf(const char *param, ...);
char	*ft_getstr(char *s);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		ft_isint(const char *str);

#endif