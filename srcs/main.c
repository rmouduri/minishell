/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:40:46 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/03 23:10:46 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "minishell.h"

t_shell	*g_shell;

int	main(__attribute__((unused))int ac, __attribute__((unused))
		char **av, char **env)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler);
	if (!env)
		return (1);
	if (init_shell(env) == 1)
		return (1);
	while (1)
	{
		while (!g_shell->input)
			g_shell->input = get_input();
		go_to_function();
		free_tab(g_shell->input, -1);
		g_shell->input = 0;
		free(g_shell->ops);
	}
	if (g_shell)
		free_shell();
	return (0);
}
