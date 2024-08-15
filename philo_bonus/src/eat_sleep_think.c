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

void	clean_sem(t_param *param)
{
	sem_close(param->forks);
	sem_unlink("forks");
	sem_unlink("term");
}

void	kill_and_clean(t_param *param, t_philo *phi)
{
	int	i;
	int	status;

	i = 0;
	while (i < param->rules.nbr_phi)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status))
			break ;
		i++;
	}
	i = 0;
	while (i < param->rules.nbr_phi)
		kill(phi[i++].pid, SIGKILL);
	clean_sem(param);
	free(param);
}

int	init_param(t_param *param, t_rules rules)
{
	param->rules = rules;
	param->begin_time = get_time();
	param->forks = sem_open("forks", O_CREAT, 0644, param->rules.nbr_phi);
	if (param->forks == SEM_FAILED)
	{
		clean_sem(param);
		printf("Error: Failed to initialise semaphores.\n");
		return (-1);
	}
	return (0);
}

int	eat_sleep_think(t_rules rules, t_philo *phi)
{
	t_param	*param;
	int		i;

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
		{
			clean_sem(param);
			free(param);
			return (-1);
		}
		else if (phi[i].pid == 0)
			est_actions(&phi[i]);
		i++;
	}
	kill_and_clean(param, phi);
	return (0);
}
