/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:07:59 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/10 12:50:02 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
		return (1);
	write(STDIN_FILENO, pwd, ft_strlen(pwd));
	write(STDIN_FILENO, "\n", 1);
	free(pwd);
	return (0);
}
