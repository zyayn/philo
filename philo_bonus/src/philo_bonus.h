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

typedef struct s_philo
{
	pid_t			pid;
	int				phi_id;
	int				nbr_eaten;
	int				start_time;
	int				t_hungry;
	int				is_dead;
	struct s_param	*param;
}	t_philo;

typedef struct s_param
{
	t_rules	rules;
	t_philo	*philos;
	sem_t	*forks;
	sem_t	*print_sem;	
	int		begin_time;
	int		stop;
}	t_param;

int		init_param(t_param *param, t_rules rules, t_philo *phi);
int		init_sem(t_param *param, t_rules rules);
void	monitor(t_param *param);
void	est_actions(t_philo *phi);
void	cleanup(t_param *param);
void	print_log(t_param *param, int id, char *status);
int		get_time(void);

int		ft_printf(const char *param, ...);
char	*ft_getstr(char *s);
int		ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		ft_isint(const char *str);

#endif
