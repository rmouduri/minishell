/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 22:23:08 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/17 22:34:19 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <wait.h>
#include <stdlib.h>
#include "minishell.h"

__pid_t	*init_cpids(int amt)
{
	__pid_t	*cpids;
	int		i;

	cpids = malloc(sizeof(__pid_t) * amt);
	if (!cpids)
		return (0);
	i = -1;
	while (++i < amt)
		cpids[i] = -1;
	return (cpids);
}

void	wait_kill_pids(void)
{
	int	i;

	waitpid(g_shell->cpids[g_shell->pipes - 1], &g_shell->waitstatus, 0);
	i = -1;
	while (++i < g_shell->pipes - 1)
		if (g_shell->cpids[i] > 1)
			kill(g_shell->cpids[i], SIGPIPE);
}
