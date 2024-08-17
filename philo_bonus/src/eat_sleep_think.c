/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:12:10 by zchia             #+#    #+#             */
/*   Updated: 2024/08/05 22:12:10 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isint(const char *str)
{
	int	nbr;

	nbr = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = 1;
		str++;
	}
	while (*str == ' ' || *str == '\t')
		str++;
	return (nbr && *str == '\0');
}

void	kill_and_clean(t_param *param, t_philo *phi)
{
	int	i;

	i = 0;
	while (i < param->rules.nbr_phi)
	{
		kill(phi[i].pid, SIGKILL);
		i++;
	}
	sem_close(param->forks);
	sem_close(param->stop_sem);
	sem_unlink("forks");
	sem_unlink("stop");
	free(param);
}

int	init_param(t_param *param, t_rules rules)
{
	param->rules = rules;
	param->begin_time = get_time();
	param->stop = 0;
	param->forks = sem_open("forks", O_CREAT, 0644, param->rules.nbr_phi);
	param->stop_sem = sem_open("stop", O_CREAT, 0644, 0);
	if (param->forks == SEM_FAILED || param->stop_sem == SEM_FAILED)
	{
		sem_close(param->forks);
		sem_close(param->stop_sem);
		sem_unlink("forks");
		sem_unlink("stop");
		free(param);
		return (-1);
	}
	sem_unlink("forks");
	sem_unlink("stop");
	return (0);
}

void	*monitor_full(void *arg)
{
	t_philo	*phi;
	int		full_count;
	int		status;

	full_count = 0;
	phi = (t_philo *)arg;
	while (1)
	{
		if (waitpid(-1, &status, WNOHANG) > 0)
			full_count++;
		if (full_count == phi->param->rules.nbr_phi)
		{
			sem_post(phi->param->stop_sem);
			break ;
		}
		usleep(1000);
	}
	exit (0);
}

int	eat_sleep_think(t_rules rules, t_philo *phi)
{
	t_param		*param;
	pthread_t	monitor_thread;
	int			i;

	param = (t_param *)malloc(sizeof(t_param));
	if (!param || init_param(param, rules) == -1)
		return (-1);
	i = 0;
	while (i < rules.nbr_phi)
	{
		phi[i].param = param;
		phi[i].start_eat = get_time();
		phi[i].pid = fork();
		if (phi[i].pid == -1)
			return (-1);
		else if (!phi[i].pid)
			est_actions(&phi[i]);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_full, (void *)phi))
		return (-1);
	pthread_detach(monitor_thread);
	sem_wait(phi->param->stop_sem);
	kill_and_clean(param, phi);
	return (0);
}
