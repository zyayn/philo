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

void	cleanup(t_param *param)
{
	sem_close(param->forks);
	sem_close(param->print_sem);
	sem_unlink("forks");
	sem_unlink("print_sem");
	free(param);
}

void	check_all_eaten(t_philo *phi)
{
	int	phi_full;
	int	i;

	phi_full = 0;
	i = 0;
	while (i < phi->param->rules.nbr_phi)
	{
		if (phi[i].nbr_eaten >= phi->param->rules.nbr_eat)
			phi_full++;
		i++;
	}
	if (phi_full == phi->param->rules.nbr_phi)
		phi->param->stop = 1;
}

void	monitor(t_philo *phi)
{
	int	i;
	int	j;
	int	hungry;

	while (!phi->param->stop)
	{
		i = 0;
		while (i < phi->param->rules.nbr_phi)
		{
			sem_wait(phi->param->print_sem);
			hungry = get_time() - phi[i].start_time;
			sem_post(phi->param->print_sem);
			if (hungry >= phi->param->rules.t_die)
			{
				print_log(&phi[i++], "died");
				phi->param->stop = 1;
			}
			if (phi->param->stop)
			{
				j = 0;
				while (j < phi->param->rules.nbr_phi)
					kill(phi[j++].pid, SIGKILL);
				exit(0);
			}
		}
		check_all_eaten(phi);
	}
}

int	init_param(t_param *param, t_rules rules)
{
	param->rules = rules;
	param->begin_time = get_time();
	param->stop = 0;
	sem_close(param->forks);
	sem_close(param->print_sem);
	sem_unlink("forks");
	sem_unlink("print_sem");
	param->forks = sem_open("forks", O_CREAT, 0644, param->rules.nbr_phi);
	param->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	if (param->forks == SEM_FAILED || param->print_sem == SEM_FAILED)
	{
		if (param->forks != SEM_FAILED)
			sem_close(param->forks);
		if (param->print_sem != SEM_FAILED)
			sem_close(param->print_sem);
		sem_unlink("forks");
		sem_unlink("print_sem");
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
		phi[i].start_time = get_time();
		phi[i].pid = fork();
		if (phi[i].pid == -1)
		{
			cleanup(param);
			return (-1);
		}
		else if (!phi[i].pid)
			est_actions(&phi[i]);
		i++;
	}
	monitor(phi);
	cleanup(param);
	return (0);
}
