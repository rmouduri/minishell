/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:05:24 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/03 22:54:29 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "minishell.h"

static int	incr_i(char **input, int i)
{
	while (input[i] && ft_strcmp(input[i], ";") && ft_strcmp(input[i], "&&")
		&& ft_strcmp(input[i], "|"))
		++i;
	if (input[i])
		return (i + 1);
	return (i);
}

static void	reset(void)
{
	g_shell->waitstatus = 0;
	g_shell->op = 0;
	g_shell->ret = 0;
	if (g_shell->fct)
		free(g_shell->fct);
	g_shell->fct = 0;
	if (g_shell->exec)
		free(g_shell->exec);
	g_shell->exec = 0;
	++g_shell->index;
	if (g_shell->char_env)
		free_char_env(g_shell->char_env, -1);
	g_shell->char_env = 0;
}

static char	*get_exec(char **input)
{
	char	**path;
	char	*exec;
	int		index;

	exec = 0;
	path = get_path(input[0]);
	if (!path)
		return (0);
	index = check_exec(path);
	if (index != -1)
		exec = ft_strdup(path[index]);
	index = -1;
	while (path[++index])
		free(path[index]);
	free(path);
	return (exec);
}

int	fork_and_exec(int fd, int *pipefd, int i)
{
	if (ft_redirect(fd, pipefd) == 0)
	{
		if (!is_builtin(i) || check_builtins(i) == -1)
		{
			if (!g_shell->exec || check_function() == -1)
				return_error("minishell", g_shell->input[i],
					"command not found", 0);
		}
	}
	reset_redirect();
	waitpid(g_shell->cpid, &g_shell->waitstatus, 0);
	return (0);
}

int	go_to_function(void)
{
	int		i;
	int		fd;
	int		*pipefd;

	i = 0;
	pipefd = create_pipes();
	g_shell->tty[0] = dup(STDIN_FILENO);
	g_shell->tty[1] = dup(STDOUT_FILENO);
	while (g_shell->input[i])
	{
		g_shell->fct = get_arg_tab(&g_shell->input[i], i);
		g_shell->char_env = dup_env();
		g_shell->exec = get_exec(&g_shell->input[i]);
		fd = get_and_open_file(&g_shell->input[i], i);
		if (fd != -1 && g_shell->fct && g_shell->char_env)
			fork_and_exec(fd, (int *)pipefd, i);
		g_shell->ret = WEXITSTATUS(g_shell->waitstatus);
		reset();
		i = incr_i(g_shell->input, i);
	}
	g_shell->index = 0;
	close_pipes(pipefd);
	return (g_shell->ret);
}
